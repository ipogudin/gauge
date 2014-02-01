/*
 * Exception.h
 *
 *  Created on: Jun 30, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <Poco/Exception.h>
#include <typeinfo>

#include "commons.h"

POCO_DECLARE_EXCEPTION(Thrower_API, IncorrectStateException, Poco::LogicException)

POCO_DECLARE_EXCEPTION(Thrower_API, ManageProtocolException, Poco::RuntimeException)

#endif /* EXCEPTION_H_ */
