#include "com_usb.h"

int main (int argc, char** argv) {

	libusb_context *context = NULL;
	libusb_init(&context); //TODO ERROR CHECKING

	list *butias = cu_find();
	printf("Butias found: %lu\n", butias->size);
	
	lfree(butias, 0);	
	libusb_exit(context);
	return 0;

}
