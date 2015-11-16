#!/bin/bash

ifconfig wlan0 down
ifconfig usb0 down
ifconfig wlan0 up
ifconfig usb0 up

/home/root/pinewoods/fl_edison_monitor/monitor-arduino.sh 