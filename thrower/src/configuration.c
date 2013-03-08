/*
 * configuration.c
 *
 *  Created on: Mar 8, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#include "configuration.h"

struct option options[] = {
  'd', "daemon", O_FLAG, OV_UNDEFINED, NULL,
  "sets daemon mode.",
  'h', "help", O_FLAG, OV_UNDEFINED, NULL,
  "shows help",
};

int init_configuration(int argc, char *argv[])
{
  return (0);
}
