#ifndef _BUTIAC_BOARD_H_
#define _BUTIAC_BOARD_H_

#include "com_usb.h"
#include "module.h"

typedef struct board {

    libusb_device_handle *udev;

} board;

int board_new(board **new_b_ptr, libusb_device_handle *udev);
void board_free(board *b_ptr);
int board_open(libusb_device *dev, board **b_ptr);
void board_close(board *b_ptr);
int board_send(board *b_ptr, int index, unsigned char* data, size_t size);
int board_read(board *b_ptr, unsigned char* data, size_t size);

//Board functions
int b_get_handler_type(board *b_ptr, int index);
int b_get_user_modules_size(board *b_ptr);
int b_get_user_module_line(board *b_ptr, int index, char **buffer);

#endif
