#include "com_usb.h"

int mod_open(MODULES mod, libusb_device_handle *devh) {
    unsigned char *module_name;
    size_t len_module_name = 0;
    switch(mod) {
    
    case admin : {
        len_module_name = 6;
        module_name = malloc( 6 );
        module_name[0] = 97;
        module_name[1] = 100;
        module_name[2] = 109;
        module_name[3] = 105;
        module_name[4] = 110;
        module_name[5] = 0;
        printf("Opening module 'admin'.\n");
        break;
    }
    case distanc : {
        len_module_name = 8;
        module_name = malloc( 8 );
        module_name[0] = 100;
        module_name[1] = 105;
        module_name[2] = 115;
        module_name[3] = 116;
        module_name[4] = 97;
        module_name[5] = 110;
        module_name[6] = 99;
        module_name[7] = 0;
        printf("Opening module 'distanc'.\n");
        break;
    }

    }

    unsigned char *payload = malloc( 6 + len_module_name );
    payload[0] = ADMIN_HANDLER_SEND_COMMAND;
    payload[1] = HEADER_PACKET_SIZE + len_module_name;
    payload[2] = NULL_BYTE;
    payload[3] = OPEN_COMMAND;
    payload[4] = 0x01;
    payload[5] = 0x01;
    for(int i = 6; i < 6 + len_module_name; i++) {
        payload[i] = module_name[i - 6];
    }
    free(module_name);
    printf("Write: %d\n", dev_write(devh, payload, 6 + len_module_name));
    free(payload);
    unsigned char raw[OPEN_RESPONSE_PACKET_SIZE];
    printf("Read: %d\n", dev_read(devh, raw, OPEN_RESPONSE_PACKET_SIZE));
    printf("Handler returned: %d\n", raw[4]);
    return raw[4];
}

int get_handler_type(int index, libusb_device_handle *devh) {
    printf("Getting handler type of: %d.\n", index);
    unsigned char payload[5] = { ADMIN_HANDLER_SEND_COMMAND,
                                 GET_HANDLER_TYPE_PACKET_SIZE,
                                 NULL_BYTE,
                                 GET_HANDLER_TYPE_COMMAND,
                                 index };
    printf("Write: %d\n", dev_write(devh, payload, 5));
    unsigned char raw[GET_HANDLER_RESPONSE_PACKET_SIZE];
    printf("Read: %d\n", dev_read(devh, raw, GET_HANDLER_RESPONSE_PACKET_SIZE));
    printf("Handler type returned: %d\n", raw[4]);
    return raw[4];
}

int main (int argc, char** argv) {

	libusb_context *context = NULL;
	printf("libusb init: %d\n", libusb_init(&context));
	libusb_set_debug(context,3);

	list *butias_devices = cu_find();
	printf("Butias found: %lu\n", butias_devices->size);

	list *bdevh = lnew();

	node *iter = butias_devices->head;
	for(int i = 0; i < butias_devices->size; i++) {
		libusb_device_handle *newhandle;
		printf("Opening %d: %d\n", i, libusb_open(iter->value, &newhandle));
		ladd(bdevh,newhandle);
		iter = iter->next;
	}
	
	iter = bdevh->head;
	for(int i = 0; i < bdevh->size; i++) {
		dev_open(iter->value);
        printf("----------\n");
		dev_print(iter->value);
        printf("----------\n");
		iter = iter->next;
	}

    mod_open(admin,bdevh->head->value);
    int handler = mod_open(distanc,bdevh->head->value);

    unsigned char opcode[1] = { 0x01 };
    dev_write_to(bdevh->head->value, opcode, 1, handler);
    unsigned char raw[6];
    dev_read(bdevh->head->value, raw, 6);
    printf("Distance[%d]: {%d}\n", handler, 65536 - (raw[4] + raw[5] * 256));
    
    iter = bdevh->head;
	for(int i = 0; i < bdevh->size; i++) {
        libusb_close(iter->value);
		iter = iter->next;
	}

	lfree(butias_devices, 0);
    lfree(bdevh, 0);
	libusb_exit(context);
	return 0;

}
