#ifndef _BUTIAC_COM_USB_H_
#define _BUTIAC_COM_USB_H_

#include <libusb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USB4ALL_VENDOR        0x04d8
#define USB4ALL_PRODUCT       0x000c
#define USB4ALL_CONFIGURATION 1
#define USB4ALL_INTERFACE     0

#define ADMIN_MODULE_IN_ENDPOINT  0x01
#define ADMIN_MODULE_OUT_ENDPOINT 0x81

#define TIMEOUT 250
#define ERROR -1

struct {

	libusb_device_handle *dev;
	int debug;

} typedef usb_device;

usb_device* usb_device_new(libusb_device_handle *dev, int debug);
void usb_device_free(usb_device *udev);
void usb_device_print(usb_device *udev);
int usb_device_open(usb_device *udev);
unsigned char* usb_device_read(usb_device *udev, size_t size);
int usb_device_write(usb_device *udev, unsigned char* data, size_t size);

ssize_t cu_find(usb_device*** list);

#endif
