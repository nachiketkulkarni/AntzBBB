include Makefile.inc

SRC_DIR=src
ANTZ_DIR=$(SRC_DIR)/antz
UTILS_DIR=$(SRC_DIR)/utils
DISP_DIR=$(UTILS_DIR)/display/nokia_5110
MOTOR_DIR=$(UTILS_DIR)/motor/dc_motor
COMM_DIR=$(UTILS_DIR)/communication
IR_DIR=$(COMM_DIR)/ir
BT_DIR=$(COMM_DIR)/bluetooth
XBEE_DIR=$(COMM_DIR)/xbee
INCLUDE_DIR=$(SRC_DIR)/include
MANPAGE_DIR=Documentation/man-pages
LIB_DIR=$(SRC_DIR)/libs

help:
	@echo "		all		: build all components, library, robots"
	@echo "		antz		: build robots"
	@echo "		utils		: build all utilities"
	@echo "		lcd		: build lcd"
	@echo "		motor		: build motor"
	@echo "		communication	: build all communication components"
	@echo "		ir		: build ir communication"
	@echo "		bluetooth	: build bluetooth communication"
	@echo "		xbee		: build xbee communication"
	@echo "		librobotutils	: build utility library"
	@echo "		install		: installs headers, libcoreutils.so and man pages"
	@echo "		clean_all	: clean all executables"
	@echo "		clean_antz	: clean all executables in antz/"
	@echo "		clean_utils	: clean all executables in utils/"

all:
	cd $(UTILS_DIR) && $(MAKE) all
	cd $(UTILS_DIR) && $(MAKE) build_so
	cd $(ANTZ_DIR) && $(MAKE)

antz:
	cd $(ANTZ_DIR) && $(MAKE)

utils:
	cd $(UTILS_DIR) && $(MAKE) all

lcd:
	cd $(UTILS_DIR) && $(MAKE) display

motor:
	cd $(UTILS_DIR) && $(MAKE) motor

communication:
	cd $(UTILS_DIR) && $(MAKE) communication

ir:
	cd $(UTILS_DIR) && $(MAKE) ir

bluetooth:
	cd $(UTILS_DIR) && $(MAKE) bluetooth

xbee:
	cd $(UTILS_DIR) && $(MAKE) xbee

librobotutils:
	cd $(UTILS_DIR) && $(MAKE) build_so

install:
	cd $(INCLUDE_DIR) && $(MAKE) install
	cd $(MANPAGE_DIR) && $(MAKE) install
	cd $(LIB_DIR) && $(MAKE) install

clean_all:
	cd $(ANTZ_DIR) && $(MAKE) clean
	cd $(UTILS_DIR) && $(MAKE) clean_utils

clean_antz:
	cd $(ANTZ_DIR) && $(MAKE) clean

clean_utils:
	cd $(UTILS_DIR) && $(MAKE) clean_utils

.PHONY: all librobotutils motor ir bluetooth xbee utils lcd communication antz install \
		clean_all clean_antz clean_utils
