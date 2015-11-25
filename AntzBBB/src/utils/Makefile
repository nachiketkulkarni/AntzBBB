CC=gcc
CFLAGS=-I../include/ -fPIC -Wall
LDFLAGS=-shared
COMM_DIR=communication
DISP_DIR=display/nokia_5110
MOTOR_DIR=motor/dc_motor
SRC_DIRS=$(COMM_DIR)/ir $(COMM_DIR)/xbee $(COMM_DIR)/bluetooth $(DISP_DIR) $(MOTOR_DIR)
OBJS=$(COMM_DIR)/ir/infrared.o $(COMM_DIR)/xbee/xbee.o $(COMM_DIR)/bluetooth/bluetooth.o $(DISP_DIR)/lcd.o $(MOTOR_DIR)/motor.o
LIB_PATH=../libs/
TARGET_LIB=$(LIB_PATH)librobotutils.so

.PHONY: all
all:
	cd $(COMM_DIR)/ir; $(MAKE)
	cd $(COMM_DIR)/xbee; $(MAKE)
	cd $(COMM_DIR)/bluetooth; $(MAKE)
	cd $(DISP_DIR); $(MAKE)
	cd $(MOTOR_DIR); $(MAKE)

communication:
	cd $(COMM_DIR)/ir; $(MAKE)
	cd $(COMM_DIR)/xbee; $(MAKE)
	cd $(COMM_DIR)/bluetooth; $(MAKE)

display:
	cd $(DISP_DIR) && $(MAKE)

motor:
	cd $(MOTOR_DIR) && $(MAKE)

ir:
	cd $(COMM_DIR)/ir && $(MAKE)

xbee:
	cd $(COMM_DIR)/xbee && $(MAKE)

bluetooth:
	cd $(COMM_DIR)/bluetooth && $(MAKE)

display:
	cd $(DISP_DIR) && $(MAKE)

motor:
	cd $(MOTOR_DIR) &&  $(MAKE)

build_so: $(TARGET_LIB)
$(TARGET_LIB): $(OBJS)
	$(CC) -o $(TARGET_LIB) $(OBJS) $(CFLAGS) $(LDFLAGS)

clean_utils:
	cd $(COMM_DIR)/ir; $(MAKE) clean
	cd $(COMM_DIR)/xbee; $(MAKE) clean
	cd $(COMM_DIR)/bluetooth; $(MAKE) clean
	cd $(DISP_DIR); $(MAKE) clean
	cd $(MOTOR_DIR); $(MAKE) clean	

clean_lib:
	rm -rf $(TARGET_LIB)

.PHONY: clean_lib all communication ir xbee bluetooth display motor build_so
