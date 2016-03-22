/*
 * test_lcd.c
 *	A test suit to test functionality of Nokia 5110 LCD.
 */
#include "lcd.h"
#include <sys/time.h>
#include <time.h>

char *ret_time_str()
{
	struct timeval tv;
        time_t nowtime;
        struct tm *nowtm;
        char tmbuf[64];
	char *buf = calloc(1, 64);
	if (buf == NULL) {
		fprintf(stderr, "calloc() failed for buf\n");
	}
 
        gettimeofday(&tv, NULL);
        nowtime = tv.tv_sec;
        nowtm = localtime(&nowtime);
        strftime(tmbuf, sizeof tmbuf, "%Y-%m-%d %H:%M:%S", nowtm);
        snprintf(buf, 64, "%s.%06d", tmbuf, tv.tv_usec);

	return buf;
}

int main()
{
	int ret;
	int i = 0;
	
	lcd_init();
	init_all_segments();
	sleep(3);

	//init();
	clrscr();
	for(i = 0; i < 10; i++) {
		lcd_printf("I am not here: %d", i);
		sleep(1);
	}

/*	
	while(1) {						//Tutorial 2
		lcd_write_data(0x55);
		lcd_write_data(0xAA);
	}
*/

/*	
	while(1) {						//Tutorial 2
		lcd_write_data(0xFE);
	}
*/

/*
	while(1) {						//Tutorial 2 
		lcd_write_data(0x01);
		lcd_write_data(0x03);
		lcd_write_data(0x08);
		lcd_write_data(0x30);
		lcd_write_data(0x80);
		usleep(2);
	}
*/

/*	lcd_write_char(0x41); */				//Tutorial 2

/*	lcd_write_str("Hello"); */				//Tutorial 2
	
//	for (i = 0; i < 504; i++) {	// clear lcd screen	//Tutorial 2
//		lcd_write_data(0x00);
//	}

  // 	lcd_write_str("THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG");	//Tutorial 2


//	lcd_set_coordinates(20, 2);				//Tutorial 2
//	lcd_write_str("The End");
//	invert_color();
// An example similar to the potentiometer example from Tutorial 3. It prints current time of the day.
//	lcd_set_coordinates(0, 0);
//	lcd_write_str("Current Time: ");
	
//	lcd_set_coordinates(0, 2);
//	lcd_write_str(ret_time_str());

	lcd_deinit();
	return 0;
}
