#include "com_usb.h"

void dev_print(libusb_device_handle *devh) {

	unsigned char name[64];
	unsigned char copy[64];
	unsigned char sn[64];

	libusb_get_string_descriptor_ascii(devh,1,name,64);
	libusb_get_string_descriptor_ascii(devh,2,copy,64);
	libusb_get_string_descriptor_ascii(devh,3,sn,  64);

	printf("Name: %s\nCopy: %s\nSn: %s\n", name, copy, sn);

}

int dev_open(libusb_device_handle *devh) {

	int active = libusb_kernel_driver_active(devh, USB4ALL_INTERFACE);
	if(active == 1) {
		libusb_detach_kernel_driver(devh, USB4ALL_INTERFACE);
		active = 0;
	}
	int claim = libusb_claim_interface(devh, USB4ALL_INTERFACE);
	int set_conf = libusb_set_configuration(devh, USB4ALL_CONFIGURATION);
	return 0;

}

int dev_read(libusb_device_handle *devh, unsigned char* data, size_t size) {

	int transferred = 0;
	return libusb_bulk_transfer(devh, ADMIN_MODULE_OUT_ENDPOINT, data, size, &transferred, TIMEOUT);	

}

int dev_write(libusb_device_handle *devh, unsigned char* data, size_t size) {

	int transferred = 0;
	return libusb_bulk_transfer(devh, ADMIN_MODULE_IN_ENDPOINT, data, size, &transferred, TIMEOUT);

}

int dev_write_to(libusb_device_handle *devh, unsigned char* data, size_t size, int handler) {
    printf("Sending %lu bytes to %d.\n", size + 3, handler);
    unsigned char *payload = malloc( 3 + size );
    payload[0] = handler * 8;
    payload[1] = 3 + size;
    payload[2] = NULL_BYTE;
    for(int i = 3; i < size + 3; i++) {
        payload[i] = data[i - 3];
    }
    printf("Write: %d\n", dev_write(devh, payload, 3 + size));
    return 0;
}

list* cu_find(void) {
	
	list *list = lnew();
	libusb_device **devs;
	ssize_t found = libusb_get_device_list(NULL,&devs);

	for(int i = 0; i < found; i++) {
		struct libusb_device_descriptor desc;
		libusb_get_device_descriptor(devs[i],&desc);

		if(desc.idVendor == USB4ALL_VENDOR && desc.idProduct == USB4ALL_PRODUCT){

			ladd(list,devs[i]);
			
		}
	}
	libusb_free_device_list(devs,1);
	
	return list;
	
}
