/*
 * commons.h
 *
 *  Created on: Mar 31, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#ifndef COMMONS_H_
#define COMMONS_H_

typedef int bool;
#define TRUE (bool)1
#define FALSE (bool)0

enum types {
  VOID,
  STRING,
  SINT,
  USINT,
  UINT,
  INT,
  ULONG,
  LONG
};

#endif /* COMMONS_H_ */
