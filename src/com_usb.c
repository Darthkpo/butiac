#include "com_usb.h"

//TODO: ERROR CHECKING EVERYWERE

usb_device* usb_device_new(libusb_device_handle *dev, int debug) {

	usb_device *newdev = (usb_device*) malloc(sizeof(usb_device));
	newdev->dev = dev;
	newdev->debug = debug;
	return newdev;

}

void usb_device_free(usb_device *udev) {

	libusb_close(udev->dev);
	free(udev);

}

void usb_device_print(usb_device *udev) {

	unsigned char name[64];
	unsigned char copy[64];
	unsigned char sn[64];

	libusb_get_string_descriptor_ascii(udev->dev,1,name,64);
	libusb_get_string_descriptor_ascii(udev->dev,2,copy,64);
	libusb_get_string_descriptor_ascii(udev->dev,3,sn,  64);

	printf("Name: %s\nCopy: %s\nSn: %s\n", name, copy, sn);

}

int usb_device_open(usb_device *udev) {

	int active = libusb_kernel_driver_active(udev->dev, USB4ALL_INTERFACE);
	if(active == 1)
		libusb_detach_kernel_driver(udev->dev, USB4ALL_INTERFACE);

	libusb_set_configuration(udev->dev, USB4ALL_CONFIGURATION);

	return 0;

}

/*Cambiar esto a que retorne int para checkear errores
y en cambio pasar un puntero a un buffer*/
unsigned char* usb_device_read(usb_device *udev, size_t size) {

	unsigned char *data = (unsigned char*)malloc(size);
	int transferred = 0;
	libusb_bulk_transfer(udev->dev, ADMIN_MODULE_OUT_ENDPOINT, data, size, &transferred, TIMEOUT);	
	return data;

}

int usb_device_write(usb_device *udev, unsigned char* data, size_t size) {

	int transferred = 0;
	return libusb_bulk_transfer(udev->dev, ADMIN_MODULE_IN_ENDPOINT, data, size, &transferred, TIMEOUT);

}

ssize_t cu_find(usb_device*** list) {

	libusb_device **devs = NULL;
	ssize_t tot_dev_count = 0;
	ssize_t u4b_count = 0;

	tot_dev_count = libusb_get_device_list(NULL, &devs);
	for(int i = 0; i < tot_dev_count; i++) {

		struct libusb_device_descriptor desc = {0};
		libusb_get_device_descriptor(devs[i], &desc);

		if(desc.idVendor == USB4ALL_VENDOR && desc.idProduct == USB4ALL_PRODUCT) {
		
			libusb_device_handle *newdev = NULL;
			libusb_open(devs[i],&newdev);

			if(u4b_count == 0) {
				*list = (usb_device**)malloc(sizeof(usb_device*));
				*list[0] = usb_device_new(newdev,0);
			} else {

				usb_device **tmplist = (usb_device**) malloc(u4b_count * sizeof(usb_device*));
				for(int j = 0; j < u4b_count; j++) {
					tmplist[j] = (usb_device*)malloc(sizeof(usb_device));
					memcpy(tmplist[j],list[j],sizeof(usb_device));
					free(list[j]);
				}
				free(list);
				*list = (usb_device**) malloc((u4b_count + 1) * sizeof(usb_device*));
				for(int j = 0; j < u4b_count; j++) {
					*list[j] = (usb_device*)malloc(sizeof(usb_device));
					memcpy(list[j],tmplist[j],sizeof(usb_device));
					free(tmplist[j]);
				}
				free(tmplist);
				*list[u4b_count] = usb_device_new(newdev,0);

			}

			u4b_count++;

		}

	}
	libusb_free_device_list(devs,1);

	return u4b_count;

}
