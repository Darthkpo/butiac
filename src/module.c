#include "module.h"

unsigned char get_value[1] = { GET_VALUE };
unsigned char get_version[1] = { RD_VERSION };

int mod_new(module **new_m_ptr, struct board *base, module_type type, size_t port) {

    DEBUG_PASSED_NULL_PTR(base);
    module *new_mod = malloc(sizeof(module));
    CHECK_MALLOC_RETURNED(new_mod);
    new_mod->baseboard = base;
    new_mod->type = type;
    new_mod->port = port;
    if(type == admin || type == motors)
        new_mod->openable = 1; //true
    *new_m_ptr = new_mod;

    return 0;

}

void mod_free(module *m_ptr) {

    DEBUG_PASSED_NULL_PTR(m_ptr);
    free(m_ptr);

}

int mod_getversion(module *m_ptr) {

    CHECK_LIBUSB_RETURNED(board_send(m_ptr->baseboard, m_ptr->port, get_version, 1));
    unsigned char raw[3];
    CHECK_LIBUSB_RETURNED(board_read(m_ptr->baseboard, raw, 3));

    return raw[1] + raw[2] * 256;

}

int mod_turn(module *m_ptr, char on) {

    if(m_ptr->type < 11 || m_ptr->type > 16) {
        return ERROR;
    }
    unsigned char payload[2] = { TURN, on };
    CHECK_LIBUSB_RETURNED(board_send(m_ptr->baseboard, m_ptr->port, payload, 2));
    unsigned char raw[1];
    CHECK_LIBUSB_RETURNED(board_read(m_ptr->baseboard, raw, 1));
    return raw[0];
}

float mod_getvaluef(module *m_ptr) {

    if(m_ptr->type < 8 || m_ptr->type > 10) {
        return ERROR;
    }
    CHECK_LIBUSB_RETURNED(board_send(m_ptr->baseboard, m_ptr->port, get_value, 1));
    unsigned char raw[MAX_READ_SIZE];
    CHECK_LIBUSB_RETURNED(board_read(m_ptr->baseboard, raw, 3));

    switch(m_ptr->type) {

    case res : {
        int value = raw[1] + raw[2] * 256;
        return value * 6800.0f / (VCC - value);
        break;
    }
    case temp : {
        float value = (raw[1] + raw[2] * 256) * 5.0f / VCC;
        return (value * 1000.0f) / 10;
        break;
    }
    case volt : {
        float value = (raw[1] + raw[2] * 256) * 5.0f / VCC;
        return (value * 1000.0f) / 1000;
        break;
    }

    }

}

int mod_getvalue(module *m_ptr) {

    unsigned char raw[MAX_READ_SIZE];

    switch(m_ptr->type) {

    case button : {
        CHECK_LIBUSB_RETURNED(board_send(m_ptr->baseboard, m_ptr->port, get_value, 1));
        CHECK_LIBUSB_RETURNED(board_read(m_ptr->baseboard, raw, 2));
        break;
    }

    default : {
        CHECK_LIBUSB_RETURNED(board_send(m_ptr->baseboard, m_ptr->port, get_value, 1));
        CHECK_LIBUSB_RETURNED(board_read(m_ptr->baseboard, raw, 3));
        break;
    }

    }

    switch(m_ptr->type) {

    case 1 ... 2 : {
        return VCC - (raw[1] + raw[2] * 256);
        break;
    }
    case 3 ... 6 : {
        return raw[1] + raw[2] * 256;
        break;
    }
    case button : {
        if(raw[1] != 255)
            return (1 - raw[1]);
        break;
    }
    case res : {
        DEBUG_PRINT_S("called mod_getvalue with a module type that returns float.","")
        int value = raw[1] + raw[2] * 256;
        return value * 6800 / (VCC - value);
        break;
    }
    case temp : {
        DEBUG_PRINT_S("called mod_getvalue with a module type that returns float.","")
        float value = (raw[1] + raw[2] * 256) * 5.0f / VCC;
        return (int)(value * 1000.0f) / 10;
        break;
    }
    case volt : {
        DEBUG_PRINT_S("called mod_getvalue with a module type that returns float.","")
        float value = (raw[1] + raw[2] * 256) * 5.0f / VCC;
        return (int)(value * 1000.0f) / 1000;
        break;
    }
    default : {
        break;
    }
    }

    return ERROR;

}
