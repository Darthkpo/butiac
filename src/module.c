#include "module.h"

unsigned char get_value[1] = { GET_VALUE };

int mod_new(module **new_m_ptr, struct board *base, module_type type, size_t port) {

   DEBUG_PASSED_NULL_PTR(base);
   module *new_mod = malloc(sizeof(module));
   CHECK_MALLOC_RETURNED(new_mod);
   new_mod->baseboard = base;
   new_mod->type = type;
   new_mod->port = port;
   if(type == admin)
       new_mod->openable = 1; //true
   *new_m_ptr = new_mod;

   return 0;

}

void mod_free(module *m_ptr) {

    DEBUG_PASSED_NULL_PTR(m_ptr);
    free(m_ptr);

}

int mod_getvalue(module *m_ptr) {

   
   CHECK_LIBUSB_RETURNED(board_send(m_ptr->baseboard, m_ptr->port, get_value, 1));
   unsigned char raw[3];
   CHECK_LIBUSB_RETURNED(board_read(m_ptr->baseboard, raw, 3));
  
   switch(m_ptr->type) {
   
   case distanc : {
       return VCC - (raw[1] + raw[2] * 256);
       break;
   }
   case grey : {
       return raw[1] + raw[2] * 256;
       break;
   }
   default : {
       break;
   }
   }

   return 0;

}
