/*
 * Copyright (c) 2017 Linaro Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/__assert.h>

/* Stack size for the threads */
#define Bytes 1024
#define THREAD_PRIORITY 1

/* Declare thread stacks statically */
K_THREAD_STACK_DEFINE(thread_A_stack, Bytes * 2);
K_THREAD_STACK_DEFINE(thread_B_stack, Bytes * 2);

/* Declare thread control blocks statically */
struct k_thread thread_A_data;
struct k_thread thread_B_data;

/* Thread entry functions */
extern "C" void thread_A_entry(void *p1, void *p2, void *p3)
{
	while (true)
	{
		printk("Hello from print_task A!\n");
		k_sleep(K_SECONDS(1));
	}
	/* Terminate the thread */
	k_thread_abort(k_current_get());
}

extern "C" void thread_B_entry(void *p1, void *p2, void *p3)
{
	while (true)
	{
		printk("Hello from print_task B!\n");
		k_sleep(K_SECONDS(2));
	}
	/* Terminate the thread */
	k_thread_abort(k_current_get());
}

extern "C" int main(void)
{
	printk("Main thread started\n");

	/* Create threads using statically allocated stacks */
	k_thread_create(&thread_A_data,	 // Pointer to uninitialized struct k_thread
					thread_A_stack,	 // Pointer to the stack space.
					Bytes * 2,		 // Stack size in bytes.
					thread_A_entry,	 // Thread entry function.
					NULL,			 // 1st entry point parameter.
					NULL,			 // 2nd entry point parameter.
					NULL,			 // 3rd entry point parameter.
					THREAD_PRIORITY, // Thread priority.
					0,				 // Thread options.
					K_NO_WAIT);		 // Scheduling delay, or K_NO_WAIT (for no delay).

	k_thread_create(&thread_B_data,	 // Pointer to uninitialized struct k_thread
					thread_B_stack,	 // Pointer to the stack space.
					Bytes * 2,		 // Stack size in bytes.
					thread_B_entry,	 // Thread entry function.
					NULL,			 // 1st entry point parameter.
					NULL,			 // 2nd entry point parameter.
					NULL,			 // 3rd entry point parameter.
					THREAD_PRIORITY, // Thread priority.
					0,				 // Thread options.
					K_NO_WAIT);		 // Scheduling delay, or K_NO_WAIT (for no delay).

	while (true)
	{
		printk("Main thread running\n");
		k_msleep(2000);
	}
	/* Terminate the thread */
	k_thread_abort(k_current_get());
	return 0;
}
