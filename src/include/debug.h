#ifndef _BUTIAC_DEBUG_H_
#define _BUTIAC_DEBUG_H_

#define ERROR_H "[Error]: "
#define WARN_H  "[Warning]: "

#define DEBUG_PASSED_NULL_PTR(a) \
        if(!(a)) { \
                printf("%scalled %s with null pointer at %d in file %s.\n", ERROR_H, __func__, __LINE__, __FILE__); \
        }

#define CHECK_LIBUSB_RETURNED(a) \
        if((a) < 0) { \
            printf("%slibusb returned error '%d' at %d in file %s.\n", ERROR_H, (a), __LINE__, __FILE__); \
            return (a); \
        }

#define CHECK_MALLOC_RETURNED(a) \
        if(!(a)) { \
            printf("%smalloc returned null pointer at %d in file %s.\n", ERROR_H, __LINE__, __FILE__); \
            return 1; \
        }

#endif
