#ifndef _LCD_H_
#define _LCD_H_

/*
 * lcd.c
 * Code to display the ASCII characters on Nokia 5110 LCD display through SPI interface.
 * Have referred to following documents, video and reference material
 * 	# All the documents over here:
 *	# https://www.sparkfun.com/products/10168
 *	
 *	# ASCII character array
 *	# http://playground.arduino.cc/Code/PCD8544
 *
 *	# Following video tutorials:
 *	# This file contains all the demonstartions from the following tutorials, but for beaglebone
 *	# https://www.youtube.com/watch?v=RAlZ1DHw03g	(Tutorial 1)
 *	# https://www.youtube.com/watch?v=E6PUa4n2DnA	(Tutorial 2)
 *	# https://www.youtube.com/watch?v=cwsCxUhHbQM	(Tutorial 3)
 *
 *	# Python library for using Nokia 5110 LCD display with BeagleBone Black
 *	# https://github.com/adafruit/Adafruit_Nokia_LCD
 *
 *	# Linux kernel's SPI documentation (spidev_test.c is of great help)
 *	# https://www.kernel.org/doc/Documentation/spi/
 *	
 *	# To understand usage of Linux kernel's SPI driver
 *	# https://github.com/sparkfun/pcDuino/tree/master/examples/SPI
 *	
 *
 *	# spidev.h of Linux kernel 3.8 to understand ioctls and struct spi_ioc_transfer
 *	# http://lxr.free-electrons.com/source/include/uapi/linux/spi/spidev.h?v=3.8
 *
 *	# Derek Molloys videos:
 * 	# https://www.youtube.com/watch?v=z6b4zlh0IrE&list=PLF4A1A7E09E5E260A
 */

/*
 *	Connections:
 *	-------------------------------------------------
 *	| LCD Pin:	| BBB Pin	| GPIO No.	|
 *	|-----------------------------------------------|
 *	| 1 - VCC	| VCC		| -		|
 *	| 2 - GND	| DGND		| -		|
 *	| 3 - SCE	| P9_17		| 5		|
 *	| 4 - RST	| P9_12		| 60		|
 *	| 5 - D/C	| P9_15		| 48		|
 *	| 6 - DIN(MOSI) | P9_18		| 4		|
 *	| 7 - SCLK	| P9_22		| 2		|
 *	| 8 - LED	| to VCC	| - 		|
 *	-------------------------------------------------
 * 	References:
 *	https://learn.adafruit.com/downloads/pdf/nokia-5110-3310-lcd-python-library.pdf
 *	https://github.com/derekmolloy/boneDeviceTree/blob/master/docs/BeagleboneBlackP9HeaderTable.pdf
 */

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>
#include <assert.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

void lcd_init();
void lcd_deinit();
void clrscr();
void invert_color();
void init_all_segments();
void lcd_write_cmd(uint8_t cmd);
void lcd_write_data(uint8_t data);
int lcd_printf(const char *fmt, ...);

#endif 	//_LCD_H_
