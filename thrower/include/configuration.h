/*
 * configuration.h
 *
 *  Created on: Mar 8, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#include <stdlib.h>

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#define option_type int
#define O_PARAMETER 1
#define O_FLAG 2

#define option_value_type char
#define OV_UNDEFINED '\0'
#define OV_UINT 'u'
#define OV_INT 'i'
#define OV_STRING 's'

struct configuration_option {
  char short_name;
  char* name;
  option_type type;
  option_value_type value_type;
  union option_value {
    void* undefined;
    unsigned int ui_value;
    int i_value;
    char* s_value;
  } default_value;
  char* description;
};

struct configuration_element {
  char* name;
};

/*
 * Initialize configuration with command line arguments
 */
extern int init_configuration(int argc, char *argv[]);

extern struct configuration_element* get_configuration_element(char* name);

#endif /* CONFIGURATION_H_ */
