/*
 * errors.c
 *
 *  Created on: Mar 9, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#include <utils/errors.h>

void initialize_exception_handling()
{
  exception_handler = malloc(sizeof(jmp_buf));
  block = malloc(sizeof(struct exception_block_result));
}

struct exception* exception(char* type, char* message)
{
  struct exception* e = malloc(sizeof(struct exception));
  e->type = type;
  e->message = message;
  return e;
}

void free_exception(struct exception* e)
{
  free(e);
}
