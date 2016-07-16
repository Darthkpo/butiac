#include "board.h"

int board_new(board **new_b_ptr, libusb_device_handle *udev) {
    DEBUG_PASSED_NULL_PTR(udev)
    board *b_ptr = malloc(sizeof(board));

    CHECK_MALLOC_RETURNED(b_ptr)

    b_ptr->udev = udev;
    
    *new_b_ptr = b_ptr;

    return 0;

}

void board_free(board *b_ptr) { 

    DEBUG_PASSED_NULL_PTR(b_ptr);
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

int board_send(board *b_ptr, int index, unsigned char* data, size_t size) {

    unsigned char *payload = malloc( 3 + size );
    CHECK_MALLOC_RETURNED(payload);
    payload[0] = index * 8;
    payload[1] = 3 + size;
    payload[2] = NULL_BYTE;
    for(int i = 3; i < size + 3; i++) {
        payload[i] = data[i - 3];
    }
    CHECK_LIBUSB_RETURNED(dev_write(b_ptr->udev, payload, 3 + size));
    return 0;

}

int board_read(board *b_ptr, unsigned char* data, size_t size) {

    unsigned char *raw = malloc( 3 + size );
    CHECK_LIBUSB_RETURNED(dev_read(b_ptr->udev, raw, 3 + size));
    for(int i = 3; i < size + 3; i++) {
        data[i - 3] = raw[i];
    }
    return 0;

}

int b_get_handler_type(board *b_ptr, int index) {
    DEBUG_PASSED_NULL_PTR(b_ptr)
    unsigned char payload[5] = { ADMIN_HANDLER_SEND_COMMAND,
                                 GET_HANDLER_TYPE_PACKET_SIZE,
                                 NULL_BYTE,
                                 GET_HANDLER_TYPE_COMMAND,
                                 index };
    CHECK_LIBUSB_RETURNED(dev_write(b_ptr->udev, payload, 5))
    unsigned char raw[GET_HANDLER_RESPONSE_PACKET_SIZE];
    CHECK_LIBUSB_RETURNED(dev_read(b_ptr->udev, raw, GET_HANDLER_RESPONSE_PACKET_SIZE))
    return raw[4];
}

int b_get_user_modules_size(board *b_ptr) {
    DEBUG_PASSED_NULL_PTR(b_ptr)
    unsigned char payload[4] = { ADMIN_HANDLER_SEND_COMMAND,
                                 DEFAULT_PACKET_SIZE,
                                 NULL_BYTE,
                                 GET_USER_MODULES_SIZE_COMMAND };
    CHECK_LIBUSB_RETURNED(dev_write(b_ptr->udev, payload, 4))
    unsigned char raw[GET_USER_MODULE_LINE_PACKET_SIZE];
    CHECK_LIBUSB_RETURNED(dev_read(b_ptr->udev, raw, GET_USER_MODULE_LINE_PACKET_SIZE))
    return raw[4]; 
}

int b_get_user_module_line(board *b_ptr, int index, char **buffer) {
   DEBUG_PASSED_NULL_PTR(b_ptr);
   unsigned char payload[5] = { ADMIN_HANDLER_SEND_COMMAND,
                                GET_USER_MODULE_LINE_PACKET_SIZE,
                                NULL_BYTE,
                                GET_USER_MODULE_LINE_COMMAND,
                                index };
   CHECK_LIBUSB_RETURNED(dev_write(b_ptr->udev, payload, 5))
   unsigned char raw[GET_LINE_RESPONSE_PACKET_SIZE];
   CHECK_LIBUSB_RETURNED(dev_read(b_ptr->udev, raw, GET_LINE_RESPONSE_PACKET_SIZE));
   char *module_line = malloc( GET_LINE_RESPONSE_PACKET_SIZE - 4 );
   CHECK_MALLOC_RETURNED(module_line);
   for(int i = 4; i < GET_LINE_RESPONSE_PACKET_SIZE; i++) {
      
      module_line[i-4] = (char)raw[i];

   }
   *buffer = module_line;
   return 0;
}
