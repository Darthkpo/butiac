#include "butiac.h"

size_t butiac_init_multiboard(list *butia_list) {

	libusb_device **devs;
	ssize_t found = libusb_get_device_list(NULL,&devs);
    CHECK_LIBUSB_RETURNED((int)found);

	size_t butias = 0;
	for(int i = 0; i < found; i++) {
		struct libusb_device_descriptor desc;
		CHECK_LIBUSB_RETURNED(libusb_get_device_descriptor(devs[i],&desc));

		if(desc.idVendor == USB4ALL_VENDOR && desc.idProduct == USB4ALL_PRODUCT){

			butias++;
			board *current;
			CHECK_LIBUSB_RETURNED(board_open(devs[i], &current))
			ladd(butia_list,current);

		}
	}
	libusb_free_device_list(devs,1);

	return butias;

}

int butiac_init_singleboard(board **b_ptr) {

    libusb_device_handle *udev = libusb_open_device_with_vid_pid(NULL,USB4ALL_VENDOR,USB4ALL_PRODUCT);
    if(!udev)
        return -1; //Error or not found
    CHECK_LIBUSB_RETURNED(board_new(b_ptr, udev));

    return 0;

}
