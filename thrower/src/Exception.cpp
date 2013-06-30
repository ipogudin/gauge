/*
 * Exception.cpp
 *
 *  Created on: Jun 30, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#include "Exception.h"

POCO_IMPLEMENT_EXCEPTION(ThrowerException, Poco::RuntimeException, "Thrower exception")


