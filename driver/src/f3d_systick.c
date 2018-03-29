/* f3d_systick.c --- 
 * 
 * Filename: f3d_systick.c
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: 
 * Created: Thu Nov 14 07:57:37 2013
 * Last-Updated: 
 *           By: 
 *     Update #: 0
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */

/* Copyright (c) 2004-2007 The Trustees of Indiana University and 
 * Indiana University Research and Technology Corporation.  
 * 
 * All rights reserved. 
 * 
 * Additional copyrights may follow 
 */

/* Code: */

/* Author: Dylan Wright
 *
 */

#include <f3d_systick.h>
#include <f3d_led.h> 
#include <f3d_button.h>
#include <f3d_uart.h>

volatile int systick_flag = 0;

/*
 * Function to setup the initial rate of the timer
 * pass the number of interrupts per second in as the divsor to the SysTick_Config function
 */
void f3d_systick_init(void) {
}

/*
 * called on each interrupt
 * clears the pending interrupt from the systick timer
 */
void SysTick_Handler(void) {
}

/* f3d_systick.c ends here */
