/**
 * @file ElementsLogging.h
 * @date January 13, 2014
 * @author Nikolaos Apostolakos
 */

#ifndef ELEMENTSLOGGING_H
#define	ELEMENTSLOGGING_H

#include <string>
#include <sstream>
#include <boost/filesystem.hpp>
#include <log4cpp/Category.hh>
#include "ElementsKernel/Export.h" // ELEMENTS_API

/**
 * @class ElementsLogging
 * 
 * @brief Logging API of the Elements framework
 * 
 * 
 * The ElementsLogging class provides the logging API of the Elements framework.
 * To use the logging API the ElementsLogging::getLogger method can be used to
 * retrieve a logger instance, which can be further used for logging messages 
 * of different severities. For construction of more complicated messages, the
 * printf style and stream style syntax are supported. For example:
 * 
 * \code
 * ElementsLogging logger = ElementsLogging::getLogger("name");
 * logger.debug("A debug message");
 * logger.info("A value %d in a printf style info message", 15);
 * logger.error() << "A value " << 15 << " in a steam style error message";
 * \endcode
 * 
 * The name given as parameter of the ElementsLogging::getLogger method can be
 * used for identification of the log messages and for further tuning of the
 * underlying logging framework.
 * 
 * By default the logging level is set to INFO and the default behavior is to
 * forward all the messages to the standard error stream. This behavior can be
 * modified by using the method ElementsLogging::setLevel, which can be used
 * to set the level to show, and the method ElementsLogging::setLogFile, which
 * can be used to redirect the messages in a file (in addition to the standard
 * error stream). Note that these methods have a global effect to the application.
 * 
 * If the ElementsProgram API is used, the logging level and the log file
 * can be set by using the command line parameters <b>--log-level</b> and
 * <b>--log-file</b> and no direct use of the ElementsLogging::setLevel and
 * ElementsLogging::setLogFile methods is necessary. Exception of this rule is
 * any log messages which are sent before the command line parameters are handled
 * (like global or static variable initializations, or any other action before
 * the call of the main method). These messages (without an explicit call to the
 * ElementsLogging::setLogFile method) will only appear in the standard error
 * stream.
 */
class ElementsLogging {
  
private:
  
  // We declare the LogMessageStream here because it is used from the public
  // functions. It is defined in the private section at the end.
  class LogMessageStream;
  
public:

  /**
   * The different available levels of logging
   */
  typedef enum {
    /// Panic messages (affecting multiple apps/servers/sites)
    NONE = 0,
    /// Very severe error events that will lead the application to abort
    FATAL = 100,
    /// Error events that might still allow the application to continue running
    ERROR = 200,
    /// Designates potentially harmful situations
    WARN = 300,
    /// Informational messages that highlight the progress of the application
    INFO = 400,
    /// Fine-grained informational events
    DEBUG = 500
  } LoggingLevel;
  
  /**
   * Returns an instance of ElementsLogging which can be used for logging
   * messages of different severities.
   * @param name The name to use for identifying the logger messages
   * @return A logger instance
   */
  ELEMENTS_API static ElementsLogging getLogger(const std::string& name);
  
  /**
   * @brief
   * Sets the global message level
   * @details
   * This call has effect to all the loggers already retrieved as well as loggers
   * which will be retrieved in the future. Exceptions are loggers which have
   * been fine tuned using the underlying framework configuration methods.
   * 
   * @param level The new message level
   */
  static void setLevel(LoggingLevel level);
  
  /**
   * @brief
   * Sets the file to store the log messages
   * @details
   * This call has effect to all the loggers already retrieved, as well as loggers
   * which will be retrieved in the future. There can be only one global file
   * in which the messages are redirected. Multiple calls of this method will
   * just switch the file the messages are stored in. Note that this method does
   * not affect any file handlers attached to specific loggers by using the
   * underlying framework configuration methods.
   * 
   * If an empty string is given as fileName, then the loggers will stop storing
   * the messages in any files.
   * 
   * @param fileName The file where the log messages will be stored
   */
  static void setLogFile(const boost::filesystem::path& fileName);
  
  /**
   * Logs a debug message.
   * @param logMessage The message to log
   */
  void debug(const std::string& logMessage) {
    m_log4cppLogger.debug(logMessage);
  }

  /**
   * Logs a debug message using format specifiers.
   * @param stringFormat The message containing the format specifiers
   * @param args The values to replace the format specifiers with
   */
  template<typename ...Args>
  void debug(const char *stringFormat, Args &&...args) {
    m_log4cppLogger.debug(stringFormat, std::forward<Args>(args)...);
  }
  
  /**
   * Returns an object which can be used for logging a debug message using the
   * "<<" operator.
   * @return An object used for logging a debug message using the "<<" opearator
   */
  LogMessageStream debug() {
    return LogMessageStream {m_log4cppLogger, &log4cpp::Category::debug};
  }

  /**
   * Logs an info message.
   * @param logMessage The message to log
   */
  void info(const std::string& logMessage) {
    m_log4cppLogger.info(logMessage);
  }

  /**
   * Logs an info message using format specifiers.
   * @param stringFormat The message containing the format specifiers
   * @param args The values to replace the format specifiers with
   */
  template<typename ...Args>
  void info(const char *stringFormat, Args &&...args) {
    m_log4cppLogger.info(stringFormat, std::forward<Args>(args)...);
  }
  
  /**
   * Returns an object which can be used for logging a info message using the
   * "<<" operator.
   * @return An object used for logging a info message using the "<<" opearator
   */
  LogMessageStream info() {
    return LogMessageStream {m_log4cppLogger, &log4cpp::Category::info};
  }

  /**
   * Logs a warning message.
   * @param logMessage The message to log
   */
  void warn(const std::string& logMessage) {
    m_log4cppLogger.warn(logMessage);
  }

  /**
   * Logs a warning message using format specifiers.
   * @param stringFormat The message containing the format specifiers
   * @param args The values to replace the format specifiers with
   */
  template<typename ...Args>
  void warn(const char *stringFormat, Args &&...args) {
    m_log4cppLogger.warn(stringFormat, std::forward<Args>(args)...);
  }
  
  /**
   * Returns an object which can be used for logging a warn message using the
   * "<<" operator.
   * @return An object used for logging a warn message using the "<<" opearator
   */
  LogMessageStream warn() {
    return LogMessageStream {m_log4cppLogger, &log4cpp::Category::warn};
  }

  /**
   * Logs an error message.
   * @param logMessage The message to log
   */
  void error(const std::string& logMessage) {
    m_log4cppLogger.error(logMessage);
  }

  /**
   * Logs an error message using format specifiers.
   * @param stringFormat The message containing the format specifiers
   * @param args The values to replace the format specifiers with
   */
  template<typename ...Args>
  void error(const char *stringFormat, Args &&...args) {
    m_log4cppLogger.error(stringFormat, std::forward<Args>(args)...);
  }
  
  /**
   * Returns an object which can be used for logging a error message using the
   * "<<" operator.
   * @return An object used for logging a error message using the "<<" opearator
   */
  LogMessageStream error() {
    return LogMessageStream {m_log4cppLogger, &log4cpp::Category::error};
  }

  /**
   * Logs a fatal message.
   * @param logMessage The message to log
   */
  void fatal(const std::string& logMessage) {
    m_log4cppLogger.fatal(logMessage);
  }

  /**
   * Logs a fatal message using format specifiers.
   * @param stringFormat The message containing the format specifiers
   * @param args The values to replace the format specifiers with
   */
  template<typename ...Args>
  void fatal(const char *stringFormat, Args &&...args) {
    m_log4cppLogger.fatal(stringFormat, std::forward<Args>(args)...);
  }
  
  /**
   * Returns an object which can be used for logging a fatal message using the
   * "<<" operator.
   * @return An object used for logging a fatal message using the "<<" opearator
   */
  LogMessageStream fatal() {
    return LogMessageStream {m_log4cppLogger, &log4cpp::Category::fatal};
  }
  
private:
  
  ElementsLogging(log4cpp::Category& log4cppLogger);
  
  log4cpp::Category& m_log4cppLogger;
  
  /**
   * @class LogMessageStream
   * @brief A helper class for logging messages using the "<<" operator
   * @details
   * Each instance of the LogMessageStream class is used for logging one single
   * message. It keeps a reference of the logger to use and a pointer of the
   * related function (to allow different logging levels). The message is logged
   * during the destruction of the object. Instances can only be retrieved by
   * using the ElementsLogging::debug, ElementsLogging::info, etc methods.
   */
  class LogMessageStream {
    using P_log_func = void (log4cpp::Category::*)(const std::string&);
  public:
    LogMessageStream(log4cpp::Category& logger, P_log_func log_func);
    LogMessageStream(LogMessageStream&& other);
    ~LogMessageStream();
    template <typename T>
    LogMessageStream& operator<<(const T& m) {
      m_message << m;
      return *this;
    }
  private:
    log4cpp::Category& m_logger;
    P_log_func m_log_func;
    std::stringstream m_message {};
  };
  
}; /* ElementsLogging */

#endif	/* ELEMENTSLOGGING_H */

