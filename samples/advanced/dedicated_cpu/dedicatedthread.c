/*
 *
 * Dedicated CPU advanced example project for Ultibo API
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
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

#include "ultibo/platform.h"
#include "ultibo/threads.h"
#include "ultibo/console.h"

volatile uint32_t counter;
WINDOW_HANDLE right_window;

static ssize_t STDCALL dedicated_thread_execute(void * parameter);

/* This is the startup function which creates the dedicated CPU thread and handles all of
 * the setup work to migrate other threads away from the selected CPU. The comments contain
 * a lot of important information, make sure you read them well
 */
void start_dedicated_thread(WINDOW_HANDLE handle)
{
    char name[THREAD_NAME_LENGTH];
    char value[256];

    THREAD_MESSAGE message;
    THREAD_SNAPSHOT *thread_current;
    THREAD_SNAPSHOT *thread_snapshot;

    /* Because parts of Ultibo core like the file system and network start in asynchronous mode
     * we'll stop here for a second just to make sure they are done. You've seen in other examples
     * how to wait for the network to have a valid IP and how to wait for drive C:\ to be ready, 
     * to keep this example simple we'll just sleep for three seconds which should be enough for now
     */
    thread_sleep(3000);

    /* Create another console window so we can track the progress of our thread later */
    right_window = console_window_create(console_device_get_default(), CONSOLE_POSITION_RIGHT, FALSE);

    /* Some initial housekeeping just to be safe, check the number of CPUs available */
    if (cpu_get_count() < 4)
    {
        /* Less than 4 is bad, we can't continue with the example */
        console_window_write_ln(handle, "Error, less than 4 CPUs available");
        return;
    }
    sprintf(value, "CPU count is %u", (unsigned int)cpu_get_count());
    console_window_write_ln(handle, value);

    /* First step is to create a new thread and assign it to the CPU that we want to take
     * over, this is just the same as creating any other thread except we want to explicitly
     * set the CPU for it to run on and also the affinity so that it cannot run on any other CPU.
     * 
     * We can do this in one step by calling the begin_thread_ex() function but we can also do it
     * by using the normal begin_thread() function and then adjusting the CPU and affinity later
     */
    THREAD_HANDLE dedicated_thread = begin_thread(NULL, thread_get_stack_size(thread_get_current()), dedicated_thread_execute, NULL, THREAD_CREATE_NONE, &dedicated_thread);
    
    sprintf(value, "Created dedicated CPU thread with handle %x", (unsigned int)dedicated_thread);
    console_window_write_ln(handle, value);

    /* Let's set the name of our thread so we can see it in the "Thread List" page of web status */
    thread_set_name(dedicated_thread, "Dedicated CPU Thread");
    
    console_window_write_ln(handle, "Set name of thread to \"Dedicated CPU Thread\"");

    /* Now we can set the affinity of our thread to CPU 3 and wait for the scheduler to migrate it for us */
    thread_set_affinity(dedicated_thread, CPU_AFFINITY_3);
    
    sprintf(value, "Set affinity of dedicated CPU thread to CPU %u", CPU_ID_3); //To Do //cpuid_to_string etc from globalconfig
    console_window_write_ln(handle, value);

    /* Migrations happen during context switches, so our thread may not be instantly on the new CPU, instead
     * we check where our thread is and wait for it to migrate if needed
     */
    uint32_t current_cpu = thread_get_cpu(dedicated_thread);
    if (current_cpu != CPU_ID_3)
    {
        sprintf(value, "Thread %x currently on CPU %d", (unsigned int)dedicated_thread, (unsigned int)current_cpu); //To Do //cpuid_to_string etc from globalconfig
        console_window_write_ln(handle, value);

        /* Keep checking until it is migrated */
        while (thread_get_cpu(dedicated_thread) != CPU_ID_3)
            thread_sleep(1000);
    }
    sprintf(value, "Thread %x now on CPU %d", (unsigned int)dedicated_thread, (unsigned int)thread_get_cpu(dedicated_thread)); //To Do //cpuid_to_string etc from globalconfig
    console_window_write_ln(handle, value);

    /* Now we disable thread migrations temporarily so that we don't have threads moving around while we
     * are trying to setup our dedicated CPU, you can see this on the "Scheduler" page in web status
     */
    scheduler_migration_disable();
    
    console_window_write_ln(handle, "Disabled scheduler migration");

    /* We also don't want any more threads created on our dedicated CPU so we need to disable thread 
     * allocation as well but only for that CPU and not the others, if you look in the initunit.pas
     * file you will also see this function being called during initialization. As part of understanding
     * how this process works you should try commenting that out and see the difference when you run the 
     * example again 
     */
    scheduler_allocation_disable(CPU_ID_3);
    
    sprintf(value, "Disabled scheduler allocation for CPU %u", CPU_ID_3); //To Do //cpuid_to_string etc from globalconfig
    console_window_write_ln(handle, value);

    /* Our final step in the process is to migrate all of the other threads away from our dedicated CPU
     * so they are able to continue running without any impact. To do this we need to know what threads
     * are running on CPU 3, we can use the thread_sapshot_create() function to get a current list
     */
 
    /* We also want to count how many threads need to be migrated so we'll start with zero */
    int count = 0;

    /* Then create a thread snapshot, the snapshot contains all of the thread information at a precise 
     * point in time. The real thread information changes hundreds of times per second and so isn't easy
     * to read directly
     */
    thread_snapshot = thread_snapshot_create();
    if (thread_snapshot)
    {
        /* Get the first thread in the snapshot */
        thread_current = thread_snapshot;
        while (thread_current)
        {
            /* Check the handle of the thread to make sure it is not our dedicated CPU thread */
            if (thread_current->handle != dedicated_thread)
            {
                /* Check the CPU to see if it is on CPU 3 */
                if (thread_current->cpu == CPU_ID_3)
                {
                    
                    /* In our normal configuration there are 4 threads on each CPU that we cannot migrate because
                     * they form a special part of the internals of Ultibo core and are needed for the system to
                     * function. That doesn't mean we can't have a dedicated CPU just for our purpose because at 
                     * least 3 of these threads never run and the fourth one is the idle thread which does nothing
                     * except run when no one else is ready.
                     * 
                     * So what are these special threads?
                     * 
                     * 1. The Idle thread, this just runs when no other threads are ready. It also counts CPU 
                     *    utilization so if it doesn't run then our CPU may appear to be 100% in use but that
                     *    is fine because we want to use it for just one purpose anyway.
                     * 
                     * 2. The IRQ thread, on CPU 0 this is actually the thread that started the system in most
                     *    cases but after that it never runs again, on the other CPUs it is the thread that was
                     *    used to start the CPU and again it will never run after that. If you look at the thread
                     *    list in web status you will see the IRQ threads (one for each CPU) are shown as priority
                     *    THREAD_PRIORITY_NONE which means that they are placed on a special thread queue that the
                     *    scheduler never chooses from. The threads are still ready to run but will never be given
                     *    the chance.
                     * 
                     * 3 and 4. The FIQ and SWI threads, these 2 along with the IRQ threads also have a very important 
                     *    role to play in managing the internal operation of Ultibo core. Even though they will never
                     *    run (because they are THREAD_PRIORITY_NONE) their thread handle is used whenever the system
                     *    is executing an interrupt. So when an IRQ is occurring the system will use the handle of the
                     *    IRQ thread, likewise when an FIQ or fast interrupt is occurring the system will use the handle
                     *    of the FIQ thread. In the same way the system uses the SWI thread to perform software interrupts
                     */
                    thread_get_name(thread_current->handle, name, sizeof(name));

                    /* Check for one of the special threads and if it is not then ask it to migrate */
                    if (thread_current->handle == scheduler_get_thread_handle(CPU_ID_3, THREAD_TYPE_IDLE))
                    {
                        /* This is the idle thread, we can't migrate this one */
                        sprintf(value, "Skipping migration of idle thread \"%s\"", name);
                        console_window_write_ln(handle, value);
                    }
                    else if (thread_current->handle == scheduler_get_thread_handle(CPU_ID_3, THREAD_TYPE_IRQ))
                    {
                        /* This one is the IRQ thread and it can't be migrated either */
                        sprintf(value, "Skipping migration of IRQ thread \"%s\"", name);
                        console_window_write_ln(handle, value);
                    }
                    else if (thread_current->handle == scheduler_get_thread_handle(CPU_ID_3, THREAD_TYPE_FIQ))
                    {
                        /* FIQ threads also can't be migrated but they never run so it doesn't matter */
                        sprintf(value, "Skipping migration of FIQ thread \"%s\"", name);
                        console_window_write_ln(handle, value);
                    }
                    else if (thread_current->handle == scheduler_get_thread_handle(CPU_ID_3, THREAD_TYPE_SWI))
                    {
                        /* And the SWI threads are the same so we can ignore them as well */
                        sprintf(value, "Skipping migration of SWI thread \"%s\"", name);
                        console_window_write_ln(handle, value);
                    }
                    else
                    {
                        /* If the thread is not any of those then it must be a normal thread. Ask the scheduler to migrate it
                         * to CPU 0 instead, we could specify any CPU and we could try to round robin them but the scheduler 
                         * will rebalance anyway once we enable migrations again
                         */
                        thread_set_cpu(thread_current->handle, CPU_ID_0);

                        sprintf(value, "Migrating thread \"%s\" to CPU %u", name, CPU_ID_0); //To Do //cpuid_to_string etc from globalconfig
                        console_window_write_ln(handle, value);

                        /* Add one to our migrated thread count */
                        count++;
                    }
                }
            }
            else
            {
                /* No need to migrate our own thread, that wouldn't make any sense! */
                thread_get_name(dedicated_thread, name, sizeof(name));
                sprintf(value, "Skipping migration for \"%s\"", name);
                console_window_write_ln(handle, value);
            }

            /* Get the next thread from the snapshot */
            thread_current = thread_current->next;
        }

        /* Remember to destroy the snapshot when we have finished using it */
        thread_snapshot_destroy(thread_snapshot);
    }

    /* Print the number of threads that we asked to migrate */
    sprintf(value, "Migrated %d threads from CPU %u", count, CPU_ID_0); //To Do //cpuid_to_string etc from globalconfig
    console_window_write_ln(handle, value);

    /* As we saw above, thread migrations happen during context switches. So even though we asked each of 
     * the threads above to migrate they may not neccessarily have done that if they haven't performed a
     * context switch since our request. There are many reasons why a thread might not perform a context
     * switch, the main reason is if the thread is not ready to run because it is waiting or sleeping.
     * 
     * Let's sleep for a second and then quickly run through a new snapshot to check if everyone has migrated
     */
    thread_sleep(1000);

    /* Create the snapshot and reset the count */
    count = 0;
    thread_snapshot = thread_snapshot_create();
    if (thread_snapshot)
    {
        /* Get the first thread */
        thread_current = thread_snapshot;
        while (thread_current)
        {
            /* Check the handle and the CPU */
            if (thread_current->handle != dedicated_thread && thread_current->cpu == CPU_ID_3)
            {
                if (thread_current->handle != scheduler_get_thread_handle(CPU_ID_3, THREAD_TYPE_IDLE) &&
                    thread_current->handle != scheduler_get_thread_handle(CPU_ID_3, THREAD_TYPE_IRQ) &&
                    thread_current->handle != scheduler_get_thread_handle(CPU_ID_3, THREAD_TYPE_FIQ) &&
                    thread_current->handle != scheduler_get_thread_handle(CPU_ID_3, THREAD_TYPE_SWI))
                {
                    /* Add one to our count */
                    count++;
                }
            }

            /* Get the next thread */
            thread_current = thread_current->next;
        }

        /* Destroy the snapshot */
        thread_snapshot_destroy(thread_snapshot);
    }

    /* Check the count to see if any threads have not migrated yet, we won't proceed if there are any.
     *
     * If you are trying the example with the line from the initunit.pas file commented out, then take
     * a look at the "Thread List" to see which threads did not migrate even though we asked them to.
     * 
     * Can you see why they didn't migrate?
     */
    if (count != 0)
    {
        sprintf(value, "Error, %d threads remaining on CPU %u", count, CPU_ID_3); //To Do //cpuid_to_string etc from globalconfig
        console_window_write_ln(handle, value);

        return;
    }
    sprintf(value, "No threads remaining on CPU %u proceeding with example", CPU_ID_3); //To Do //cpuid_to_string etc from globalconfig
    console_window_write_ln(handle, value);

    /* Send a message to our dedicated CPU thread to tell it we are done and it can go ahead */
    memset(&message, 0, sizeof(message));
    thread_send_message(dedicated_thread, &message);
    
    console_window_write_ln(handle, "Sent a message to the dedicated CPU thread");

    /* Enable thread migrations now that we are all done, the scheduler will not touch our dedicated CPU */
    scheduler_migration_enable();

    console_window_write_ln(handle, "Enabled scheduler migration");

    /* Because our dedicated CPU thread won't be able to print on the console, we'll go into a loop here
     * and print the value of the counter variable that it is incrementing. That way you can see just how 
     * many loops it can do in a second
     */
    uint32_t last = 0;
    uint32_t current = 0;
    while (true)
    {
        /* Copy the counter */
        current = counter;

        /* Check if anything has happened */
        if (last != current)
        {
            /* Print the counter value on the right window */
            sprintf(value, "Counter value is %" PRIu32 ",  Difference is %" PRIu32, current, current - last);
            console_window_write_ln(right_window, value);
        }
        last = current;

        /* Wait one second */
        thread_sleep(1000);
    }
}

/* This is the thread function for our dedicated CPU thread, to use this technique
 * you need to understand the rules about what you can and can't do when taking over
 * a CPU for real time use. Again the comments in this function explain many of the
 * things you need to know so read them carefully before using this in your own programs
 */
static ssize_t STDCALL dedicated_thread_execute(void * parameter)
{
    char value[256];
    THREAD_MESSAGE message;

    /* Do a loop while we are not on our dedicated CPU */
    sprintf(value, "Waiting for migration to CPU %u", CPU_ID_3); //To Do //cpuid_to_string etc from globalconfig
    console_window_write_ln(right_window, value);
    while (thread_get_cpu(thread_get_current()) != CPU_ID_3)
        thread_sleep(1000);
    
    /* Wait for a message from the main thread to say we are ready to go */
    console_window_write_ln(right_window, "Waiting for a message from the main thread");
    thread_receive_message(&message);
    console_window_write_ln(right_window, "Received a message, taking control of CPU");

    /* Now that we are in control, let's disable preemption so the scheduler won't
     * interrupt us at all, once we do this we can no longer call any function that
     * will cause our thread to sleep or yield since without preemption the scheduler
     * will not be able to switch back to our thread 
     */
    sprintf(value, "Disabling scheduler preemption on CPU %u", CPU_ID_3); //To Do //cpuid_to_string etc from globalconfig
    console_window_write_ln(right_window, value);

    scheduler_preempt_disable(CPU_ID_3);

    /* Go into our loop doing whatever we want, no one else is here so we can break all the rules!
     *
     * Now that preemption is disabled the scheduler interrupts will still occur but the scheduler
     * will not switch away from our thread. If you look at the "CPU" page in web status while this
     * is happening you will see the CPU utilization runs at 100% for CPU 3
     */
    counter = 0;
    uint64_t start_count = get_tick_count64();
    while (true)
    {
        /* Increment our loop counter */
        counter++;

        /* See how much time has elapsed since we started the loop, 30,000 milliseconds (or 30 seconds)
         * should be enough time for you to see what is happening but you can extend it if you like
         */
        uint64_t current_count = get_tick_count64();
        if (current_count > (start_count + 30000))
            break;

        /* There's no need to sleep on each loop, this is our CPU and no one can tell us what to do.
         *
         * More importantly we must NOT sleep because that would switch to the idle thread and never
         * return to here again
         */
    }

    /* We can switch back and forth between dedicated and standard mode which can be useful to allow
     * using other functions that cannot be called while preemption is disabled. Let's reenable the
     * scheduler preemption and then print something on the console
     */
    scheduler_preempt_enable(CPU_ID_3);

    sprintf(value, "Enabled scheduler preemption on CPU %u", CPU_ID_3); //To Do //cpuid_to_string etc from globalconfig
    console_window_write_ln(right_window, value);

    /* With preemption disabled the scheduler interrupts were still occuring, in a realtime scenario
     * this could still affect our timing because the interrupts happen every 500 microseconds. This
     * time let's disable interrupts completely so the only thing happening on the CPU is our thread.
     * 
     * Remember once we disable interrupts any call to a function that tries to sleep, yield, wait or
     * acquire a lock will most likely deadlock the CPU and never ever ever return!
     * 
     * Do you think you understood that? Read it again just to be sure!
     */
    sprintf(value, "Disabling interrupts and fast interrupts on CPU %u", CPU_ID_3); //To Do //cpuid_to_string etc from globalconfig
    console_window_write_ln(right_window, value);

    disable_fiq();
    disable_irq();

    /* Of course you can reenable interrupts when you need to do something like allocate some memory
     * or read or write to a file. There are a number of choices available, the simplest is just to
     * call enable_fiq() and enable_irq() which will undo the disable from above.
     * 
     * Ultibo also has a several pairs of functions that allow you to recursively disable and enable
     * interrupts without having to count how many times you disabled and then reenable using the same
     * number of calls. The save_irq_fiq() function disables both IRQ and FIQ and then returns a mask
     * to indicate the previous state, when you want to enable again you just pass the mask back to the
     * restore_irq_fiq() function which will only actually reenable if interrupts were previously enabled.
     * 
     * Got that, maybe not but it will make more sense when you need to use it!
     */

    /* Go back to looping and counting, the main thread is still watching so it will continue printing
     * the counter values while we do this as well
     */
    start_count = get_tick_count64();
    while (true)
    {
        /* Increment our loop counter */
        counter++;

        /* Check our tick count for elapsed time */
        uint64_t current_count = get_tick_count64();
        if (current_count > (start_count + 30000))
            break;

        /* No sleeping here, this is a realtime only thread. Seriously you cannot sleep in this
         * scenario, go on try it if you don't believe me and see what happens
         */
    }

    /* That's the end of the example and now you can explore on your own
     * 
     * Remember, in the dedicated CPU scenario there are very strict rules about what functions you can
     * call in Ultibo core.
     * 
     * Pretty much any function that allocates memory is out of the question because the memory manager 
     * uses locks, without memory then most functions are off limits so you need to plan your code in 
     * advance to allocate any memory you might want beforehand or to switch in and out of dedicated
     * mode as required in order to interact with the rest of Ultibo core.
     * 
     * Have fun!
     */
    while (true)
    {
        /* Don't think the counter values per loop were as high as you expected? Try uncommenting this
         * line and see how many loop iterations happen per second with no other code
         *
         * Note that the counter variable has been marked as volatile so this loop doesn't get optimized
         * away by the compiler
         */
        //counter++;
    }

    /* If you really want to see just how fast a single CPU can go, try commenting out the loop above
     * so that the dedicated thread executes this small piece of inline assembler instead. This loop 
     * only contains 3 ARM instructions so it isn't very real world but it does increment and store
     * the value of the counter as many times as it possibly can per second
     */
    #if defined (__arm__)
    asm volatile
    (
        "ldr r3, [%0]\n"
        "loop:\n"
        "add r3, r3, #1\n"
        "str r3, [%0]\n"
        "b loop\n"
        :                 // No Outputs
        : "r" (&counter)  // Input Counter address
        : "r3"            // r3 = Counter value
    );
    #endif

    return 0;
}