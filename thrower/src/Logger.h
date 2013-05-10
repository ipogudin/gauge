/*
 * Logger.h
 *
 *  Created on: May 5, 2013
 *      Author: Ivan Pogudin <i.a.pogudin@gmail.com>
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <Poco/Logger.h>

using Poco::Logger;

namespace Thrower
{

  /*
   * The wrapper for Poco::Logger
   */
  class Logger
  {
  public:
    static Logger& logger(const std::string& name);

    void fatal(const std::string& msg);
    void critical(const std::string& msg);
    void error(const std::string& msg);
    void warning(const std::string& msg);
    void notice(const std::string& msg);
    void information(const std::string& msg);
    void debug(const std::string& msg);
    void trace(const std::string& msg);

    void setLevel(const std::string& level);
  protected:
    Logger(Poco::Logger& logger);
    virtual
    ~Logger();
  private:
    Poco::Logger& _logger;
  };

  inline void Logger::fatal(const std::string& msg)
  {
    _logger.fatal(msg);
  }

  inline void Logger::critical(const std::string& msg)
  {
    _logger.critical(msg);
  }

  inline void Logger::error(const std::string& msg)
  {
    _logger.error(msg);
  }

  inline void Logger::warning(const std::string& msg)
  {
    _logger.warning(msg);
  }

  inline void Logger::notice(const std::string& msg)
  {
    _logger.notice(msg);
  }

  inline void Logger::information(const std::string& msg)
  {
    _logger.information(msg);
  }

  inline void Logger::debug(const std::string& msg)
  {
    _logger.debug(msg);
  }

  inline void Logger::trace(const std::string& msg)
  {
    _logger.trace(msg);
  }
} /* namespace Thrower */

#endif /* LOGGER_H_ */
