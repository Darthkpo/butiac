#include "butiac.h"
#include <unistd.h>

int main(int argc, char **argv) {

    libusb_context *context = NULL;
	CHECK_LIBUSB_RETURNED(libusb_init(&context));

	board *robot;
	int ret = butiac_init_singleboard(&robot);
	DEBUG_PRINT_D("Board init: ", ret)
	CHECK_LIBUSB_RETURNED(ret)

	module lediod = { robot, led, 1, 0 };
	DEBUG_PRINT_D("Led turn on  @ 1: ", mod_turn(&lediod, 1))
    sleep(1);
    DEBUG_PRINT_D("Led turn off @ 1: ", mod_turn(&lediod, 0))

	board_close(robot);

	libusb_exit(context);
	return 0;

}
