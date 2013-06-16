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
    static void initialize();
    static Logger& logger(const std::string& name);
    static void setLevel(const std::string& level);

    void fatal(const std::string& msg);
    void critical(const std::string& msg);
    void error(const std::string& msg);
    void warning(const std::string& msg);
    void notice(const std::string& msg);
    void information(const std::string& msg);
    void debug(const std::string& msg);
    void trace(const std::string& msg);

    bool fatal() const;
    bool critical() const;
    bool error() const;
    bool warning() const;
    bool notice() const;
    bool information() const;
    bool debug() const;
    bool trace() const;

    Poco::Logger& logger() const;

    ~Logger();
  protected:
    Logger(Poco::Logger& logger);
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

  inline bool Logger::fatal() const
  {
    return _logger.fatal();
  }

  inline bool Logger::critical() const
  {
    return _logger.critical();
  }

  inline bool Logger::error() const
  {
    return _logger.error();
  }

  inline bool Logger::warning() const
  {
    return _logger.warning();
  }

  inline bool Logger::notice() const
  {
    return _logger.notice();
  }

  inline bool Logger::information() const
  {
    return _logger.information();
  }

  inline bool Logger::debug() const
  {
    return _logger.debug();
  }

  inline bool Logger::trace() const
  {
    return _logger.trace();
  }

  inline Poco::Logger& Logger::logger() const
  {
    return _logger;
  }
} /* namespace Thrower */

#endif /* LOGGER_H_ */
