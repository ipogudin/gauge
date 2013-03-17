/*
 * platform.h
 *
 *  Created on: Mar 2, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include <pthread.h>

//concurrency utils
#define MAX_THREAD_NAME_LENGTH 16

typedef pthread_t thread_id;

struct thread_group {
  char* name;
};

struct thread {
  char* name;
  thread_id id;
};

extern struct thread* current_thread();

/* Set a new name for a thread and copy a new name to the thread structure */
extern void set_thread_name(struct thread* t, const char* name);

extern void set_name_to_current_thread(char* name);

extern void free_thread(struct thread* t);
//end of concurrency utils

#endif /* PLATFORM_H_ */
