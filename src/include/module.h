#ifndef _BUTIAC_MODULE_H_
#define _BUTIAC_MODULE_H_

#include "board.h"

#define RD_VERSION 0x00
#define GET_VALUE  0x01
#define TURN       0x01
#define VCC        65536
#define ERROR      -1

#define MAX_READ_SIZE 3

enum {

    admin   = 0,

    distanc = 1,
    light   = 2,

    grey    = 3,
    mod_sen_a = 4,
    mod_sen_b = 5,
    mod_sen_c = 6,
    
    button  = 7,

    res     = 8,
    temp    = 9,
    volt    = 10,

    buzzer    = 11,
    led       = 12,
    relay     = 13,
    mod_act_a = 14,
    mod_act_b = 15,
    mod_act_c = 16

} typedef module_type;

typedef struct module {

    struct board *baseboard;
    module_type type;
    size_t port;
    char openable;
  

} module;

int mod_new(module **new_m_ptr, struct board *base, module_type type, size_t port);
void mod_free(module *m_ptr);
int mod_turn(module *m_ptr, char on);
int mod_getvalue(module *m_ptr);
float mod_getvaluef(module *m_ptr);
int mod_getversion(module *m_ptr);

#endif
