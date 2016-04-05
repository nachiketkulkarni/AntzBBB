#include "sender.h"

int
main(int argc, char *argv[])
{
	int num = 2;
	int arr[8] = {0, 0, 0, 0, 0, 0, 1, 1};
	ir_sender_init(argv[1]);
#if 0
//	while(1) {
		test_send_1_bit(0);
		sleep(1);
		test_send_1_bit(0);
		sleep(1);
		test_send_1_bit(1);
		sleep(1);
		test_send_1_bit(1);
		sleep(1);
		test_send_1_bit(0);
		sleep(1);
		test_send_1_bit(1);
		sleep(1);
		test_send_1_bit(0);
		sleep(1);
		test_send_1_bit(1);
//	}
//	while(1) {
//		send(2);
//		send(7);
//	}
//	while (1) {
//		test_send_8_bits(arr);
//	}
#endif

	send_data(8, 61);
	ir_sender_deinit();

	return 0;
}
