#include "board.h"

int main (int argc, char** argv) {

	libusb_context *context = NULL;
    CHECK_LIBUSB_RETURNED(libusb_init(&context));

	list *butias_devices = cu_find();
    DEBUG_PRINT_D("Butias found: ", (int)butias_devices->size);

	list *butias = lnew();

	node *iter = butias_devices->head;
	for(int i = 0; i < butias_devices->size; i++) {
		board *butia;
        DEBUG_PRINT_D("board_open returned: ", board_open(iter->value, &butia));
		ladd(butias,butia);
		iter = iter->next;
	}

    module *greys;
    mod_new(&greys, butias->head->value, grey, 3);
    int value = mod_getvalue(greys);
    DEBUG_PRINT_D("Sensor value at 3: ", value);
    mod_free(greys);

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
