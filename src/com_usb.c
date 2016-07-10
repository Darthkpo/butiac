#include "com_usb.h"

void dev_print(libusb_device_handle *devh) {

	unsigned char name[64];
	unsigned char copy[64];
	unsigned char sn[64];

	libusb_get_string_descriptor_ascii(devh,1,name,64);
	libusb_get_string_descriptor_ascii(devh,2,copy,64);
	libusb_get_string_descriptor_ascii(devh,3,sn,  64);

	printf("Name: %s\nCopy: %s\nSn: %s\n", name, copy, sn);

}

int dev_open(libusb_device_handle *devh) {

	int active = libusb_kernel_driver_active(devh, USB4ALL_INTERFACE);
	if(active == 1)
		libusb_detach_kernel_driver(devh, USB4ALL_INTERFACE);

	libusb_set_configuration(devh, USB4ALL_CONFIGURATION);

	return 0;

}

int dev_read(libusb_device_handle *devh, unsigned char* data, size_t size) {

	int transferred = 0;
	return libusb_bulk_transfer(devh, ADMIN_MODULE_OUT_ENDPOINT, data, size, &transferred, TIMEOUT);	

}

int dev_write(libusb_device_handle *devh, unsigned char* data, size_t size) {

	int transferred = 0;
	return libusb_bulk_transfer(devh, ADMIN_MODULE_IN_ENDPOINT, data, size, &transferred, TIMEOUT);

}
