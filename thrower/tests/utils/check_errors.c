/*
 * check_errors.c
 *
 *  Created on: Mar 24, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#include <tests/tests.h>
#include <utils/errors.h>

START_TEST(test_single_layer_exception_catching)
  initialize_exception_handling();
  int caught = 0;
  try {
    throw(exception("error", "test"));
  }
  catch(e) {
   caught = 1;
   free_exception(e);
  }
  fail_unless(
    caught,
    "A thrown exception must be caught."
    );
END_TEST

START_TEST(test_single_layer_exception_catching_without_throwing)
  initialize_exception_handling();
  int caught = 0;
  try {

  }
  catch(e) {
   caught = 1;
   free_exception(e);
  }
  fail_unless(
    caught == 0,
    "A catch block must be executed only with a thrown exception."
    );
END_TEST

START_TEST(test_single_layer_final_block_execution_after_exception_throwing)
  initialize_exception_handling();
  int finally = 0;
  try {

  }
  finally {
   finally = 1;
  }
  fail_unless(
    finally == 0,
    "A final block must be executed after exception throwing."
    );
END_TEST

BEGIN
  SUITE("Errors")
    CASE("Exceptions")
      TEST(test_single_layer_exception_catching)
    END_CASE
  END_SUITE
END
