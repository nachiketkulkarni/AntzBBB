#include "motor.h"

void
print_usage(char *argv)
{
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "./%s <P8_13_pwm_dir> <P9_14_pwm_dir>\n");
}

int
main(int argc, char *argv[])
{
	if (argc < 3) {
		print_usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	motor_init(argv[1], argv[2]);

	move_forward(MT_SLOW);
	sleep(2);
	turn_left();
	sleep(2);
	turn_right();
	sleep(2);
//	move_forward(MT_NORMAL);
//	sleep(2);
//	set_speed(MT_SUPERSLOW);
//	sleep(2);
//	move_backward(MT_SLOW);
//	sleep(2);
	stop();
	motor_deinit();
	return 0;
}

