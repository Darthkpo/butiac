#include "board.h"

int board_new(board **new_b_ptr, libusb_device_handle *udev) {
    DEBUG_PASSED_NULL_PTR(udev)
    board *b_ptr = malloc(sizeof(board));

    CHECK_MALLOC_RETURNED(b_ptr)

    b_ptr->udev = udev;
    b_ptr->modules = lnew();
    
    *new_b_ptr = b_ptr;

    return 0;

}

void board_free(board *b_ptr) { 

    DEBUG_PASSED_NULL_PTR(b_ptr)
    lfree(b_ptr->modules, 1);
    free(b_ptr);
    
}

int board_open(libusb_device *dev, board **b_ptr) {

    DEBUG_PASSED_NULL_PTR(dev)
    libusb_device_handle *ndev;
    int ret = libusb_open(dev, &ndev);
    CHECK_LIBUSB_RETURNED(ret)
    return board_new(b_ptr, ndev);

}

void board_close(board *b_ptr) {
    
    DEBUG_PASSED_NULL_PTR(b_ptr)
    libusb_close(b_ptr->udev);
    board_free(b_ptr);

}

int b_get_handler_type(board *b_ptr, int index) {
    DEBUG_PASSED_NULL_PTR(b_ptr)
    unsigned char payload[5] = { ADMIN_HANDLER_SEND_COMMAND,
                                 GET_HANDLER_TYPE_PACKET_SIZE,
                                 NULL_BYTE,
                                 GET_HANDLER_TYPE_COMMAND,
                                 index };

    int ret = dev_write(b_ptr->udev, payload, 5);
    CHECK_LIBUSB_RETURNED(ret)

    unsigned char raw[GET_HANDLER_RESPONSE_PACKET_SIZE];
    ret = dev_read(b_ptr->udev, raw, GET_HANDLER_RESPONSE_PACKET_SIZE);
    CHECK_LIBUSB_RETURNED(ret)

    return raw[4];
}

int b_get_user_modules_size(board *b_ptr) {
    DEBUG_PASSED_NULL_PTR(b_ptr)
    unsigned char payload[4] = { ADMIN_HANDLER_SEND_COMMAND,
                                 DEFAULT_PACKET_SIZE,
                                 NULL_BYTE,
                                 GET_USER_MODULES_SIZE_COMMAND };
    
}
