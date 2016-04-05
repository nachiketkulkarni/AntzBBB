#include "sender.h"

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
pwm_stop_run(char *action)
{
	int w_count;
	w_count = write(fd_p9_14_run, action, strlen(action));
	if (w_count == -1) {
		write_failure(__FILE__, __func__, __LINE__);
	}
}

void
open_pwm_files(char *p9_14_pwm_dir)
{
	char buf[256];
	char *pwm_run = "run";
	char *pwm_period = "period";
	char *pwm_duty = "duty";
	char *pwm_polarity = "polarity";

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
set_pwm_files()
{
	int w_count;

	pwm_stop_run(STOP);

	w_count = write(fd_p9_14_period, MAX_PERIOD, strlen(MAX_PERIOD));
	if (w_count == -1) {
		write_failure(__FILE__, __func__, __LINE__);
	}

	w_count = write(fd_p9_14_duty, DUTY, strlen(DUTY));
	if (w_count == -1) {
		write_failure(__FILE__, __func__, __LINE__);
	}

	return;
}

void
ir_sender_init(char *p9_14_pwm_dir)
{
	open_pwm_files(p9_14_pwm_dir);
	set_pwm_files();
}

void
ir_sender_deinit()
{
	if (fd_p9_14_run) {
		close(fd_p9_14_run);
	}

	if (fd_p9_14_period) {
		close(fd_p9_14_period);
	}

        if (fd_p9_14_duty) {
		close(fd_p9_14_duty);
	}

        if (fd_p9_14_polarity) {
		close(fd_p9_14_polarity);
	}
}

void
test_send_8_bits(int *arr)
{
	int i = 0;
	int num = 0;
	struct timespec sleep_time;
	struct timespec one = {
		.tv_sec = 0,
		.tv_nsec = ONE,
	};

	struct timespec zero = {
		.tv_sec = 0,
		.tv_nsec = ZERO,
	};

	for (i = 0; i < 8; i++) {
		num = arr[i];
		pwm_stop_run(STOP);
		sleep_time = (num == 1 ? one : zero);
		pwm_stop_run(RUN);
		nanosleep(&sleep_time, NULL);
	}
}

void
test_send_1_bit(int num)
{
	struct timespec sleep_time;

	struct timespec one = {
		.tv_sec = 0,
		.tv_nsec = ONE,
	};

	struct timespec zero = {
		.tv_sec = 0,
		.tv_nsec = ZERO,
	};

	sleep_time = (num == 1 ? one : zero);
	pwm_stop_run(STOP);
	pwm_stop_run(RUN);
	nanosleep(&sleep_time, NULL);
	pwm_stop_run(STOP);
}

void
send(uint32_t data)
{
	int i;
	int mask;
	int masked_n;
	int bit;

	struct timespec signature = {
		.tv_sec = 0,
		.tv_nsec = SIGNATURE,
	};

	struct timespec one = {
		.tv_sec = 0,
		.tv_nsec = ONE,
	};

	struct timespec zero = {
		.tv_sec = 0,
		.tv_nsec = ZERO,
	};

	struct timespec nosend = {
		.tv_sec = 0,
		.tv_nsec = NOSEND,
	};

	struct timespec sleep_time;

	uint32_t numbits = 32;

	/* Send message signature */

	pwm_stop_run(RUN);
	nanosleep(&signature, NULL);

	for(i = 0; i < numbits; i++){
		pwm_stop_run(STOP);
		nanosleep(&nosend, NULL);
		mask =  1 << i;
		masked_n = data & mask;
		bit = masked_n >> i;

		sleep_time = (bit == 1 ? one : zero);
		pwm_stop_run(RUN);
		nanosleep(&sleep_time, NULL);
	}

	usleep(3000);		// random delay that gives the receier a leeway to finish processing on the received data
	pwm_stop_run(STOP);
	return;
}

void send_data(int num_bits, uint32_t data)
{
	int i;
	int mask;
	int masked_n;
	int bit;

	struct timespec signature = {
		.tv_sec = 0,
		.tv_nsec = SIGNATURE,
	};

	struct timespec one = {
		.tv_sec = 0,
		.tv_nsec = ONE,
	};

	struct timespec zero = {
		.tv_sec = 0,
		.tv_nsec = ZERO,
	};

	struct timespec nosend = {
		.tv_sec = 0,
		.tv_nsec = NOSEND,
	};

	struct timespec sleep_time;

	pwm_stop_run(RUN);
	nanosleep(&signature, NULL);

	for(i = 0; i < num_bits; ++i){
		pwm_stop_run(STOP);
		nanosleep(&nosend, NULL);
//		sleep(1);
		mask =  1 << i;
		masked_n = data & mask;
		bit = masked_n >> i;

	//	printf("  %d  ", bit);
		sleep_time = (bit == 1 ? one : zero);
		pwm_stop_run(RUN);
		nanosleep(&sleep_time, NULL);
	}

	pwm_stop_run(STOP);
	usleep(3000);		// random delay that gives the receier a leeway to finish processing on the received data
	return;
}
