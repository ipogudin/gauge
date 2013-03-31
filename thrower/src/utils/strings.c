/*
 * strings.c
 *
 *  Created on: Mar 31, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */
#include <stdarg.h>

char* sformat(unsigned int size, char* template, ...)
{
  char* buffer = malloc(size);
  va_list args;
  va_start(args, template);
  vsnprintf(buffer, size, template, args);
  va_end(args);
  return buffer;
}

