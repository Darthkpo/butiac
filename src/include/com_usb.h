#ifndef _BUTIAC_COM_USB_H_
#define _BUTIAC_COM_USB_H_

#include <libusb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "debug.h"

#define USB4ALL_VENDOR        0x04d8
#define USB4ALL_PRODUCT       0x000c
#define USB4ALL_CONFIGURATION 1
#define USB4ALL_INTERFACE     0
#define NULL_BYTE                         0x00
#define OPEN_COMMAND                      0x00
#define CLOSE_COMMAND                     0x01
#define HEADER_PACKET_SIZE                0x06
#define ADMIN_HANDLER_SEND_COMMAND        0x00
#define OPEN_RESPONSE_PACKET_SIZE         5
#define CLOSE_RESPONSE_PACKET_SIZE        5
#define DEFAULT_PACKET_SIZE               0x04
#define GET_USER_MODULES_SIZE_COMMAND     0x05
#define GET_USER_MODULE_LINE_COMMAND      0x06
#define GET_HANDLER_SIZE_COMMAND          0x0A
#define GET_HANDLER_TYPE_COMMAND          0x0B
#define ADMIN_HANDLER_SEND_COMMAND        0x00
#define CLOSEALL_COMMAND                  0x07
#define CLOSEALL_RESPONSE_PACKET_SIZE     0x05
#define SWITCH_TO_BOOT_BASE_BOARD_COMMAND 0x09
#define RESET_BASE_BOARD_COMMAND          0xFF
#define GET_USER_MODULE_LINE_PACKET_SIZE  0x05
#define GET_LINES_RESPONSE_PACKET_SIZE    0x05
#define GET_LINE_RESPONSE_PACKET_SIZE     0x0C
#define GET_HANDLER_TYPE_PACKET_SIZE      0x05
#define GET_HANDLER_RESPONSE_PACKET_SIZE  0x05

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
