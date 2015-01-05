#
# Makefile for 'usb_snippets' targets.
#
# Changelog:
# 20121016: usbreset target added. 
#

CC=gcc
CFLAGS-std=c89

all: usbreset

usbreset: usbreset.o

clean:
	rm -f usbreset usbreset.o

