#include "board.h"

int main (int argc, char** argv) {

	libusb_context *context = NULL;
    CHECK_LIBUSB_RETURNED(libusb_init(&context));

	list *butias_devices = cu_find();
    DEBUG_PRINT("Butias found: ", (int)butias_devices->size);

	list *butias = lnew();

	node *iter = butias_devices->head;
	for(int i = 0; i < butias_devices->size; i++) {
		board *butia;
        DEBUG_PRINT("board_open returned: ", board_open(iter->value, &butia));
		ladd(butias,butia);
		iter = iter->next;
	}

    iter = butias->head;
	for(int i = 0; i < butias->size; i++) {
		board_close(iter->value);
		iter = iter->next;
	}

	lfree(butias_devices, 0);
    lfree(butias, 0);
	libusb_exit(context);
	return 0;

}
