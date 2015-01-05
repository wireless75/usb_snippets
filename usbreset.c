/*
	usbreset.c

	Yet another USB reset snippet.

	Syntax: usbreset usb_device_file_name
	Example: usbreset /dev/bus/usb/002/001

	Return codes:
		0: OK
		1: Syntax error
		2: Device not found
		3: Not enough privileges
		4: Not an USB device

	Changelog:
	20121016: Implementation.
*/

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/usbdevice_fs.h>

enum
{
	RES_OK = 0, RES_SYNTAX_ERR = 1, RES_NOT_FOUND = 2, RES_PRIV_ERR = 3, RES_NOT_USB = 4
};

int usb_reset(char *device_name)
{
	int f, result = RES_NOT_FOUND;
	if (access(device_name, F_OK) == 0) {
		if ( (f = open(device_name, O_WRONLY)) > 0 ) {
			result = ioctl(f, USBDEVFS_RESET, 0) < 0? RES_NOT_USB : RES_OK;
			close(f);
		}
		else {
			result = RES_PRIV_ERR;
		}
	}
	return result;
}

int main(int argc, char **argv)
{
	int result = argc == 2? usb_reset(argv[1]) : RES_SYNTAX_ERR;
	switch (result) {
	case RES_SYNTAX_ERR:	fprintf(stderr, "ERROR: Wrong syntax. Example: %s /dev/bus/usb/002/001\n", argv[0]);
				break;
	case RES_NOT_FOUND:	fprintf(stderr, "ERROR: '%s': File not found.\n", argv[1]);
				break;
	case RES_PRIV_ERR:	fprintf(stderr, "ERROR: '%s': Not enough privileges.\n", argv[1]);
				break;
	case RES_NOT_USB:	fprintf(stderr, "ERROR: '%s': Not an USB device\n", argv[1]);
	}
	return result;
}
	

