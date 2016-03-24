#!/bin/bash

DRIVER="am33xx_pwm"
P9_14_DRIVER="bone_pwm_P9_14"

SLOTS=`ls /sys/devices/bone_capemgr.*/slots`

echo $DRIVER > $SLOTS 2> /tmp/abc
sleep 0.5

echo $P9_14_DRIVER > $SLOTS 2> /tmp/abc
sleep 0.5

P9_14_PWM_DIR=`find /sys/devices/ocp.* -name "pwm_test_P9_14.*"`
if [ $? -ne 0 ];
then
	echo "pwm dir of P9_14 not found"
	exit 1
fi

P9_14_PWM_DIR="$P9_14_PWM_DIR/"

echo -e "\n$P9_14_PWM_DIR"

./test_ir $P9_14_DIR
