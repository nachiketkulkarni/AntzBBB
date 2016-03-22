#!/bin/bash

MOTOR_DRIVER="am33xx_pwm"
P8_13_DRIVER="bone_pwm_P8_13"
P9_14_DRIVER="bone_pwm_P9_14"

SLOTS=`ls /sys/devices/bone_capemgr.*/slots`

echo $P8_13_DRIVER > $SLOTS 2> /tmp/abc
echo $P9_14_DRIVER > $SLOTS 2> /tmp/abc

P8_13_PWM_DIR=`find /sys/devices/ocp.* -name "pwm_test_P8_13.*"`

if [ $? -ne 0 ];
then
	echo "pwm dir of P8_13 not found"
	exit 1
fi

sleep 1

P9_14_PWM_DIR=`find /sys/devices/ocp.* -name "pwm_test_P9_14.*"`
if [ $? -ne 0 ];
then
	echo "pwm dir of P9_14 not found"
	exit 1
fi

sleep 1

P8_13_PWM_DIR="$P8_13_PWM_DIR/"
P9_14_PWM_DIR="$P9_14_PWM_DIR/"

#echo -e "\n$P8_13_PWM_DIR"
#echo -e "\n$P8_13_PWM_DIR"

./test_motor $P9_14_PWM_DIR $P9_14_PWM_DIR
