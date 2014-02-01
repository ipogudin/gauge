/*
 * test.cpp
 *
 *  Created on: Feb 1, 2014
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Logger.h>

int main(int argc, char** argv) {
  testing::InitGoogleMock(&argc, argv);
  INIT_TRACE_LOGGER
  return RUN_ALL_TESTS();
}

