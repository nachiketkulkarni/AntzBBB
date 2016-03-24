#!/bin/bash

echo 30 > /sys/class/gpio/export

echo "in" > /sys/class/gpio/gpio30/direction

echo "both" > /sys/class/gpio/gpio30/edge

echo 1 > /sys/class/gpio/gpio30/active_low 
