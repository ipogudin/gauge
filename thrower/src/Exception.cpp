/*
 * Exception.cpp
 *
 *  Created on: Jun 30, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#include "Exception.h"

POCO_IMPLEMENT_EXCEPTION(IncorrectStateException,
    Poco::LogicException, "Incorrect state to do the current action")

POCO_IMPLEMENT_EXCEPTION(ManageProtocolException,
    Poco::RuntimeException, "Manage protocol error")
