/*
 *
 * LVGL advanced example project for Ultibo API
 *
 * This example shows how to initialize and use the LVGL graphics library in an
 * Ultibo application. Initialization requires configuring the framebuffer, mouse,
 * keyboard and touch devices as well as starting the LVGL event loop to service
 * UI events such as button clicks.
 *
 * A precompiled static library for LVGL is included with the Ultibo RTL and the 
 * header files are provided with the Ultibo API, the library is compiled with
 * the most common options but can easily be recompiled to suit your needs by
 * following the information in the libs/lvgl folder of the API.
 *
 * For the full LVGL documentation visit https://lvgl.io/
 * 
 *
 * This file is part of the Ultibo project, https://ultibo.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2025 Garry Wood <garry@softoz.com.au>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
 
#include "ultibo/platform.h"
#include "ultibo/threads.h"
#include "ultibo/serial.h"
#include "ultibo/logging.h"
#include "ultibo/framebuffer.h"
#include "ultibo/mouse.h"
#include "ultibo/touch.h"
#include "ultibo/keyboard.h"

#include "lv_conf.h"
#include "lvgl/lvgl.h"

/* Include the lvgl demo headers to allow starting the LVGL demos */
#include "lvgl/demos/lv_demos.h"

/* App configuration structure 
 *
 * Instead of declaring global variables for various pieces of information
 * like the display size and depth, rendering buffers and the mouse or touch
 * device we utilize the capability of LVGL to attach a data parameter to 
 * many objects and pass that too us when it calls the various device callback
 * functions. We can use the data parameter to obtain the information we need
 * during the callback and avoid the problems caused by global variables
 */
typedef struct _APP_CONFIG {
	/* Framebuffer and Display Configuration */
	FRAMEBUFFER_DEVICE *display_device;         /* Framebuffer for display */
    FRAMEBUFFER_PROPERTIES display_properties;  /* Properties of Framebuffer */

	uint32_t display_width;                     /* Display Width */
	uint32_t display_height;                    /* Display Height */
	uint32_t display_depth;                     /* Display Bits per Pixel */
	uint32_t display_bytes_per_pixel;           /* Display Bytes per Pixel */

	uint32_t display_buffer_bytes;				/* LVGL Render Buffer Size */
	void *display_render_buf1;                  /* LVGL Render Buffer 1 */
	void *display_render_buf2;                  /* LVGL Render Buffer 2 */
	lv_display_t *display_driver;               /* LVGL display driver */

	/* Mouse and Touch Configuration */
	TOUCH_DEVICE *touch_device;                 /* Device for touch data, null if using mouse only */
	TOUCH_PROPERTIES touch_properties;          /* Properties of Touch device */

	uint32_t touch_max_x;                       /* Maximum X value for the current touch device (if applicable) */
	uint32_t touch_max_y;                       /* Maximum Y value for the current touch device (if applicable) */

	uint32_t touch_use_mouse;                   /* Get mouse data if 0 or touch data if 1 */
	uint32_t touch_show_cursor;                 /* If 1 show and update cursor on display */
	uint32_t touch_config_delay;                /* If 1 then delay touch configuration due to USB touch */
	double_t touch_scaling_x;                   /* Scale factor for display width to touch maximum x */
	double_t touch_scaling_y;                   /* Scale factor for display height to touch maximum y */
    int32_t touch_last_x;                       /* Last X position of the touch or mouse data */
    int32_t touch_last_y;                       /* Last Y position of the touch or mouse data */

	lv_indev_t *touch_driver;                   /* LVGL touch driver */

	/* Keyboard Configuration */
	uint32_t keyboard_last_key;                 /* Last key pressed on keyboard */

	lv_indev_t *keyboard_driver;                /* LVGL keyboard/keypad driver */

} APP_CONFIG;


/* Forward declare the functions used by main */
static int display_init_configuration(APP_CONFIG *config);
static void display_flush_callback(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map);

static int touch_init_configuration(APP_CONFIG *config);
static void touch_read_callback(lv_indev_t * indev, lv_indev_data_t * data);

static void keyboard_read_callback(lv_indev_t * indev, lv_indev_data_t * data);

static int lvgl_init_configuration(APP_CONFIG *config);

static int lvgl_create_screen(APP_CONFIG *config);

static void * lvgl_tick_thread(void *args);

/* The main function for our app, called after system initialization */
int apimain(int argc, char **argv)
{
    int res = -1;
    pthread_t tick_thread;

    /* Allocate a local copy of our app configuration, this will only
     * remain valid until our main function exits so if you plan to 
     * spawn multiple threads and then return from main you should 
     * allocate the app configuration dynamically using malloc()
     */
	APP_CONFIG config;

    /* Initialize the app configuration */
    memset(&config, 0, sizeof(APP_CONFIG));

    #ifdef DEBUG
    /* Enable logging to the default serial device */
    serial_logging_device_add(serial_device_get_default());

    /* Make the serial logging device the default */
    logging_device_set_default(logging_device_find_by_type(LOGGING_TYPE_SERIAL));

    /* Redirect stdout to the serial logging device */
    logging_device_redirect_output(logging_device_find_by_type(LOGGING_TYPE_SERIAL));

    logging_output("Logging initialized");
    #endif

	/* Initialize display configuration */
	res = display_init_configuration(&config);
	if (res < 0)
		return res;

	/* Initialize touch configuration */
	res = touch_init_configuration(&config);
	if (res < 0)
		return res;

	/* Initialize LVGL configuration */
	res = lvgl_init_configuration(&config);
	if (res < 0)
		return res;

	/* Initialize the demo screen */
	lvgl_create_screen(&config);

	/* Start the LVGL tick thread */
	pthread_create(&tick_thread, NULL, *lvgl_tick_thread, &config);

    /* Start the main loop, running the LVGL timer */
	while (1)
	{
		/* Process LVGL events */
		uint32_t time_till_next = lv_timer_handler();

		/* Wait for next event time */
		usleep(time_till_next * 1000);
	}

    return res;
}

/* Initialize display configuration and determine display properties */
static int display_init_configuration(APP_CONFIG *config)
{

	/* Get default framebuffer device */
	config->display_device = framebuffer_device_get_default();
	if (!config->display_device)
	{
		#ifdef DEBUG
		logging_output("No display device found");
		#endif
		return -1;
	}

	/* Get the properties of the framebuffer device */
	if (framebuffer_device_get_properties(config->display_device, &config->display_properties) != ERROR_SUCCESS)
	{
		#ifdef DEBUG
		logging_output("Failed to get display device properties");
		#endif
		return -1;
	}

	/* Store the display configuration */
	config->display_width = config->display_properties.physicalwidth;
	config->display_height = config->display_properties.physicalheight;
	config->display_depth =  config->display_properties.depth;
	config->display_bytes_per_pixel = config->display_properties.depth >> 3;

	#ifdef DEBUG
	logging_output("Display configuration initialized");
	logging_outputf(" Width = %d\n", (int)config->display_width);
	logging_outputf(" Height = %d\n", (int)config->display_height);
	logging_outputf(" Depth = %d\n", (int)config->display_depth);
	logging_outputf(" Bytes per Pixel = %d\n", (int)config->display_bytes_per_pixel);
	#endif

	return 0;
}

/* LVGL display flush callback, called whenever an area of the UI needs to be written to the display */
static void display_flush_callback(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map)
{
	APP_CONFIG *config = (APP_CONFIG *)lv_display_get_user_data(disp);

	/* Check for valid parameters */
	if(config->display_device == NULL ||
		area->x2 < 0 ||
		area->y2 < 0 ||
		area->x1 > config->display_width - 1 ||
		area->y1 > config->display_height - 1)
	{
		lv_display_flush_ready(disp);

		return;
	}

	/* Clip the drawing area to the screen */
	int32_t act_x1 = area->x1 < 0 ? 0 : area->x1;
	int32_t act_y1 = area->y1 < 0 ? 0 : area->y1;
	int32_t act_x2 = area->x2 > config->display_width - 1 ? config->display_width - 1 : area->x2;
	int32_t act_y2 = area->y2 > config->display_height - 1 ? config->display_height - 1 : area->y2;

	/* Hide the cursor if needed */
	if (config->touch_show_cursor)
		framebuffer_device_update_cursor(config->display_device, FALSE, config->touch_last_x, config->touch_last_y, FALSE);

	/* If the framebuffer is not in the same format as LV_COLOR_DEPTH the buffer would be converted
	 * here to the correct format, both LVGL and Ultibo have functions to convert between color formats
	 *
	 * By default the Raspberry Pi uses the same ARGB8888 (COLOR_FORMAT_ARGB32 in Ultibo) format as LVGL */

	/* Render the entire buffer to the display device using DMA */
	framebuffer_device_put_rect(config->display_device, act_x1, act_y1, (void *)px_map, (act_x2 - act_x1 + 1), (act_y2 - act_y1 + 1), 0, FRAMEBUFFER_FLAG_DMA);

	/* Show the cursor if needed */
	if (config->touch_show_cursor)
		framebuffer_device_update_cursor(config->display_device, TRUE, config->touch_last_x, config->touch_last_y, FALSE);

	/* Indicate to LVGL we are ready with the flushing */
	lv_display_flush_ready(disp);
}

/* Initialize the touch configuration and determine touch properties */
static int touch_init_configuration(APP_CONFIG *config)
{
	size_t argument2;

	/* Get default touch device */
	config->touch_device = touch_device_get_default();
	if (config->touch_device)
	{
		/* Set the rotation of the touch device if required */
		if (touch_device_control(config->touch_device, TOUCH_CONTROL_SET_ROTATION, TOUCH_ROTATION_0, &argument2) != ERROR_SUCCESS)
		{
			#ifdef DEBUG
			logging_output("Failed to set rotation for touch device");
			#endif
		}

		/* Get the properties of the touch device */
		if (touch_device_get_properties(config->touch_device, &config->touch_properties) == ERROR_SUCCESS)
		{
			/* Save the maximum X and Y values from the touch device */
			config->touch_max_x = config->touch_properties.maxx;
			config->touch_max_y = config->touch_properties.maxy;

			/* Check if the touch device sends touch or mouse data */
			if (config->touch_properties.flags & TOUCH_FLAG_MOUSE_DATA)
				config->touch_use_mouse = 1;

			/* Don't show the cursor for a touch device */
			config->touch_show_cursor = 0;

		} else {
			/* No touch properties, use mouse instead and show the cursor */
			config->touch_use_mouse = 1;
			config->touch_show_cursor = 1;
		}
	} else {
		/* No touch device, use mouse instead and show the cursor */
		config->touch_use_mouse = 1;
		config->touch_show_cursor = 1;

		/* For USB touch screen devices it may be necessary to delay the configuration 
		 * to allow time for the USB device enumeration, initialization and binding 
		 * process which occurs asynchronously with other boot processing */
		config->touch_config_delay = 1;
	}

	/* Setup last position */
	config->touch_last_x = config->display_width / 2;
	config->touch_last_y = config->display_height / 2;

	/* Enable cursor if needed */
	if (config->touch_show_cursor)
	{
		framebuffer_device_set_cursor(config->display_device, 0, 0, 0, 0, NULL, 0);
		framebuffer_device_update_cursor(config->display_device, TRUE, config->touch_last_x, config->touch_last_y, FALSE);
	}

	#ifdef DEBUG
	logging_output("Touch configuration initialized");
	logging_outputf(" Max X = %d\n", (int)config->touch_max_x);
	logging_outputf(" Max Y = %d\n", (int)config->touch_max_y);
	logging_outputf(" Last X = %d\n", (int)config->touch_last_x);
	logging_outputf(" Last Y = %d\n", (int)config->touch_last_y);
	logging_outputf(" Use Mouse = %d\n", (int)config->touch_use_mouse);
	logging_outputf(" Show Cursor = %d\n", (int)config->touch_show_cursor);
	logging_outputf(" Config Delay = %d\n", (int)config->touch_config_delay);
	#endif

	return 0;
}

/* LVGL touch read callback, called periodically to determine if any touch events have occurred */
static void touch_read_callback(lv_indev_t * indev, lv_indev_data_t * data)
{
	APP_CONFIG *config = (APP_CONFIG *)lv_indev_get_user_data(indev);
	MOUSE_DATA mousedata;
	TOUCH_DATA touchdata;
	double_t scaling_x;
	double_t scaling_y;
	uint32_t status;
	uint32_t count;

	/* Check if configuration was delayed for USB touch devices and if so try
	 * to configure the device now. Once a device is successfully configured
	 * set the touch_config_delay value to 0 so we don't check again
     */
	if (config->touch_config_delay)
	{
		if (!config->touch_device)
		{
			size_t argument2;

			/* Get default touch device */
			config->touch_device = touch_device_get_default();
			if (config->touch_device)
			{
				/* Hide the cursor if previously shown */
				if (config->touch_show_cursor)
					framebuffer_device_update_cursor(config->display_device, FALSE, config->touch_last_x, config->touch_last_y, FALSE);

				/* Reset the touch configuration */
				config->touch_use_mouse = 0;
				config->touch_show_cursor = 0;

				/* Set the rotation of the touch device if required */
				if (touch_device_control(config->touch_device, TOUCH_CONTROL_SET_ROTATION, TOUCH_ROTATION_0, &argument2) != ERROR_SUCCESS)
				{
					#ifdef DEBUG
					logging_output("Failed to set rotation for touch device");
					#endif
				}

				/* Get the properties of the touch device */
				if (touch_device_get_properties(config->touch_device, &config->touch_properties) == ERROR_SUCCESS)
				{
					/* Save the maximum X and Y values from the touch device */
					config->touch_max_x = config->touch_properties.maxx;
					config->touch_max_y = config->touch_properties.maxy;

					/* Check if the touch device sends touch or mouse data */
					if (config->touch_properties.flags & TOUCH_FLAG_MOUSE_DATA)
						config->touch_use_mouse = 1;

					/* Don't show the cursor for a touch device */
					config->touch_show_cursor = 0;

				} else {
					/* No touch properties, use mouse instead and show the cursor */
					config->touch_use_mouse = 1;
					config->touch_show_cursor = 1;
				}

				/* Remove the delayed config marker so no further checks are made */
				config->touch_config_delay = 0;
			}
		} else
			config->touch_config_delay = 0;
	}

	if (config->touch_use_mouse)
	{
		/* Read the mouse data */
		while (1)
		{
			/* Perform a non blocking read from the mouse event queue */
			status = mouse_read_ex(&mousedata, sizeof(MOUSE_DATA), MOUSE_FLAG_NON_BLOCK, &count);

			if (status == ERROR_SUCCESS)
			{

				/* Check for absolute X value */
				if (mousedata.buttons & MOUSE_ABSOLUTE_X)
				{
					scaling_x = (double_t)mousedata.maximumx / (double_t)config->display_width;
					if (scaling_x <= 0.0)
						scaling_x = 1.0;

					config->touch_last_x = (double_t)(mousedata.offsetx / scaling_x);
				} else
					config->touch_last_x += mousedata.offsetx;

				/* Check for X value outside display */
				if (config->touch_last_x < 0)
					config->touch_last_x = 0;
				if (config->touch_last_x >= config->display_width)
					config->touch_last_x = config->display_width - 1;

				/* Check for absolute Y value */
				if (mousedata.buttons & MOUSE_ABSOLUTE_Y)
				{
					scaling_y = (double_t)mousedata.maximumy / (double_t)config->display_height;
					if (scaling_y <= 0.0)
						scaling_y = 1.0;

					config->touch_last_y = (double_t)(mousedata.offsety / scaling_y);
				} else
					config->touch_last_y += mousedata.offsety;

				/* Check for Y value outside display */
				if (config->touch_last_y < 0)
					config->touch_last_y = 0;
				if (config->touch_last_y >= config->display_height)
					config->touch_last_y = config->display_height - 1;

				/* Update the current touch state */
				if (mousedata.buttons & (MOUSE_LEFT_BUTTON | MOUSE_TOUCH_BUTTON))
					data->state = LV_INDEV_STATE_PRESSED;
				else
					data->state = LV_INDEV_STATE_RELEASED;

				/* Update the current touch X and Y */
				data->point.x = config->touch_last_x;
				data->point.y = config->touch_last_y;
			} else  /* if (status = ERROR_NO_MORE_ITEMS) */
				break;
		}
	} else {
		/* Read the touch data */
		while (1)
		{
			/* Perform a non blocking read from the touch device event queue */
			status = touch_device_read(config->touch_device, &touchdata, sizeof(TOUCH_DATA), TOUCH_FLAG_NON_BLOCK, &count);

			if (status == ERROR_SUCCESS)
			{

				/* Check for the first touch point */
				if (touchdata.pointid == 1)
				{

					/* Scale the X value to the display */
					scaling_x = (double_t)config->touch_max_x / (double_t)config->display_width;
					if (scaling_x <= 0.0)
						scaling_x = 1.0;

					config->touch_last_x = (double_t)(touchdata.positionx / scaling_x);

					/* Check for X value outside display */
					if (config->touch_last_x < 0)
						config->touch_last_x = 0;
					if (config->touch_last_x >= config->display_width)
						config->touch_last_x = config->display_width - 1;

					/* Scale the Y value to the display */
					scaling_y = (double_t)config->touch_max_y / (double_t)config->display_height;
					if (scaling_y <= 0.0)
						scaling_y = 1.0;

					config->touch_last_y = (double_t)(touchdata.positiony / scaling_y);

					/* Check for Y value outside display */
					if (config->touch_last_y < 0)
						config->touch_last_y = 0;
					if (config->touch_last_y >= config->display_height)
						config->touch_last_y = config->display_height - 1;

					/* Update the current touch state */
					if (touchdata.info & TOUCH_FINGER)
						data->state = LV_INDEV_STATE_PRESSED;
					else
						data->state = LV_INDEV_STATE_RELEASED;

					/* Update the current touch X and Y */
					data->point.x = config->touch_last_x;
					data->point.y = config->touch_last_y;
				}
			} else  /* if (status = ERROR_NO_MORE_ITEMS) */
				break;
		}
	}

	/* Update the cursor if needed */
	if (config->touch_show_cursor)
		framebuffer_device_update_cursor(config->display_device, TRUE, config->touch_last_x, config->touch_last_y, FALSE);

}

/* LVGL keyboard read callback, called periodically to determine if any keyboard events have occurred */
static void keyboard_read_callback(lv_indev_t * indev, lv_indev_data_t * data)
{
	APP_CONFIG *config = (APP_CONFIG *)lv_indev_get_user_data(indev);
	uint32_t key;
	lv_indev_state_t state;

	/* Check for keypress */
	if (console_keypressed())
	{

		/* Get key press */
		key = (uint8_t)console_read_key();
		if (key != 0)
		{
			/* Store key press */
			data->key =  key;
			data->state = LV_INDEV_STATE_PR;

			#ifdef DEBUG
			logging_outputf("Keyboard key = %d state = %d\n", (int)data->key, (int)data->state);
			#endif

		} else {
			/* Get extended key */
			key = (uint8_t)console_read_key();

			/* Translate extended key */
			switch(key)
			{
				case 0x48 :
					key = LV_KEY_UP;
					state = LV_INDEV_STATE_PR;
					break;
				case 0x50 :
					key = LV_KEY_DOWN;
					state = LV_INDEV_STATE_PR;
					break;
				case 0x4D :
					key = LV_KEY_RIGHT;
					state = LV_INDEV_STATE_PR;
					break;
				case 0x4B :
					key = LV_KEY_LEFT;
					state = LV_INDEV_STATE_PR;
					break;
				//case KEY_CODE_ESCAPE :
				//	key = LV_KEY_ESC;
				//	state = LV_INDEV_STATE_PR;
				//	break;
				case 0x53 :
					key = LV_KEY_DEL;
					state = LV_INDEV_STATE_PR;
					break;
				//case KEY_CODE_BACKSPACE :
				//	key = LV_KEY_BACKSPACE;
				//	state = LV_INDEV_STATE_PR;
				//	break;
				case KEY_CODE_ENTER :
					key = LV_KEY_ENTER;
					state = LV_INDEV_STATE_PR;
					break;
				//case KEY_CODE_TAB :
				//	key = LV_KEY_NEXT;
				//	state = LV_INDEV_STATE_PR;
				//	break;
				case 0x0F :
					key = LV_KEY_PREV;
					state = LV_INDEV_STATE_PR;
					break;
				case 0x47 :
					key = LV_KEY_HOME;
					state = LV_INDEV_STATE_PR;
					break;
				case 0x4F :
					key = LV_KEY_END;
					state = LV_INDEV_STATE_PR;
					break;
				default :
					key = config->keyboard_last_key;
					state = LV_INDEV_STATE_REL;
			}

			/* Store extended key */
			data->key = key;
			data->state = state;

			#ifdef DEBUG
			logging_outputf("Keyboard key = %d state = %d\n", (int)data->key, (int)data->state);
			#endif
		}

		/* Update last key */
		config->keyboard_last_key = key;

	} else {
		/* Store key release */
		data->key = config->keyboard_last_key;
		data->state = LV_INDEV_STATE_REL;

		/* Clear last key */
		config->keyboard_last_key = 0;
	}

}

#ifdef DEBUG
/* Logging callback for LVGL (Debug mode only) */
static void lvgl_logging_output(lv_log_level_t level, const char * buf)
{
	logging_outputf("LVGL: %s", buf);
}
#endif

/* Initialize the LVGL configuration including display, touch and keyboard drivers */
static int lvgl_init_configuration(APP_CONFIG *config)
{

	#ifdef DEBUG
	/* Enable LVGL logging */
	lv_log_register_print_cb(lvgl_logging_output);
	#endif

	/* Initialize LVGL */
	lv_init();

	/* Determine the render buffer size (1/10 of screen size) */
	config->display_buffer_bytes = (config->display_width * config->display_bytes_per_pixel) * (config->display_height * config->display_bytes_per_pixel) / 10;

	/* Allocate render buffers */
	if (dma_available())
	{
		/* If DMA is available allocate compatible buffers */
		config->display_render_buf1 = dma_allocate_buffer(config->display_buffer_bytes);
		#ifdef USE_DISPLAY_DOUBLE_BUFFER
		config->display_render_buf2 = dma_allocate_buffer(config->display_buffer_bytes);
		#else
		config->display_render_buf2 = NULL;
		#endif

	} else {
		/* Allocate standard buffers using malloc */
		config->display_render_buf1 = malloc(config->display_buffer_bytes);
		#ifdef USE_DISPLAY_DOUBLE_BUFFER
		config->display_render_buf2 = malloc(config->display_buffer_bytes);
		#else
		config->display_render_buf2 = NULL;
		#endif
	}

	#ifdef DEBUG
	logging_outputf("LVGL Render Buffers Address 1 = %x Address 2 = %x Size = %d\n", (unsigned int)config->display_render_buf1, (unsigned int)config->display_render_buf2, (int)config->display_buffer_bytes);
	#endif

	/* Initialize the display driver */
	/* Basic initialization, horizontal and vertical resolution */
	config->display_driver = lv_display_create(config->display_width, config->display_height);
	/* Set the callback function */
	lv_display_set_flush_cb(config->display_driver, display_flush_callback);
	/* Assign the draw buffers to the display */
	lv_display_set_buffers(config->display_driver, config->display_render_buf1, config->display_render_buf2, config->display_buffer_bytes, LV_DISPLAY_RENDER_MODE_PARTIAL);
	/* Store our configuration as user data */
    lv_display_set_user_data(config->display_driver, config);
	/* Set the color depth of the display*/
	//lv_display_set_color_depth(state->config.display_driver, LV_COLOR_FORMAT_ARGB8888);

	/* Initialize the touch driver */
	/* Basic initialization*/
	config->touch_driver = lv_indev_create();
	/* Touch pad is a pointer-like device */
	lv_indev_set_type(config->touch_driver, LV_INDEV_TYPE_POINTER);
	/* Set the driver callback function */
	lv_indev_set_read_cb(config->touch_driver, touch_read_callback);
	/* Store our configuration as user data */
	lv_indev_set_user_data(config->touch_driver, config);

	/* Initialize keyboard driver */
	/* Basic initialization */
	config->keyboard_driver = lv_indev_create();
	/* Keyboard is a keypad-like device */
	lv_indev_set_type(config->keyboard_driver, LV_INDEV_TYPE_KEYPAD);
	/* Set the driver callback function */
	lv_indev_set_read_cb(config->keyboard_driver, keyboard_read_callback);
	/* Store our configuration as user data */
	lv_indev_set_user_data(config->keyboard_driver, config);

	#ifdef DEBUG
	logging_output("LVGL configuration initialized");
	#endif

	return 0;
}

/* Forward declarations of event callbacks */
static void button_click(lv_event_t * event);

/* Create a simple LVGL screen to demonstrate some features */
static int lvgl_create_screen(APP_CONFIG *config)
{
	lv_obj_t * current_screen = lv_scr_act();

	/* Setup active screen background color */
	lv_obj_set_style_bg_color(current_screen, lv_color_make(142, 167, 196), LV_PART_MAIN);

	/* Create a text area (and a label) (https://docs.lvgl.io/9.2/widgets/textarea.html) */
	lv_obj_t * text_area = lv_textarea_create(current_screen);
	lv_obj_align(text_area, LV_ALIGN_TOP_LEFT, (double_t)config->display_width * 0.05, (double_t)config->display_height * 0.10);
	lv_textarea_set_one_line(text_area, true);

	lv_obj_t * text_label = lv_label_create(current_screen);
	lv_label_set_text(text_label, "This is a text area, try typing some text");
	lv_obj_set_style_text_color(text_label, lv_color_white(), LV_PART_MAIN);
	lv_obj_align(text_label, LV_ALIGN_TOP_LEFT, (double_t)config->display_width * 0.05, (double_t)config->display_height * 0.05);

	/* Create a checkbox  (https://docs.lvgl.io/9.2/widgets/checkbox.html) */
	lv_obj_t * checkbox = lv_checkbox_create(current_screen);
	lv_obj_align(checkbox, LV_ALIGN_TOP_LEFT, (double_t)config->display_width * 0.05, (double_t)config->display_height * 0.20);
	lv_checkbox_set_text(checkbox, "This is a checkbox");

	/* Create a slide switch (and a label) (https://docs.lvgl.io/9.2/widgets/switch.html) */
	lv_obj_t * slideswitch = lv_switch_create(current_screen);
	lv_obj_align(slideswitch, LV_ALIGN_TOP_LEFT, (double_t)config->display_width * 0.05, (double_t)config->display_height * 0.35);
	lv_obj_add_state(slideswitch, LV_STATE_CHECKED);

	lv_obj_t * switch_label = lv_label_create(current_screen);
	lv_label_set_text(switch_label, "This is a switch");
	lv_obj_set_style_text_color(switch_label, lv_color_white(), LV_PART_MAIN);
	lv_obj_align(switch_label, LV_ALIGN_TOP_LEFT, (double_t)config->display_width * 0.05, (double_t)config->display_height * 0.30);

	/* Create a slider (and a label) (https://docs.lvgl.io/9.2/widgets/slider.html) */
	lv_obj_t * slider = lv_slider_create(current_screen);
	lv_obj_align(slider, LV_ALIGN_TOP_LEFT, (double_t)config->display_width * 0.05, (double_t)config->display_height * 0.50);

	lv_obj_t * slider_label = lv_label_create(current_screen);
	lv_label_set_text(slider_label, "This is a slider");
	lv_obj_set_style_text_color(slider_label, lv_color_white(), LV_PART_MAIN);
	lv_obj_align(slider_label, LV_ALIGN_TOP_LEFT, (double_t)config->display_width * 0.05, (double_t)config->display_height * 0.45);

	/* Create a button (and two labels)  (https://docs.lvgl.io/9.2/widgets/button.html) */
	lv_obj_t * button = lv_btn_create(current_screen);
	lv_obj_set_size(button, (double_t)config->display_width * 0.20, (double_t)config->display_height * 0.10);
	lv_obj_align(button, LV_ALIGN_TOP_LEFT, (double_t)config->display_width * 0.05, (double_t)config->display_height * 0.65);
	lv_obj_set_style_border_width(button, 3, LV_PART_MAIN);
	lv_obj_set_style_border_color(button, lv_color_white(), LV_PART_MAIN);

	lv_obj_t * button_text = lv_label_create(button);
	lv_obj_align(button_text, LV_ALIGN_CENTER, 0, 0);
	lv_label_set_text(button_text, "Start the LVGL Demo");

	lv_obj_t * button_label = lv_label_create(current_screen);
	lv_label_set_text(button_label, "This is a button, click the button to see more of what LVGL can do");
	lv_obj_set_style_text_color(button_label, lv_color_white(), LV_PART_MAIN);
	lv_obj_align(button_label, LV_ALIGN_TOP_LEFT, (double_t)config->display_width * 0.05, (double_t)config->display_height * 0.60);

	/* Create a group and add the objects */
	lv_group_t * group = lv_group_create();
	lv_group_add_obj(group, button);
	lv_group_add_obj(group, text_area);
	lv_group_add_obj(group, checkbox);
	lv_group_add_obj(group, slideswitch);
	lv_group_add_obj(group, slider);
	
	/* Associate the group with the keyboard */
	lv_indev_set_group(config->keyboard_driver, group);

	/* Focus the text area */
	lv_group_focus_obj(text_area);

	/* Register events (https://docs.lvgl.io/9.2/overview/event.html) */
	lv_obj_add_event_cb(button, button_click, LV_EVENT_CLICKED, config);

	return 0;
}

/* LVGL tick thread (See: https://docs.lvgl.io/9.2/porting/tick.html) */
static void * lvgl_tick_thread(void *args)
{
    /* Set the thread name */
	thread_set_name(thread_get_current(), "LVGL Tick");

	while(1)
	{
		/* Sleep for 5 milliseconds */
		usleep(5 * 1000);

		/* Tell LVGL that 5 milliseconds have elapsed */
		lv_tick_inc(5);
	}

	return NULL;
}

/* Evant callback for first button */
static void button_click(lv_event_t * event)
{
	/* Initialize the LVGL widgets demo */
	lv_demo_widgets();
}
