#ifndef _SENDER_H_
#define _SENDER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "protocol.h"

/*
 * Pin Configuration
 *	Sender
 *	    (PWM Pin) P9_14 - GPIO 50
 *	Receiver
 *	(Digital Pin) P9_11 - GPIO 30
 *	IR Proximity
 *      (Digital Pin) P9_12 - GPIO 60
 */

void ir_sender_init(char *pwm_p9_14_path);
void send(uint32_t data);
void ir_sender_deinit();
void test_send_8_bits(int *arr);
void test_send_1_bit(int num);
void send_data(int num_bits, uint32_t data);

int fd_p9_14_run;
int fd_p9_14_period;
int fd_p9_14_duty;
int fd_p9_14_polarity;

#endif	// _SENDER_H_
