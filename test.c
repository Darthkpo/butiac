#include "com_usb.h"

int main (int argc, char** argv) {

	libusb_context *context = NULL;
	printf("%d\n", libusb_init(&context)); //TODO ERROR CHECKING
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
		dev_print(iter->value);
		iter = iter->next;
	}

	unsigned char openadmin[12] = { 0, 12, 0, 0, 1, 1, 97, 100, 109, 105, 110, 0 };
	printf("Write: %d\n", dev_write(bdevh->head->value, openadmin, 12));
	unsigned char openresp[5];
	printf("Read: %d\n", dev_read(bdevh->head->value, openresp, 5));
	
	printf("%d\n", openresp[4]);

    unsigned char getversion[4] = { 0, 4, 0, 254 };
	printf("Write: %d\n", dev_write(bdevh->head->value, getversion, 4));
	unsigned char version[5];
	printf("Read: %d\n", dev_read(bdevh->head->value, version, 5));
	
	printf("%d\n", version[4]);

	lfree(butias_devices, 0);	
	libusb_exit(context);
	return 0;

}
