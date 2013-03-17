/*
 * check_configuration.c
 *
 *  Created on: Mar 10, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#include <tests/tests.h>
#include <utils/platform.h>

START_TEST(test_current_thread)
  struct thread* ct = current_thread();
  fail_unless(ct->id != 0, "Thread's id isn't set");
  fail_unless(ct->name != 0, "Thread's name isn't set");
  size_t l = strlen(ct->name);
  fail_unless(
      l > 0 && l <= MAX_THREAD_NAME_LENGTH,
      "Thread's name must be greater than 0 and less than or equal to %u, actual value %u",
      MAX_THREAD_NAME_LENGTH,
      l);
  free_thread(ct);
END_TEST

START_TEST(test_set_thread_name)
  struct thread* ct = current_thread();
  char* old_name = malloc(sizeof(char) * MAX_THREAD_NAME_LENGTH);
  strncpy(old_name, ct->name, MAX_THREAD_NAME_LENGTH);
  char* new_name = "current_thread1";
  set_thread_name(ct, new_name);
  fail_unless(
      strncmp(ct->name, new_name, MAX_THREAD_NAME_LENGTH) == 0,
      "The name field in the thread structure must be equal to the new name."
      );
  free_thread(ct);
  ct = current_thread();
  fail_unless(
        strncmp(ct->name, new_name, MAX_THREAD_NAME_LENGTH) == 0,
        "The name of a thread must be equal to the new name."
        );
  //returning a previous value
  set_thread_name(ct, old_name);
  free(old_name);
  free_thread(ct);
END_TEST

START_TEST(test_set_name_to_current_thread)
  struct thread* ct = current_thread();
  char* old_name = malloc(sizeof(char) * MAX_THREAD_NAME_LENGTH);
  strncpy(old_name, ct->name, MAX_THREAD_NAME_LENGTH);
  char* new_name = "current_thread2";
  set_name_to_current_thread(new_name);
  free_thread(ct);
  ct = current_thread();
  fail_unless(
        strncmp(ct->name, new_name, MAX_THREAD_NAME_LENGTH) == 0,
        "The name of a thread must be equal to the new name."
        );
  //returning a previous value
  set_name_to_current_thread(old_name);
  free(old_name);
  free_thread(ct);
END_TEST

BEGIN
  SUITE("Platform")
    CASE("Concurrency")
      TEST(test_current_thread)
      TEST(test_set_thread_name)
      TEST(test_set_name_to_current_thread)
    END_CASE
  END_SUITE
END
