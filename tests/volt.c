#include "butiac.h"

int main(int argc, char **argv) {

    libusb_context *context = NULL;
	CHECK_LIBUSB_RETURNED(libusb_init(&context));

	board *robot;
	int ret = butiac_init_singleboard(&robot);
	DEBUG_PRINT_D("Board init: ", ret)
	CHECK_LIBUSB_RETURNED(ret)

	module vol = { robot, volt, 1, 0 };
	DEBUG_PRINT_F("Voltage module @ 1: ", mod_getvaluef(&vol))

	board_close(robot);

	libusb_exit(context);
	return 0;

}
