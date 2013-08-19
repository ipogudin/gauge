/*
 * throwerd.cc
 *
 *  Created on: Apr 21, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#include "Thrower.h"

int main(int argc, char **argv) {
  thrower::Thrower thrower;
  return thrower.run(argc, argv);
}
