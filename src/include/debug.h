#ifndef _BUTIAC_DEBUG_H_
#define _BUTIAC_DEBUG_H_

//Text colors

#define KRST  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#ifdef DEBUG_LOG

    #define WARN_H  "[Warning]: "
    #define INFO_H  "[Info]: "

    #define DEBUG_PASSED_NULL_PTR(a) \
            if(!(a)) { \
                    printf(KYEL "%s " KRST "called %s with null pointer @ line %d in file '%s'.\n", WARN_H, __func__, __LINE__, __FILE__); \
            }

    #define DEBUG_PRINT_D(a, b) printf(KBLU "%s" KRST "%s%d @ line %d in file '%s'.\n", INFO_H, a, (b), __LINE__, __FILE__);
    #define DEBUG_PRINT_S(a, b) printf(KBLU "%s" KRST "%s%s @ line %d in file '%s'.\n", INFO_H, a, b, __LINE__, __FILE__);

#else
    
    #define DEBUG_PASSED_NULL_PTR(a) a;
    #define DEBUG_PRINT_D(a, b) b;
    #define DEBUG_PRINT_S(a, b) b;

#endif

#ifdef ERROR_CHECK

    #define ERROR_H "[Error]: "
    #define PANIC_H "[PANIC]: "

    #define CHECK_LIBUSB_RETURNED(a) \
            if((a) < 0) { \
                printf(KRED "%s" KRST "libusb returned error '%d' @ line %d in file '%s'.\n", ERROR_H, (a), __LINE__, __FILE__); \
                return (a); \
            }

    #define CHECK_LIBUSB_RETURNED_PTR(a) \
            if((a) < 0) { \
                printf(KRED "%s" KRST "libusb returned error '%d' @ line %d in file '%s'.\n", ERROR_H, (a), __LINE__, __FILE__); \
                return NULL; \
            }

    #define CHECK_MALLOC_RETURNED(a) \
            if(!(a)) { \
                printf(KRED "%s" KRST "smalloc returned null pointer @ line %d in file '%s'.\n", ERROR_H, __LINE__, __FILE__); \
                return -69; \
            }

    #define PANIC(a) printf(KRED "%s" KRST "%s @ line %d in file '%s'.\n", PANIC_H, a, __LINE__, __FILE__); exit(-77);


#else

    #define CHECK_LIBUSB_RETURNED(a) a;
    #define CHECK_LIBUSB_RETURNED_PTR(a) a;
    #define CHECK_MALLOC_RETURNED(a) a;
    #define PANIC(a) a;

#endif

#endif

