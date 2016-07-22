#include "butiac.h"
#include <unistd.h>

int main(int argc, char **argv) {

    libusb_context *context = NULL;
	CHECK_LIBUSB_RETURNED(libusb_init(&context));

	board *robot;
	int ret = butiac_init_singleboard(&robot);
	DEBUG_PRINT_D("Board init: ", ret)
	CHECK_LIBUSB_RETURNED(ret)

	//module mot = { robot, motors, 8, 1 };
    //DEBUG_PRINT_D("Open module motors: ", mod_open(&mot));
    b_set_motors_speed(robot, 1, 1000, 1, 1000);
    sleep(5);
    b_set_motors_speed(robot, 0, 0, 0, 0);

	board_close(robot);

	libusb_exit(context);
	return 0;

}
