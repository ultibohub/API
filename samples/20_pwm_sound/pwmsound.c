/*
 *
 * PWM Sound example project for Ultibo API
 * 
 * This example demonstrates using the PWM devices in Ultibo to play audio.
 *
 * The audio file is first loaded from the SD, decoded into a continuous stream
 * of samples and then fed to the PWM FIFO using a DMA request.
 *
 * The example also shows a technique for extending the functionality of an
 * existing Ultibo driver by replacing some of the built in methods.
 *
 * This example is specific to the Raspberry Pi because it uses the PWM device
 * directly instead of using a generic audio device for playback.
 *
 * Once you've tried it out you can create your own samples using tools like
 * Audacity or FFMPEG and modify it to play them instead. You simply need to
 * export the audio as 8 or 16 bit raw PCM in either mono or stereo. The default
 * sample rate is 44100Hz but many other rates will also work.
 * 
 * 
 * This file is part of the Ultibo project, https://ultibo.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2024 Garry Wood <garry@softoz.com.au>
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
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ultibo/platform.h"
#include "ultibo/threads.h"
#include "ultibo/console.h"
#include "ultibo/pwm.h"
#include "ultibo/filesystem.h"

#include "pwmsound.h"

static uint32_t pwmsound_clock_start(PWM_DEVICE * pwm, uint32_t frequency)
{
  uint32_t res = ERROR_INVALID_PARAMETER;
  volatile uint32_t *clock_pwmdiv = (uint32_t *)(BCM283X_CM_REGS_BASE + BCM283X_CM_PWMDIV);
  volatile uint32_t *clock_pwmctl = (uint32_t *)(BCM283X_CM_REGS_BASE + BCM283X_CM_PWMCTL);

  /* Check PWM */
  if (!pwm)
    return res;

  /* Check Frequency */
  if (frequency == 0)
    return res;

  /* Check Enabled */
  if (!bcm27xx_pwm_clock_enabled(pwm))
  {
    /* Get Divisors */
    uint32_t divisori = PWMSOUND_PWM_PLLD_CLOCK / frequency;
    uint32_t divisorr = PWMSOUND_PWM_PLLD_CLOCK % frequency;
    uint32_t divisorf = (divisorr * 4096) / PWMSOUND_PWM_PLLD_CLOCK;

    if (divisori > 4095)
      divisori = 4095;

    /* Memory Barrier */
    data_memory_barrier();

    /* Set Dividers */
    *clock_pwmdiv = BCM283X_CM_PASSWORD | (divisori << 12) | divisorf;
    /* Delay */
    microsecond_delay(10);

    /* Set Source */
    *clock_pwmctl = BCM283X_CM_PASSWORD | BCM283X_CM_CTL_SRC_PLLD;
    /* Delay */
    microsecond_delay(10);

    /* Start Clock */
    *clock_pwmctl = BCM283X_CM_PASSWORD | *clock_pwmctl | BCM283X_CM_CTL_ENAB;
    /* Delay */
    microsecond_delay(10);

    /* Memory Barrier */
    data_memory_barrier();
  }

  /* Return Success */
  res = ERROR_SUCCESS;
  
  return res;
}

static uint32_t pwmsound_start(PWM_DEVICE * pwm)
{
  uint32_t res = ERROR_INVALID_PARAMETER;
  BCM27XX_PWM_DEVICE *bcm27xx_pwm = (BCM27XX_PWM_DEVICE *)pwm;
  volatile BCM283X_PWM_REGISTERS *bcm283x_regs = (BCM283X_PWM_REGISTERS *)bcm27xx_pwm->address;

  /* Check PWM */
  if (!pwm)
    return res;

  /* Check Settings */
  if (pwm->range == 0)
    return res;
  
  if (pwm->frequency == 0)
    return res;

  res = ERROR_OPERATION_FAILED;

  /* Check GPIO */
  if (pwm->gpio == GPIO_PIN_UNKNOWN)
  {
    /* Check Channel */
    switch (bcm27xx_pwm->channel)
    {
      case 0:
        /* Set GPIO 18 */
        if (pwm_device_set_gpio(pwm, GPIO_PIN_18) != ERROR_SUCCESS)
          return res;

        break;
      case 1:
        /* Set GPIO 19 */
        if (pwm_device_set_gpio(pwm, GPIO_PIN_19) != ERROR_SUCCESS) 
          return res;

        break;
      default:
        return res;
    }
  }

  /* Start Clock */
  if (pwmsound_clock_start(pwm, pwm->frequency) != ERROR_SUCCESS)
    return res;

  /* Memory Barrier */
  data_memory_barrier();

  /* Check Channel */
  switch (bcm27xx_pwm->channel)
  {
      case 0:
        /* PWM0 (PWM Channel 1) */
        /* Enable PWEN, USEF and CLRF */
        bcm283x_regs->CTL = bcm283x_regs->CTL | BCM283X_PWM_CTL_PWEN1 | BCM283X_PWM_CTL_USEF1 | BCM283X_PWM_CTL_CLRF1;

        break;
      case 1:
        /* PWM1 (PWM Channel 2) */
        /* Enable PWEN, USEF and CLRF */
        bcm283x_regs->CTL = bcm283x_regs->CTL | BCM283X_PWM_CTL_PWEN2 | BCM283X_PWM_CTL_USEF2 | BCM283X_PWM_CTL_CLRF1;

        break;
      default:
        return res;
  }
  
  /* Clear Status */
  bcm283x_regs->STA = (uint32_t)-1;

  /* Memory Barrier */
  data_memory_barrier();

  /* Return Success */
  res = ERROR_SUCCESS;
  
  return res;
}

static uint32_t pwmsound_set_frequency(PWM_DEVICE * pwm, uint32_t frequency)
{
  uint32_t res = ERROR_INVALID_PARAMETER;
  BCM27XX_PWM_DEVICE *bcm27xx_pwm = (BCM27XX_PWM_DEVICE *)pwm;

  /* Check PWM */
  if (!pwm)
    return res;

  /* Check Frequency */
  if (frequency == 0)
    return res;

  res = ERROR_OPERATION_FAILED;

  /* Check Pair */
  if (bcm27xx_pwm->pair)
  {
    /* Check Enabled */
    if (bcm27xx_pwm->pair->pwm.pwmstate == PWM_STATE_ENABLED)
      return res;
  }

  /* Stop Clock */
  if (bcm27xx_pwm_clock_stop(pwm) != ERROR_SUCCESS)
    return res;

  /* Check Enabled */
  if (pwm->pwmstate == PWM_STATE_ENABLED)
  {
    /* Start Clock */
    if (pwmsound_clock_start(pwm, frequency) != ERROR_SUCCESS)
      return res;
  }

  /* Update Scaler */
  bcm27xx_pwm->scaler = NANOSECONDS_PER_SECOND / frequency;

  /* Update Properties */
  pwm->frequency = frequency;
  pwm->properties.frequency = frequency;

  /* Check Pair */
  if (bcm27xx_pwm->pair)
  {
    /* Update Scaler */
    bcm27xx_pwm->pair->scaler = NANOSECONDS_PER_SECOND / frequency;

    /* Update Properties */
    bcm27xx_pwm->pair->pwm.frequency = frequency;
    bcm27xx_pwm->pair->pwm.properties.frequency = frequency;
  }

  /* Return Success */
  res = ERROR_SUCCESS;
  
  return res;
}

static uint32_t pwmsound_play_sample(PWM_DEVICE * pwm, void *data, uint32_t size, uint32_t channel_count, uint32_t bit_count)
{
  char value[256];
  uint32_t res = ERROR_INVALID_PARAMETER;
  BCM27XX_PWM_DEVICE *bcm27xx_pwm = (BCM27XX_PWM_DEVICE *)pwm;
  volatile BCM283X_PWM_REGISTERS *bcm283x_regs = (BCM283X_PWM_REGISTERS *)bcm27xx_pwm->address;

  /* Check PWM */
  if (!pwm)
    return res;

  /* Check Parameters */
  if (size == 0)
    return res;
  
  if ((channel_count != 1) && (channel_count != 2))
    return res;
  
  if ((bit_count != 8) && (bit_count != 16))
    return res;

  sprintf(value, "Playing %u bytes on %u channel(s) at %u bits per channel", (unsigned int)size, (unsigned int)channel_count, (unsigned int)bit_count);
  console_write_ln(value);

  res = ERROR_OPERATION_FAILED;

  /* Calculate Range Bits */
  uint32_t range_bits = 0;
  uint32_t count = 2;
  while (count < 16)
  {
    if (pwm->range < (1 << count))
    {
      range_bits = count - 1;

      break;
    }

    count++;
  }

  sprintf(value, "Range = %u", (unsigned int)pwm->range);
  console_write_ln(value);
  sprintf(value, "Range Bits = %u", (unsigned int)range_bits);
  console_write_ln(value);

  /* Get Sample Count */
  uint32_t samples = 0;
  if (bit_count == 8)
  {
    samples = size;

    if (channel_count == 1)
      samples *= 2;
  }
  else if (bit_count == 16)
  {
    samples = size / 2;

    if (channel_count == 1)
      samples *= 2;
  }
  if (samples == 0)
    return res;

  /* Allocate Output */
  uint32_t *output = dma_allocate_buffer(samples * sizeof(uint32_t));
  if (!output)
    return res;

  sprintf(value, "Total Samples = %u", (unsigned int)samples);
  console_write_ln(value);

  /* Convert Sound */
  uint8_t *buffer = (uint8_t *)data;
  uint32_t value1, value2;
  uint32_t current = 0;
  count = 0;
  while (count < size)
  {
    /* Get channel 1 */
    value1 = buffer[count];
    count++;
    if (bit_count > 8)
    {
      /* Get 16 bit sample */
      value1 |= buffer[count] << 8;
      count++;
      
      /* Convert to unsigned */
      value1 = (value1 + 0x8000) & 0xffff;
    }

    if (bit_count >= range_bits)
      value1 >>= (bit_count - range_bits);
    else
      value1 <<= (range_bits - bit_count);

    /* Get channel 2 */
    value2 = value1;
    if (channel_count == 2)
    {
      value2 = buffer[count];
      count++;
      if (bit_count > 8)
      {
        /* Get 16 bit sample */
        value2 |= buffer[count] << 8;
        count++;

        /* Convert to unsigned */
        value2 = (value2 + 0x8000) & 0xffff;
      }

      if (bit_count >= range_bits)
        value2 >>= (bit_count - range_bits);
      else
        value2 <<= (range_bits - bit_count);
    }

    /* Store Sample */
    output[current] = value1;
    output[current + 1] = value2;
    current += 2;
  }

  /* Get DMA data */
  DMA_DATA *dma_data = malloc(sizeof(DMA_DATA));
  if (!dma_data)
  {
    /* Free Output */
    dma_release_buffer(output);

    return res;
  }
  dma_data->source = output;
  dma_data->dest = bcm27xx_pwm->address + BCM283X_PWM_FIF1;
  dma_data->size = samples * sizeof(uint32_t);
  dma_data->flags = DMA_DATA_FLAG_DEST_NOINCREMENT | DMA_DATA_FLAG_DEST_DREQ | DMA_DATA_FLAG_LITE;
  dma_data->stridelength = 0;
  dma_data->sourcestride = 0;
  dma_data->deststride = 0;
  dma_data->next = NULL;

  /* Enable DMA */
  bcm283x_regs->DMAC = bcm283x_regs->DMAC | BCM283X_PWM_DMAC_ENAB;

  /* Perform DMA transfer */
  dma_transfer(dma_data, DMA_DIR_MEM_TO_DEV, DMA_DREQ_ID_PWM);
  
  /* Free DMA Data */
  free(dma_data);
  
  /* Free Output */
  dma_release_buffer(output);

  /* Return Success */
  res = ERROR_SUCCESS;
 
  return res;
}

/* Open the supplied file and read the contents into memory for use by pwmsound_play_sample()
 *
 * Note that we show the use of Ultibo filesytem functions here, you could use standard C file
 * functions such as fopen, fread and fclose instead
 */
static uint32_t pwmsound_play_file(PWM_DEVICE * pwm, char *filename, uint32_t channel_count, uint32_t bit_count)
{
  char value[256];
  uint32_t res = ERROR_INVALID_PARAMETER;

  /* Check PWM */
  if (!pwm)
    return res;
  
  /* Check Parameters */
  if (strlen(filename) == 0)
    return res;

  if ((channel_count != 1) && (channel_count != 2))
    return res;
  
  if ((bit_count != 8) && (bit_count != 16))
    return res;

  sprintf(value, "Playing %s on %u channel(s) at %u bits per channel", filename, (unsigned int)channel_count, (unsigned int)bit_count);
  console_write_ln(value);

  /* Wait for SD Card */
  while (!DirectoryExists("C:\\"))
    thread_sleep(100);

  /* Check File */
  if (!FileExists(filename))
    return res;

  res = ERROR_OPERATION_FAILED;

  /* Open File */
  HANDLE handle = FileOpen(filename, fmOpenRead | fmShareDenyNone);
  if (handle == INVALID_HANDLE_VALUE)
    return res;

  /* Check Size */
  if (FileSize(handle) > (100 * 1024 * 1024))
    return res;

  /* Allocate Memory */
  void *buffer = malloc(FileSize(handle));
  if (!buffer)
  {
    /* Close File */
    FileClose(handle);

    return res;
  }

  /* Read File */
  if (FileRead(handle, buffer, FileSize(handle)) == FileSize(handle))
  {
    /* Play Sample */
    res = pwmsound_play_sample(pwm, buffer, FileSize(handle), channel_count, bit_count);
  }

  /* Free Memory */
  free(buffer);

  /* Close File */
  FileClose(handle);

  return res;
}

int apimain(int argc, char **argv)
{
  char value[256];
  WINDOW_HANDLE handle;

  char pwm1_desc[DEVICE_DESC_LENGTH];
  char pwm2_desc[DEVICE_DESC_LENGTH];

  PWM_DEVICE *pwm1_device;
  PWM_DEVICE *pwm2_device;

  /* Create a console window and display a welcome message */
  handle = console_window_create(console_device_get_default(), CONSOLE_POSITION_FULL, TRUE);
  console_window_write_ln(handle, "Welcome to Example 20 PWM Sound");
  console_window_write_ln(handle, "Make sure you have a the Raspberry Pi audio jack connected to the AUX input of an amplifier, TV or other audio device");

  /* First locate the PWM devices
   *
   * The Raspberry Pi A/B/2B/3+/3B have two PWM channels which will normally 
   * end up with the names PWM0 and PWM1 when the driver is included in an
   * application.
   * 
   * The Raspberry Pi 4B/400 have four PWM channels which normally end up with
   * the names PWM2 and PWM3.
   * 
   * For the purpose of this example we'll refer to them just as device 1 and
   * device 2 instead of their actual name.
   * 
   * As with the PWM control example we use pwm_device_find_by_description()
   * to locate the devices and use pwm_get_description() to determine the
   * correct value to pass regardless of the board or configuration.
   * 
   * We've also defined all the details that differ between models in a header
   * file named pwmsound.h so we can just refer to those definitions instead
   * of including a lot of ifdef statements in the source code.
   */

  /* Get the PWM device descriptions */
  pwm_get_description(PWMSOUND_PWM1_ID, PWMSOUND_PWM1_CH, pwm1_desc, sizeof(pwm1_desc));
  pwm_get_description(PWMSOUND_PWM2_ID, PWMSOUND_PWM2_CH, pwm2_desc, sizeof(pwm2_desc));

  /* Find the PWM devices */
  pwm1_device = pwm_device_find_by_description(pwm1_desc);
  pwm2_device = pwm_device_find_by_description(pwm2_desc);
  if (pwm1_device && pwm2_device)
  {
    /* Modify PWM device functions.
     *
     * This allows us to change the behaviour of the PWM driver so we can 
     * use a different clock source and enable the FIFO for audio output.
     * 
     * Notice how we use the same function for both devices, the PWM device
     * instance is passed to the function so it knows which device to use
     */
    pwm1_device->devicestart = pwmsound_start;
    pwm1_device->devicesetfrequency = pwmsound_set_frequency;
    pwm2_device->devicestart = pwmsound_start;
    pwm2_device->devicesetfrequency = pwmsound_set_frequency;

    /* Setup PWM device 1 */
    /* Set the GPIO */
    pwm_device_set_gpio(pwm1_device, PWMSOUND_PWM1_GPIO);
    /* Set the range */
    pwm_device_set_range(pwm1_device, (CLOCK_RATE + (SAMPLE_RATE / 2)) / SAMPLE_RATE);
    /* And the mode to PWM_MODE_BALANCED */
    pwm_device_set_mode(pwm1_device, PWM_MODE_BALANCED);
    /* Finally set the frequency */
    pwm_device_set_frequency(pwm1_device, CLOCK_RATE);

    /* Setup PWM device 2 */
    /* Use exactly the same settings as PWM1 except the GPIO is different */
    pwm_device_set_gpio(pwm2_device, PWMSOUND_PWM2_GPIO);
    pwm_device_set_range(pwm2_device, (CLOCK_RATE + (SAMPLE_RATE / 2)) / SAMPLE_RATE);
    pwm_device_set_mode(pwm2_device, PWM_MODE_BALANCED);
    pwm_device_set_frequency(pwm2_device, CLOCK_RATE);
    
    sprintf(value, "Range = %u", (unsigned int)pwm1_device->range);
    console_window_write_ln(handle, value);

    /* Start the PWM devices */
    if ((pwm_device_start(pwm1_device) == ERROR_SUCCESS) && (pwm_device_start(pwm2_device) == ERROR_SUCCESS))
    {
      /* Play the Sound Sample.
       * 
       * If you change the file to play a different sample make sure you adjust
       * the sample rate, channel count and number of bits to match your sample
       */
      if (pwmsound_play_file(pwm1_device, "a2002011001-e02.pcm", SOUND_CHANNELS, SOUND_BITS) != ERROR_SUCCESS)
      {
        console_window_write_ln(handle, "Error: Failed to play sound file");
      }
      else
      {
        console_window_write_ln(handle, "Finished playing sound sample");
      }

      /* Stop the PWM devices */
      pwm_device_stop(pwm1_device);
      pwm_device_stop(pwm2_device);
    }
    else
    {
      console_window_write_ln(handle, "Error: Failed to start PWM devices");
    }
  }
  else
  {
    console_window_write_ln(handle, "Error: Failed to locate PWM devices");
  }
  
  /* Turn on the LED to indicate completion */
  activity_led_enable();
  activity_led_on();

  /* Halt the thread if we return */
  thread_halt(0);
  
  return 0;
}
