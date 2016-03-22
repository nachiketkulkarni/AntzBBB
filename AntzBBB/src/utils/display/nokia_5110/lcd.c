/*
 * lcd.c
 *	Implementation of core utilities required for displaying desired string on Nokia 5110 LCD
 */
#include "lcd.h"

#include <malloc.h>
#include <string.h>

#include "font.h"

#define RST 12
#define DC 15
#define CS 17
#define DIN 18
#define CLK 22

#define LINES_IN_SCREEN	5
#define LINE_BUF_SIZE	14
#define SCREEN_BUF_SIZE	84 
#define min(a, b)	(a <= b ? a : b)

/* File descriptors */
int fd_rst_dir;
int fd_rst_val;
int fd_dc_dir;
int fd_dc_val;
int fd_cs_dir;
int fd_cs_val;
int fd_din_dir;
int fd_din_val;
int fd_clk_dir;
int fd_clk_val;
int fd_spi_dev;

/* SPI device and its attributes */
static const char *device = "/dev/spidev1.0";
static uint8_t bits = 8;
static uint32_t speed = 4000000;
static uint16_t delay = 0;
static int verbose;

int screen_buf_pos = 0;
int next_y_pos = 0;
char screen_buffer[84];

void lcd_write_cmd(uint8_t cmd);

/*
 * init_export()
 *	Function to export required GPIO pins
 */
void
init_export()
{
	int fd_export;
	ssize_t size;
	
	fd_export = open("/sys/class/gpio/export", O_WRONLY);
	if (fd_export == -1) {
		fprintf(stderr, "open() failed for export\n");
		exit(EXIT_FAILURE);
	}

	if ((access("/sys/class/gpio/gpio60", R_OK | W_OK)) == -1) {
		size = write(fd_export, "60", strlen("60"));
		if (size == -1) {
			fprintf(stderr, "write() failed for export\n");
			exit(EXIT_FAILURE);
		}
	}
	
	if ((access("/sys/class/gpio/gpio48", R_OK | W_OK)) == -1) {
		size = write(fd_export, "48", strlen("48"));
		if (size == -1) {
			fprintf(stderr, "write() failed for export\n");
			exit(EXIT_FAILURE);
		}
	}
	
	if ((access("/sys/class/gpio/gpio5", R_OK | W_OK)) == -1) {
		size = write(fd_export, "5", strlen("5"));
		if (size == -1) {
			fprintf(stderr, "write() failed for export\n");
			exit(EXIT_FAILURE);
		}
	}

	if ((access("/sys/class/gpio/gpio4", R_OK | W_OK)) == -1) {
		size = write(fd_export, "4", strlen("4"));
		if (size == -1) {
			fprintf(stderr, "write() failed for export\n");
			exit(EXIT_FAILURE);
		}
	}
	
	if ((access("/sys/class/gpio/gpio2", R_OK | W_OK)) == -1) {
		size = write(fd_export, "2", strlen("2"));
		if (size == -1) {
			fprintf(stderr, "write() failed for export\n");
			exit(EXIT_FAILURE);
		}
	}

	if (fd_export) {
		close(fd_export);
	}
}

/*
 * open_files()
 *	Open direction and value files of every exported GPIO pin
 */
void 
open_files()
{
	ssize_t size;

	fd_rst_dir = open("/sys/class/gpio/gpio60/direction", O_RDWR);
	if (fd_rst_dir == -1) {
		fprintf(stderr, "open() failed for rst-direction\n");
		exit(EXIT_FAILURE);
	}
	
	fd_rst_val = open("/sys/class/gpio/gpio60/value", O_RDWR);
	if (fd_rst_val == -1) {
		fprintf(stderr, "open() failed for rst-val\n");
		exit(EXIT_FAILURE);
	}
	
	fd_dc_dir = open("/sys/class/gpio/gpio48/direction", O_RDWR);
	if (fd_dc_dir == -1) {
		fprintf(stderr, "open() failed for dc-direction\n");
		exit(EXIT_FAILURE);
	}
	
	fd_dc_val = open("/sys/class/gpio/gpio48/value", O_RDWR);
	if (fd_dc_val == -1) {
		fprintf(stderr, "open() failed for dc-val\n");
		exit(EXIT_FAILURE);
	}
		
	fd_cs_dir = open("/sys/class/gpio/gpio5/direction", O_RDWR);
	if (fd_cs_dir == -1) {
		fprintf(stderr, "open() failed for cs-direction\n");
		exit(EXIT_FAILURE);
	}
	
	fd_cs_val = open("/sys/class/gpio/gpio5/value", O_RDWR);
	if (fd_cs_val == -1) {
		fprintf(stderr, "open() failed for cs-val\n");
		exit(EXIT_FAILURE);
	}

	fd_din_dir = open("/sys/class/gpio/gpio4/direction", O_RDWR);
	if (fd_din_dir == -1) {
		fprintf(stderr, "open() failed for din-direction\n");
		exit(EXIT_FAILURE);
	}
	
	fd_din_val = open("/sys/class/gpio/gpio4/value", O_RDWR);
	if (fd_cs_val == -1) {
		fprintf(stderr, "open() failed for cs-val\n");
		exit(EXIT_FAILURE);
	}
	
	fd_clk_dir = open("/sys/class/gpio/gpio2/direction", O_RDWR);
	if (fd_clk_dir == -1) {
		fprintf(stderr, "open() failed for clk-direction\n");
		exit(EXIT_FAILURE);
	}
	
	fd_clk_val = open("/sys/class/gpio/gpio2/value", O_RDWR);
	if (fd_clk_val == -1) {
		fprintf(stderr, "open() failed for clk-val\n");
		exit(EXIT_FAILURE);
	}
}

/*
 * init_rst()
 *	Reset the LCD
 */
void
init_rst()
{
	ssize_t size;
	
	size = write(fd_rst_val, "0", 1);
	if (size == -1) {
		fprintf(stderr, "write() failed for rst-val\n");
		exit(EXIT_FAILURE);
	}

	sleep(1);

	size = write(fd_rst_val, "1", 1);
	if (size == -1) {
		fprintf(stderr, "write() failed for rst-val\n");
		exit(EXIT_FAILURE);
	}
}

/*
 * write_directions()
 *	Every GPIO's direction must be set to "out"
 */
void
write_directions()
{
	ssize_t size;

	size = write(fd_rst_dir, "out", strlen("out"));
	if (size == -1) {
		fprintf(stderr, "write() failed for rst-dir\n");
		exit(EXIT_FAILURE);
	}
	
	size = write(fd_cs_dir, "out", strlen("out"));
	if (size == -1) {
		fprintf(stderr, "write() failed for cs-dir\n");
		exit(EXIT_FAILURE);
	}
	
	size = write(fd_dc_dir, "out", strlen("out"));
	if (size == -1) {
		fprintf(stderr, "write() failed for dc-dir\n");
		exit(EXIT_FAILURE);
	}
	
	size = write(fd_din_dir, "out", strlen("out"));
	if (size == -1) {
		fprintf(stderr, "write() failed for din-dir\n");
		exit(EXIT_FAILURE);
	}

	size = write(fd_clk_dir, "out", strlen("out"));
	if (size == -1) {
		fprintf(stderr, "write() failed for clk-dir\n");
		exit(EXIT_FAILURE);
	}
}

/*
 * init_spi_dev()
 *	Set SPI devices' attributes
 */
void
init_spi_dev()
{
	uint32_t mode;
	int ret = 0;
	
	fd_spi_dev = open(device, O_RDWR);
	if (fd_spi_dev == -1) {
		fprintf(stderr, "open() failed for spi device\n");
		exit(EXIT_FAILURE);
	}

	//set mode
	mode = SPI_MODE_0;
	ret = ioctl(fd_spi_dev, SPI_IOC_WR_MODE, &mode);
	if (ret == -1) {
		fprintf(stderr, "ioctl() failed while setting write mode\n");
		exit(EXIT_FAILURE);
	}
	
	//set clock speed
	ret = ioctl(fd_spi_dev, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (ret == -1) {
		fprintf(stderr, "ioctl() failed while setting write bit rate\n");
		exit(EXIT_FAILURE);
		
	}
}

/*
 * invert_color() 
 *	Invert pixel colors
 */
void
invert_color()
{
	lcd_write_cmd(0x0D);
}

/*
 * init_all_segments()
 *	Initializes all the pixels on the LCD. This function can be used 
 * 	as a simple test to test screen's sanity.
 */
void
init_all_segments()
{
	lcd_write_cmd(0x09);	// LCD all segments on		//Tutorial 1
	sleep(2);
	lcd_write_cmd(0x0C);	// LCD normal video		//Tutorial 2
}

/*
 * init_lcd_screen()
 *	Initialize the LCD by setting its attributes
 */
void
init_lcd_screen()
{
	lcd_write_cmd(0x21);	// LCD extended commands
	lcd_write_cmd(0xB8);	// set LCD Vop (contrast)
	// you can change above 0xB8 to 0xBF to lower the contrast		//Tutorial 2
	lcd_write_cmd(0x04);	// set temp coefficient
	lcd_write_cmd(0x14);	// set biad mode 1:40
	lcd_write_cmd(0x20);	// LCD basic commands
	lcd_write_cmd(0x0C);	// LCD normal video		//Tutorial 2
}

/*
 * lcd_init()
 *	Initialize the code
 */
void
lcd_init()
{
	init_export();
	open_files();
	write_directions();
	init_rst();
	init_spi_dev();
	init_lcd_screen();
	memset(screen_buffer, 0, SCREEN_BUF_SIZE);	//this buffer is used for scrolling purpose
}

/*
 * lcd_deinit()
 *	De-initialize the code
 */

void lcd_deinit()
{
	if (close(fd_rst_dir) == -1) {
		goto close_err;
	}
	
	if (close(fd_rst_val) == -1) {
		goto close_err;
	}

	if (close(fd_dc_dir) == -1) {
		goto close_err;
	}
	
	if (close(fd_dc_val) == -1) {
		goto close_err;
	}
	
	if (close(fd_cs_dir) == -1) {
		goto close_err;
	}
	
	if (close(fd_cs_val) == -1) {
		goto close_err;
	}

	if (close(fd_din_dir) == -1) {
		goto close_err;
	}
	
	if (close(fd_din_val) == -1) {
		goto close_err;
	}
	
	if (close(fd_clk_dir) == -1) {
		goto close_err;
	}
	
	if (close(fd_clk_val) == -1) {
		goto close_err;
	}
	
	if (close(fd_spi_dev) == -1) {
		goto close_err;
	}

	return;
close_err:
	fprintf(stderr, "close() failed\n");
	exit(EXIT_FAILURE);
}

/*
 * lcd_write_cmd()
 *	Send a command to the LCD over SPI protocol
 */
void
lcd_write_cmd(uint8_t cmd)
{
	int ret;
	ssize_t size;
	uint8_t temp[10];

	uint8_t *tx = &cmd;
	uint8_t rx;
	uint32_t len = 1;
	
	struct spi_ioc_transfer tr = {
		.tx_buf = (uint32_t)tx,
		.rx_buf = (uint32_t)&rx,
		.len = len,
		.delay_usecs = delay,
		.speed_hz = speed,
		.bits_per_word = bits,
		.cs_change = 1,
	};

	size = write(fd_dc_val, "0", 1);
	if (size == -1) {
		fprintf(stderr, "write() failed for dc-val\n");
		exit(EXIT_FAILURE);
	}
	
	size = write(fd_cs_val, "0", 1);
	if (size == -1) {
		fprintf(stderr, "write() failed for cs-val\n");
		exit(EXIT_FAILURE);
	}
	
	ret = ioctl(fd_spi_dev, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 0) {
		fprintf(stderr, "ioctl failed while sending command to the device\n");
		exit(EXIT_FAILURE);
	}

	size = write(fd_cs_val, "1", 1);
	if (size == -1) {
		fprintf(stderr, "write() failed for cs-val\n");
		exit(EXIT_FAILURE);
	}
}

/*
 * lcd_write_data()
 *	Send a data byte to the LCD over SPI protocol
 */
void
lcd_write_data(uint8_t data)
{
	int ret;
	ssize_t size;
	uint8_t temp[10];

	uint8_t *tx = &data;
	uint8_t rx;
	uint32_t len = 1;
	
	struct spi_ioc_transfer tr = {
		.tx_buf = (uint32_t)tx,
		.rx_buf = (uint32_t)&rx,
		.len = len,
		.delay_usecs = delay,
		.speed_hz = speed,
		.bits_per_word = bits,
		.cs_change = 1,
	};

	size = write(fd_dc_val, "1", 1);
	if (size == -1) {
		fprintf(stderr, "write() failed for dc-val\n");
		exit(EXIT_FAILURE);
	}
	
	size = write(fd_cs_val, "0", 1);
	if (size == -1) {
		fprintf(stderr, "write() failed for cs-val\n");
		exit(EXIT_FAILURE);
	}
	
	ret = ioctl(fd_spi_dev, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 0) {
		fprintf(stderr, "ioctl failed while sending data to the device\n");
		exit(EXIT_FAILURE);
	}

	size = write(fd_cs_val, "1", 1);
	if (size == -1) {
		fprintf(stderr, "write() failed for cs-val\n");
		exit(EXIT_FAILURE);
	}
}

/*
 * lcd_write_char()
 *	Display a character on LCD
 */
void
lcd_write_char(uint8_t character)
{
	int i;

	for (i = 0; i < 5; i++) {
		lcd_write_data(ASCII[character - 0x20][i]);
	}

	lcd_write_data(0x00);
}

/*
 * lcd_write_str() 
 *	Display the string on LCD character by character
 */
void
lcd_write_str(uint8_t *str)
{
	while(*str) {
		lcd_write_char(*str);
		str++;
	}
}

/*
 * lcd_set_coordinates()
 *	Set x and y coordinates for next write
 */
void
lcd_set_coordinates(int x, int y)
{
	lcd_write_cmd(0x80 | x);	// Column
	lcd_write_cmd(0x40 | y);	// Row
}

/*
 * fmt_to_str()
 *	Copy the format string and the variadic list of arguments into the specified buffer
 */
int
fmt_to_str(char **buffer, const char *fmt, va_list ap)
{
	int y_pos_increment;
	int len;
	
	vsprintf(*buffer, fmt, ap);
	
	len = strlen(*buffer);
	
	assert(len <= SCREEN_BUF_SIZE);

	y_pos_increment = len / LINE_BUF_SIZE;		// 14 characters in 1 line 
	
	if ((len % LINE_BUF_SIZE) != 0) {
		y_pos_increment += 1;
	}

	return y_pos_increment;
}

/*
 * scroll_up()
 *	Scroll one line up
 */
void
scroll_up()
{
	memmove(screen_buffer, screen_buffer + LINE_BUF_SIZE, SCREEN_BUF_SIZE - LINE_BUF_SIZE);
	memset(screen_buffer + (SCREEN_BUF_SIZE - LINE_BUF_SIZE), 0, LINE_BUF_SIZE);
	clrscr();
	lcd_write_str(screen_buffer);
}	

/*
 * lcd_printf()
 *	A printf() equivalent for displaying a string on LCD
 */
int
lcd_printf(const char *fmt, ...)
{
	char *buffer;
	int y_pos_increment;
	int num_pad_bytes = 0;
	int len;
	int buf_pos = 0;
	char *buff_to_print = calloc(1, LINE_BUF_SIZE);

	va_list ap;

	buffer = calloc(1, SCREEN_BUF_SIZE);			// screen can accomodate only 84 characters

	va_start(ap, fmt);
	y_pos_increment = fmt_to_str(&buffer, fmt, ap);
	va_end(ap);

	len = strlen(buffer);

	// pad buffer
	if (len % LINE_BUF_SIZE != 0) {
		num_pad_bytes = (LINE_BUF_SIZE * y_pos_increment) - len;
	}

	while(num_pad_bytes > 0) {
		strncat(buffer, " ", 1);
		num_pad_bytes -= 1;
	}

	while (next_y_pos <= LINES_IN_SCREEN && y_pos_increment != 0) {
		memmove(buff_to_print, buffer + buf_pos, 14);
		strncat(screen_buffer, buff_to_print, LINE_BUF_SIZE);
		lcd_set_coordinates(0, next_y_pos);
		lcd_write_str(buff_to_print);
		buf_pos += LINE_BUF_SIZE;
		next_y_pos++;
		y_pos_increment--;
		memset(buff_to_print, 0, LINE_BUF_SIZE);
	}

	if (y_pos_increment == 0) {
		goto ret_success;
	}

	// we need to scroll up now
	while(y_pos_increment != 0) {
		scroll_up();
		memcpy(buff_to_print, buffer + buf_pos, LINE_BUF_SIZE);
		strncat(screen_buffer, buff_to_print, LINE_BUF_SIZE);
		lcd_set_coordinates(0, LINES_IN_SCREEN);		// write on last line
		lcd_write_str(buff_to_print);
		buf_pos += LINE_BUF_SIZE;
		y_pos_increment--;
		memset(buff_to_print, 0, LINE_BUF_SIZE);
	}

ret_success:
	if (buff_to_print != NULL) {
		free(buff_to_print);
		buff_to_print = NULL;
	} 

	if(buffer != NULL) {
		free(buffer);
		buffer = NULL;
	}

	return 0;
}

/*
 * clrscr()
 *	Clear LCD screen
 */
void
clrscr()
{
	int i;
	for (i = 0; i < 504; i++) {	// clear lcd screen	//Tutorial 2
		lcd_write_data(0x00);
	}
}

