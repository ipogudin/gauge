/*
 * tests.h
 *
 *  Created on: Mar 16, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#ifndef TESTS_H_
#define TESTS_H_

#include <stdlib.h>
#include <check.h>

#define BEGIN \
int main (void)\
{\
  int number_failed;\
  SRunner *sr = srunner_create(NULL);

#define SUITE(__test_suite_title)\
{\
  Suite *test_suite = suite_create(__test_suite_title);

#define CASE(__test_case_title)\
{\
  TCase *test_case = tcase_create(__test_case_title);\

#define TEST(__test_name)\
  tcase_add_test(test_case, __test_name);

#define END_CASE\
  suite_add_tcase(test_suite, test_case);\
}

#define END_SUITE\
  srunner_add_suite(sr, test_suite);\
}

#define END\
  srunner_run_all(sr, CK_NORMAL);\
  number_failed = srunner_ntests_failed(sr);\
  srunner_free(sr);\
  return ((number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE);\
}

#endif /* TESTS_H_ */
