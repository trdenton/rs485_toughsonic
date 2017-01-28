#!/bin/bash
gcc --std=c99 reading.c `pkg-config --libs --cflags libmodbus` -o take_reading

