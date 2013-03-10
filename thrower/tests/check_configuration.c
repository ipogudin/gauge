/*
 * check_configuration.c
 *
 *  Created on: Mar 10, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#include <stdlib.h>
#include <check.h>

START_TEST(test_default_confiuration)
{

}
END_TEST

Suite * test_suite (void)
{
  Suite *s = suite_create("Configuration");

  /* Core test case */
  TCase *tc_core = tcase_create ("Core");
  tcase_add_test (tc_core, test_default_confiuration);
  suite_add_tcase (s, tc_core);

  return (s);
}

int main (void)
{
  int number_failed;
  Suite *s = test_suite();
  SRunner *sr = srunner_create (s);
  srunner_run_all (sr, CK_NORMAL);
  number_failed = srunner_ntests_failed (sr);
  srunner_free (sr);
  return ((number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE);
}
