#ifndef _BUTIAC_COM_USB_H_
#define _BUTIAC_COM_USB_H_

#include <libusb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define USB4ALL_VENDOR        0x04d8
#define USB4ALL_PRODUCT       0x000c
#define USB4ALL_CONFIGURATION 1
#define USB4ALL_INTERFACE     0

#define ADMIN_MODULE_IN_ENDPOINT  0x01
#define ADMIN_MODULE_OUT_ENDPOINT 0x81

#define TIMEOUT 250
#define ERROR -1

void dev_print(libusb_device_handle *devh);
int dev_open(libusb_device_handle *devh);
int dev_read(libusb_device_handle *devh, unsigned char* data, size_t size);
int dev_write(libusb_device_handle *devh, unsigned char* data, size_t size);

list* cu_find(void);

#endif
