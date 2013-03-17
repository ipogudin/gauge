/*
 * linux.c
 *
 *  Created on: Mar 2, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */
#include <utils/platform.h>

struct thread* current_thread()
{
  struct thread* result_thread = malloc(sizeof(struct thread));
  result_thread->id = pthread_self();
  char* name = malloc(sizeof(char) * MAX_THREAD_NAME_LENGTH);
  pthread_getname_np(result_thread->id, name, MAX_THREAD_NAME_LENGTH);
  result_thread->name = name;
  return result_thread;
}

void set_thread_name(struct thread* t, const char* name)
{
  pthread_setname_np(t->id, name);
  strncpy(t->name, name, MAX_THREAD_NAME_LENGTH);
}

void set_name_to_current_thread(char* name)
{
  thread_id id = pthread_self();
  pthread_setname_np(id, name);
}

void free_thread(struct thread* t)
{
  free(t->name);
  free(t);
}
