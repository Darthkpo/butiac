#include "com_usb.h"

int main (int argc, char** argv) {

	libusb_context *context = NULL;
	libusb_init(&context); //TODO ERROR CHECKING

	usb_device **butias = NULL;

	ssize_t butiasc = cu_find(&butias);

	for(int i = 0; i < butiasc; i++) {

		usb_device_print(butias[i]);

	}

	printf("Open: %d\n", usb_device_open(butias[0]));

	for(int i = 0; i < butiasc; i++) {

		usb_device_free(butias[i]);

	}

	free(butias);
	libusb_exit(context);
	return 0;

}
