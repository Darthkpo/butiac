#ifndef _BUTIAC_MODULE_H_
#define _BUTIAC_MODULE_H_

#include "board.h"

#define RD_VERSION 0x00
#define GET_VALUE  0x01
#define VCC        65536

enum {

    admin,
    distanc,
    grey

} typedef module_type;

typedef struct module {

    struct board *baseboard;
    module_type type;
    size_t port;
    char openable;
  

} module;

int mod_new(module **new_m_ptr, struct board *base, module_type type, size_t port);
void mod_free(module *m_ptr);
int mod_getvalue(module *m_ptr);

#endif
