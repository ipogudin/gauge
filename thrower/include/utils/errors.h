/*
 * errors.h
 *
 *  Created on: Mar 9, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#ifndef ERRORS_H_
#define ERRORS_H_

#include <stdlib.h>
#include <setjmp.h>
#include <errno.h>

struct exception {
  char* type;
  char* message;
};

struct exception_block_result {
  struct exception* exception;
};

extern void initialize_exception_handling();
extern struct exception* exception(char* type, char* message);
extern void free_exception(struct exception* e);

extern jmp_buf* exception_handler = NULL;
extern struct exception_block_result* block = NULL;

#define try \
  setjmp(exception_handler);\
  if (block->exception != NULL)

#define catch(__exception) \
  struct exception* __exception = block->exception; \
  if (__exception != NULL)

#define finally \

#define throw(_exception) \
  block->exception = _exception; \
  longjmp(exception_handler, 0);


#endif /* ERRORS_H_ */
