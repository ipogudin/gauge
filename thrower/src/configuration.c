/*
 * configuration.c
 *
 *  Created on: Mar 8, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#include <configuration.h>
#include <getopt.h>

static struct configuration_option configuration_options[] = {
  'd', "daemon", O_FLAG, OV_UNDEFINED, NULL,
  "sets daemon mode.",
  'h', "help", O_FLAG, OV_UNDEFINED, NULL,
  "shows help",
};

const unsigned int options_count =
    sizeof(configuration_options)/sizeof(configuration_options[0]);

int init_configuration(int argc, char *argv[])
{

  return (0);
}
