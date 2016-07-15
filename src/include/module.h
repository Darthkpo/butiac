#ifndef _BUTIAC_MODULE_H_
#define _BUTIAC_MODULE_H_

#include "board.h"

enum {

  admin,
  distanc

} typedef module_type;

struct {

  struct board *baseboard;
  module_type type;
  size_t port;
  char openable;
  

} typedef module;

#endif
