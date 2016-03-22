#ifndef MOTOR_H
#define MOTOR_H

/*
 * motor.h
 *	Declaration of all the configurations, constants,
 *	file paths, variables and forward declarations.
 *
 * Resources:
 * 	* http://oroboto.net/2014/03/29/beaglebone-pwm-motor-control/	// great blog
 *	* https://github.com/mr-oroboto/oroboto				// code from the same author
 *	* https://www.pololu.com/product/2135
 *	* DRV 8835 - datasheet
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 * Pin Configuration
 *	Right Wheel
 *	    (PWM Pin) Pin 9 - P8_13 - GPIO 23
 *	(Digital Pin) Pin 7 - P8_12 - GPIO 44
 *
 *	Left Wheel
 *	   (PWM Pin) Pin 10 - P9_14 - GPIO 50
 *     (Digital Pin)  Pin 8 - P9_23 - GPIO 49
 */

#define	LOW		"0"
#define HIGH		"1"

#define OUT_DIRN	"out"
#define IN_DIRN		"in"

#define STOP		"0"
#define RUN		"1"

/* PWM File Descriptors and Paths */

int fd_p8_13_run;
int fd_p8_13_period;
int fd_p8_13_duty;
int fd_p8_13_polarity;
char *path_p8_13_pwm_dir;

int fd_p9_14_run;
int fd_p9_14_period;
int fd_p9_14_duty;
int fd_p9_14_polarity;
char *path_p9_14_pwm_dir;

/* GPIO File Descriptors */
#define GPIO_EXPORT	 "/sys/class/gpio/export"
#define GPIO_P8_13	"23"
#define GPIO_P8_12	"44"
#define GPIO_P9_14	"50"
#define GPIO_P9_23	"49"

#define GPIO_P8_13_VALUE	"/sys/class/gpio/gpio23/value"
#define GPIO_P8_13_DIRECTION	"/sys/class/gpio/gpio23/direction"
#define GPIO_P8_12_VALUE	"/sys/class/gpio/gpio44/value"
#define GPIO_P8_12_DIRECTION	"/sys/class/gpio/gpio44/direction"
#define GPIO_P9_14_VALUE	"/sys/class/gpio/gpio50/value"
#define GPIO_P9_14_DIRECTION	"/sys/class/gpio/gpio50/direction"
#define GPIO_P9_23_VALUE	"/sys/class/gpio/gpio49/value"
#define GPIO_P9_23_DIRECTION	"/sys/class/gpio/gpio49/direction"

int fd_gpio_p8_13_value;
int fd_gpio_p8_13_direction;
int fd_gpio_p8_12_value;
int fd_gpio_p8_12_direction;
int fd_gpio_p9_14_value;
int fd_gpio_p9_14_direction;
int fd_gpio_p9_23_value;
int fd_gpio_p9_23_direction;

/* Speeds */
#define	MT_MAX_PERIOD	"4000"	/* 4000ns = 250kHZ */
#define MT_SUPERFAST	"100"
#define MT_FAST		"500"
#define MT_NORMAL		"1000"
#define MT_SLOW		"3000"
#define MT_SUPERSLOW	"3500"

/* Directions */
#define ANTICLOCKWISE	"0"
#define CLOCKWISE	"1"
#define	FORWARD		0
#define BACKWARD	1

int current_speed;
int current_direction;

void motor_init();
void move_forward(char *speed);
void move_backward(char *speed);
int set_speed(char *speed);
int set_direction();
void turn_left();
void turn_right();
void stop();
void motor_deinit();

#endif	// MOTOR_H
