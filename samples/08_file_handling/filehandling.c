/*
 *
 * File Handling example project for Ultibo API
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
#include <dirent.h>
#include <sys/stat.h>

#include "ultibo/platform.h"
#include "ultibo/threads.h"
#include "ultibo/console.h"

int apimain(int argc, char **argv)
{
  DIR *dir;
  char value[512];
  struct dirent *next;
  WINDOW_HANDLE windowhandle;

  /* Create our window */
  windowhandle = console_window_create(console_device_get_default(), CONSOLE_POSITION_FULL, TRUE);

  /* Output the message */
  console_window_write_ln(windowhandle, "Welcome to Example 08 File Handling");
  console_window_write_ln(windowhandle, "");

  /* We may need to wait a couple of seconds for any drive to be ready */
  console_window_write_ln(windowhandle, "Waiting for drive C:\\");
  dir = opendir("C:\\");
  while (!dir)
  {
    /* Sleep for a moment */
    thread_sleep(100);

    dir = opendir("C:\\");
  }
  closedir(dir);
  console_window_write_ln(windowhandle, "C:\\ drive is ready");
  console_window_write_ln(windowhandle, "");
  
  /* First let's list the contents of the SD card. We can guess that it will be C:\ drive for now */
  console_window_write_ln(windowhandle, "Contents of drive C:\\");

  /* To list the contents we need to use opendir/readdir, start with opendir */
  dir = opendir("C:\\");
  if (dir)
  {
    /* If opendir succeeds it will return a handle and we can proceed with the search */
    while ((next = readdir(dir)) != NULL)
    {
      /* Print the file found to the screen */
      sprintf(value, "Filename is %s", next->d_name);
      console_window_write_ln(windowhandle, value);
    }

    /* After a successful call to opendir, you must call closedir or else memory will be leaked */
    closedir(dir);
  }
  console_window_write_ln(windowhandle, "");

  /* Let's try creating a file and writing some text to it, we'll assign our filename to a variable */
  char filename[] = "C:\\Example 08 File Handling.txt";

  /* We should check if the file exists first before trying to create it */
  sprintf(value, "Checking to see if %s exists", filename);
  console_window_write_ln(windowhandle, value);

  struct stat statbuf;
  if (!stat(filename, &statbuf))
  {
    if (statbuf.st_mode & S_IFREG)
    {
      /* If it does exist we can delete it */
      sprintf(value, "Deleting the file %s", filename);
      console_window_write_ln(windowhandle, value);

      remove(filename);
    }
  }
  console_window_write_ln(windowhandle, "");

  /* Now create the file, we pass the filename to fopen and tell it to create the file */
  sprintf(value, "Creating a new file %s", filename);
  console_window_write_ln(windowhandle, value);

  FILE *handle = fopen(filename, "w+");
  if (handle)
  {
    /* We've created the file, now we need to write some content to it, there are many ways
     * to do that but we'll just pass some text to fputs
     */ 
    fputs("Example 08 File Handling\n", handle);
    fputs("This is a test file created by the example\n", handle);
    fputs("Here is a another line of text as well.\n", handle);

    /* With that done we can close the file */
    console_window_write_ln(windowhandle, "Closing the file");
    console_window_write_ln(windowhandle, "");

    fclose(handle);

    /* Did it work? Let's open the file and display it on screen to see */
    sprintf(value, "Opening the file %s", filename);
    console_window_write_ln(windowhandle, value);

    handle = fopen(filename, "r");
    if (handle)
    {
      /* Read the contents of our file */
      console_window_write_ln(windowhandle, "The contents of the file are:");
      
      while (fgets(value, sizeof(value), handle) != NULL)
      {
        console_window_write_ln(windowhandle, value);
      }

      /* Close the file again */
      console_window_write_ln(windowhandle, "Closing the file");
      console_window_write_ln(windowhandle, "");

      fclose(handle);
    }
    else
    {
      /* Something went wrong creating the file */
      sprintf(value, "Failed to open the file %s", filename);
      console_window_write_ln(windowhandle, value);
    }
  }
  else
  {
    /* Something went wrong creating the file */
    sprintf(value, "Failed to create the file %s", filename);
    console_window_write_ln(windowhandle, value);
  }

  /* If you remove the SD card and put in back in your computer, you should see the
   * file "Example 08 File Handling.txt" on it. If you open it in a text editor you
   * should see the contents exactly as they appeared on screen
   */

  /* Halt the thread */
  thread_halt(0);

  return 0;
}
