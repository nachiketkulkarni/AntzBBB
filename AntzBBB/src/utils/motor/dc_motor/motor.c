/*
 * motor.c
 *	Imlementation of all the required functions to carry out
 *	smooth functioning of the DC Motor
 */

#include "motor.h"

void
write_failure (const char *file, const char *func, int line)
{
	fprintf(stderr, "write() failed\n");
	fprintf(stderr, "%s :: %s :: %d\n", file, func, line);
	exit(EXIT_FAILURE);
}

void
open_failure (const char *file, const char *func, int line)
{
	fprintf(stderr, "open() failed\n");
	fprintf(stderr, "%s :: %s :: %d\n", file, func, line);
	exit(EXIT_FAILURE);
}

void
open_pwm_files(char *p8_13_pwm_dir, char *p9_14_pwm_dir)
{
	char buf[256];
	char *pwm_run = "run";
	char *pwm_period = "period";
	char *pwm_duty = "duty";
	char *pwm_polarity = "polarity";

	/* Open "run" of p8_13 */
	memset(buf, 0, 256);
	strncpy(buf, p8_13_pwm_dir, strlen(p8_13_pwm_dir));
	strncat (buf, pwm_run, strlen(pwm_run));
	fd_p8_13_run = open(buf, O_WRONLY);
	printf("%s\n", buf);
	if (fd_p8_13_run == -1) {
		open_failure(__FILE__, __func__, __LINE__);
	}

	/* Open "period" of p8_13 */
	memset(buf, 0, 256);
	strncpy(buf, p8_13_pwm_dir, strlen(p8_13_pwm_dir));
	strncat (buf, pwm_period, strlen(pwm_period));
	fd_p8_13_period = open(buf, O_WRONLY);
	if (fd_p8_13_period == -1) {
		open_failure(__FILE__, __func__, __LINE__);
	}

	/* Open "duty" of p8_13 */
	memset(buf, 0, 256);
	strncpy(buf, p8_13_pwm_dir, strlen(p8_13_pwm_dir));
	strncat (buf, pwm_duty, strlen(pwm_duty));
	fd_p8_13_duty = open(buf, O_WRONLY);
	if (fd_p8_13_duty == -1) {
		open_failure(__FILE__, __func__, __LINE__);
	}

	/* Open "polarity" of p8_13 */
	memset(buf, 0, 256);
	strncpy(buf, p8_13_pwm_dir, strlen(p8_13_pwm_dir));
	strncat (buf, pwm_polarity, strlen(pwm_polarity));
	fd_p8_13_polarity = open(buf, O_WRONLY);
	if (fd_p8_13_polarity == -1) {
		open_failure(__FILE__, __func__, __LINE__);
	}

	/* Open "run" of p9_14 */
	memset(buf, 0, 256);
	strncpy(buf, p9_14_pwm_dir, strlen(p9_14_pwm_dir));
	strncat (buf, pwm_run, strlen(pwm_run));
	fd_p9_14_run = open(buf, O_WRONLY);
	if (fd_p9_14_run == -1) {
		open_failure(__FILE__, __func__, __LINE__);
	}

	/* Open "period" of p9_14 */
	memset(buf, 0, 256);
	strncpy(buf, p9_14_pwm_dir, strlen(p9_14_pwm_dir));
	strncat (buf, pwm_period, strlen(pwm_period));
	fd_p9_14_period = open(buf, O_WRONLY);
	if (fd_p9_14_period == -1) {
		open_failure(__FILE__, __func__, __LINE__);
	}

	/* Open "duty" of p9_14 */
	memset(buf, 0, 256);
	strncpy(buf, p9_14_pwm_dir, strlen(p9_14_pwm_dir));
	strncat (buf, pwm_duty, strlen(pwm_duty));
	fd_p9_14_duty = open(buf, O_WRONLY);
	if (fd_p9_14_duty == -1) {
		open_failure(__FILE__, __func__, __LINE__);
	}

	/* Open "polarity" of p9_14 */
	memset(buf, 0, 256);
	strncpy(buf, p9_14_pwm_dir, strlen(p9_14_pwm_dir));
	strncat (buf, pwm_polarity, strlen(pwm_polarity));
	fd_p9_14_polarity = open(buf, O_WRONLY);
	if (fd_p9_14_polarity == -1) {
		open_failure(__FILE__, __func__, __LINE__);
	}

	return;
}

void
open_gpio_files()
{
	int w_count;
	int fd_gpio_export;
	char *gpio_p8_13_dir = "/sys/class/gpio/gpio23";
	char *gpio_p8_12_dir = "/sys/class/gpio/gpio44";
	char *gpio_p9_14_dir = "/sys/class/gpio/gpio50";
	char *gpio_p9_23_dir = "/sys/class/gpio/gpio49";

	/* Export required GPIO channels */
	fd_gpio_export = open(GPIO_EXPORT, O_WRONLY);
	if (fd_gpio_export == -1) {
		open_failure(__FILE__, __func__, __LINE__);
	}

	if (access(gpio_p8_13_dir, R_OK | W_OK) == -1) {
		w_count = write(fd_gpio_export, GPIO_P8_13, strlen(GPIO_P8_13));
		if (w_count == -1) {
			write_failure(__FILE__, __func__, __LINE__);
		}
	}

	if (access(gpio_p8_12_dir, R_OK | W_OK) == -1) {
		w_count = write(fd_gpio_export, GPIO_P8_12, strlen(GPIO_P8_12));
		if (w_count == -1) {
			write_failure(__FILE__, __func__, __LINE__);
		}
	}

	if (access(gpio_p9_14_dir, R_OK | W_OK) == -1) {
		w_count = write(fd_gpio_export, GPIO_P9_14, strlen(GPIO_P9_14));
		if (w_count == -1) {
			write_failure(__FILE__, __func__, __LINE__);
		}
	}

	if (access(gpio_p9_23_dir, R_OK | W_OK) == -1) {
		w_count = write(fd_gpio_export, GPIO_P9_23, strlen(GPIO_P9_23));
		if (w_count == -1) {
			write_failure(__FILE__, __func__, __LINE__);
		}
	}

	/* Open value and direction files of all gpio channels */
	fd_gpio_p8_13_value = open(GPIO_P8_13_VALUE, O_WRONLY);
	if (fd_gpio_p8_13_value == -1) {
		open_failure(__FILE__, __func__, __LINE__);
	}

	fd_gpio_p8_13_direction = open(GPIO_P8_13_DIRECTION, O_WRONLY);
	if (fd_gpio_p8_13_direction == -1) {
		open_failure(__FILE__, __func__, __LINE__);
	}

	fd_gpio_p8_12_value = open(GPIO_P8_12_VALUE, O_WRONLY);
	if (fd_gpio_p8_12_value == -1) {
		open_failure(__FILE__, __func__, __LINE__);
	}

	fd_gpio_p8_12_direction = open(GPIO_P8_12_DIRECTION, O_WRONLY);
	if (fd_gpio_p8_12_direction == -1) {
		open_failure(__FILE__, __func__, __LINE__);
	}

	fd_gpio_p9_14_value = open(GPIO_P9_14_VALUE, O_WRONLY);
	if (fd_gpio_p9_14_value == -1) {
		open_failure(__FILE__, __func__, __LINE__);
	}

	fd_gpio_p9_14_direction = open(GPIO_P9_14_DIRECTION, O_WRONLY);
	if (fd_gpio_p9_14_direction == -1) {
		open_failure(__FILE__, __func__, __LINE__);
	}

	fd_gpio_p9_23_value = open(GPIO_P9_23_VALUE, O_WRONLY);
	if (fd_gpio_p9_23_value == -1) {
		open_failure(__FILE__, __func__, __LINE__);
	}

	fd_gpio_p9_23_direction = open(GPIO_P9_23_DIRECTION, O_WRONLY);
	if (fd_gpio_p9_23_direction == -1) {
		open_failure(__FILE__, __func__, __LINE__);
	}

	if (fd_gpio_export) {
		close(fd_gpio_export);
	}
}

void
set_gpio_directions()
{
	int w_count;

	w_count = write(fd_gpio_p8_13_direction, OUT_DIRN, strlen(OUT_DIRN));
	if (w_count == -1) {
		write_failure(__FILE__, __func__, __LINE__);
	}

	w_count = write(fd_gpio_p8_12_direction, OUT_DIRN, strlen(OUT_DIRN));
	if (w_count == -1) {
		write_failure(__FILE__, __func__, __LINE__);
	}

	w_count = write(fd_gpio_p9_14_direction, OUT_DIRN, strlen(OUT_DIRN));
	if (w_count == -1) {
		write_failure(__FILE__, __func__, __LINE__);
	}

	w_count = write(fd_gpio_p9_23_direction, OUT_DIRN, strlen(OUT_DIRN));
	if (w_count == -1) {
		write_failure(__FILE__, __func__, __LINE__);
	}
	return;
}

void
set_pwm_files()
{
	int w_count;

	w_count = write(fd_p8_13_run, STOP, strlen(STOP));
	if (w_count == -1) {
		write_failure(__FILE__, __func__, __LINE__);
	}

	w_count = write(fd_p9_14_run, STOP, strlen(STOP));
	if (w_count == -1) {
		write_failure(__FILE__, __func__, __LINE__);
	}

	w_count = write(fd_p8_13_period, MT_MAX_PERIOD, strlen(MT_MAX_PERIOD));
	if (w_count == -1) {
		write_failure(__FILE__, __func__, __LINE__);
	}

	w_count = write(fd_p9_14_period, MT_MAX_PERIOD, strlen(MT_MAX_PERIOD));
	if (w_count == -1) {
		write_failure(__FILE__, __func__, __LINE__);
	}

	w_count = write(fd_p8_13_duty, MT_SUPERSLOW, strlen(MT_SUPERSLOW));
	if (w_count == -1) {
		write_failure(__FILE__, __func__, __LINE__);
	}

	w_count = write(fd_p9_14_duty, MT_SUPERSLOW, strlen(MT_SUPERSLOW));
	if (w_count == -1) {
		write_failure(__FILE__, __func__, __LINE__);
	}

	w_count = write(fd_p8_13_run, RUN, strlen(RUN));
	if (w_count == -1) {
		write_failure(__FILE__, __func__, __LINE__);
	}

	w_count = write(fd_p9_14_run, RUN, strlen(RUN));
	if (w_count == -1) {
		write_failure(__FILE__, __func__, __LINE__);
	}

	return;
}

void
motor_init(char *p8_13_pwm_dir, char *p9_14_pwm_dir)
{
	open_pwm_files(p8_13_pwm_dir, p9_14_pwm_dir);
	open_gpio_files();

	set_gpio_directions();
	set_pwm_files();
}

int
set_speed(char *speed_str)
{
	int speed;
	int w_count;
	int superfast;
	int max_period;

	speed = atoi(speed_str);
	superfast = atoi(MT_SUPERFAST);
	max_period = atoi(MT_MAX_PERIOD);
	if (speed <= superfast || speed >= max_period) {
		fprintf(stderr, "*** WARNING: speed range = 1 to 3999\n");
		fprintf(stderr, "Numerically higher value means slower speed\n");
		return 1;
	}

	w_count = write(fd_p8_13_duty, speed_str, strlen(speed_str));
	if (w_count == -1) {
		write_failure(__FILE__, __func__, __LINE__);
	}

	w_count = write(fd_p9_14_duty, speed_str, strlen(speed_str));
	if (w_count == -1) {
		write_failure(__FILE__, __func__, __LINE__);
	}

	return 0;
}

int
set_direction(int dir)
{
	int w_count;
	int res = 0;

	switch(dir) {
		case FORWARD:
			w_count = write(fd_gpio_p8_12_value, ANTICLOCKWISE, strlen(ANTICLOCKWISE));
			if (w_count == -1) {
				write_failure(__FILE__, __func__, __LINE__);
			}

			w_count = write(fd_gpio_p9_23_value, ANTICLOCKWISE, strlen(ANTICLOCKWISE));
			if (w_count == -1) {
				write_failure(__FILE__, __func__, __LINE__);
			}
			break;

		case BACKWARD:
			w_count = write(fd_gpio_p8_12_value, CLOCKWISE, strlen(CLOCKWISE));
			if (w_count == -1) {
				write_failure(__FILE__, __func__, __LINE__);
			}

			w_count = write(fd_gpio_p9_23_value, CLOCKWISE, strlen(CLOCKWISE));
			if (w_count == -1) {
				write_failure(__FILE__, __func__, __LINE__);
			}
			break;
		default:
			fprintf(stderr, "*** WARNING: Incorrectdirection\n");
			res = 1;
			break;
	}

	return res;
}

void
move_forward(char *speed_str)
{
	int ret;
	int arg_speed;
	int speed;
	char arg_speed_str[10];

	speed = atoi(speed_str);
	ret = set_direction(FORWARD);
	current_direction = ret == 0 ? FORWARD : current_direction;

	arg_speed = speed == -1 ? current_speed : speed;

	memset(arg_speed_str, 0, 10);
	sprintf(arg_speed_str, "%d", arg_speed);
	ret = set_speed(arg_speed_str);
	current_speed = ret == 0 ? speed : current_speed;

	return;
}

void
move_backward(char *speed_str)
{
	int ret;
	int arg_speed;
	int speed;
	char arg_speed_str[10];

	speed = atoi(speed_str);
	ret = set_direction(BACKWARD);
	current_direction = ret == 0 ? BACKWARD : current_direction;

	arg_speed = speed == -1 ? current_speed : speed;
	memset(arg_speed_str, 0, 10);
	sprintf(arg_speed_str, "%d", arg_speed);
	ret = set_speed(arg_speed_str);
	current_speed = ret == 0 ? speed : current_speed;

	return;
}

void
stop()
{
	int w_count;

	w_count = write(fd_p8_13_run, STOP, strlen(STOP));
	if (w_count == -1) {
		write_failure(__FILE__, __func__, __LINE__);
	}

	w_count = write(fd_p9_14_run, STOP, strlen(STOP));
	if (w_count == -1) {
		write_failure(__FILE__, __func__, __LINE__);
	}
}

void
start()
{
	int w_count;

	w_count = write(fd_p8_13_run, RUN, strlen(RUN));
	if (w_count == -1) {
		write_failure(__FILE__, __func__, __LINE__);
	}

	w_count = write(fd_p9_14_run, RUN, strlen(RUN));
	if (w_count == -1) {
		write_failure(__FILE__, __func__, __LINE__);
	}
}

void
turn_left()
{
	int w_count;
	struct timespec ts = {
		.tv_sec = 2,
		.tv_nsec = 10000000,
	};
	stop();

	w_count = write(fd_p9_14_duty, MT_SLOW, strlen(MT_SLOW));
	if (w_count == -1) {
		write_failure(__FILE__, __func__, __LINE__);
	}

	w_count = write(fd_p8_13_duty, MT_MAX_PERIOD, strlen(MT_MAX_PERIOD));
	if (w_count == -1) {
		write_failure(__FILE__, __func__, __LINE__);
	}
	start();

	nanosleep(&ts, NULL);

	set_speed(MT_SUPERSLOW);

	return;
}

void
turn_right()
{
	int w_count;
	struct timespec ts = {
		.tv_sec = 2,
		.tv_nsec = 10000000,
	};
	stop();

	w_count = write(fd_p8_13_duty, MT_SLOW, strlen(MT_SLOW));
	if (w_count == -1) {
		write_failure(__FILE__, __func__, __LINE__);
	}

	w_count = write(fd_p9_14_duty, MT_MAX_PERIOD, strlen(MT_MAX_PERIOD));
	if (w_count == -1) {
		write_failure(__FILE__, __func__, __LINE__);
	}
	start();

	nanosleep(&ts, NULL);

	set_speed(MT_SUPERSLOW);

	return;
}

void
motor_deinit()
{
	if(fd_p8_13_run) {
		close(fd_p8_13_run);
	}

	if(fd_p8_13_period) {
		close(fd_p8_13_period);
	}

	if(fd_p8_13_duty) {
		close(fd_p8_13_duty);
	}

	if(fd_p8_13_polarity) {
		close(fd_p8_13_polarity);
	}

	if(fd_p9_14_run) {
		close(fd_p9_14_run);
	}

	if(fd_p9_14_period) {
		close(fd_p9_14_period);
	}

	if(fd_p9_14_duty) {
		close(fd_p9_14_duty);
	}

	if(fd_p9_14_polarity) {
		close(fd_p9_14_polarity);
	}

	if(fd_gpio_p8_13_value){
		close(fd_gpio_p8_13_value);
	}

	if(fd_gpio_p8_13_direction){
		close(fd_gpio_p8_13_direction);
	}

	if(fd_gpio_p8_12_value){
		close(fd_gpio_p8_12_value);
	}

	if(fd_gpio_p8_12_direction){
		close(fd_gpio_p8_12_direction);
	}

	if(fd_gpio_p9_14_value){
		close(fd_gpio_p9_14_value);
	}

	if(fd_gpio_p9_14_direction){
		close(fd_gpio_p9_14_direction);
	}

	if(fd_gpio_p9_23_value){
		close(fd_gpio_p9_23_value);
	}

	if(fd_gpio_p9_23_direction){
		close(fd_gpio_p9_23_direction);
	}

	return;
}
