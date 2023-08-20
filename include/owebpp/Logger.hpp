/*************************************************************************************
 *	MIT License
 *
 *	Copyright (c) 2023 Oliver Gibson
 *
 *	Permission is hereby granted, free of charge, to any person obtaining a copy
 *	of this software and associated documentation files (the "Software"), to deal
 *	in the Software without restriction, including without limitation the rights
 *	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *	copies of the Software, and to permit persons to whom the Software is
 *	furnished to do so, subject to the following conditions:
 *
 *	The above copyright notice and this permission notice shall be included in all
 *	copies or substantial portions of the Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *	SOFTWARE.
*************************************************************************************/
#ifndef OWEBPP_LOGGER_HPP
#define OWEBPP_LOGGER_HPP

#include <chrono>
#include <iomanip>
#include <iostream>
#include <memory>
#include <source_location>

// This macro allows to choose if the metadata (file, function name, line and column should be printed since it might contain sensitive information.
#ifdef DISABLE_METADATA_LOG
    #define OWEBPP_LOG_DEBUG(message)    owebpp::Logger::getInstance().log(owebpp::LogLevel::LOG_DEBUG, message)
    #define OWEBPP_LOG_INFO(message)     owebpp::Logger::getInstance().log(owebpp::LogLevel::LOG_INFO, message)
    #define OWEBPP_LOG_WARNING(message)  owebpp::Logger::getInstance().log(owebpp::LogLevel::LOG_WARNING, message)
    #define OWEBPP_LOG_ERROR(message)    owebpp::Logger::getInstance().log(owebpp::LogLevel::LOG_ERROR, message)
    #define OWEBPP_LOG_FATAL(message)    owebpp::Logger::getInstance().log(owebpp::LogLevel::LOG_FATAL, message)
#else
    #define OWEBPP_LOG_DEBUG(message)    owebpp::Logger::getInstance().log(owebpp::LogLevel::LOG_DEBUG, std::source_location::current(), message)
    #define OWEBPP_LOG_INFO(message)     owebpp::Logger::getInstance().log(owebpp::LogLevel::LOG_INFO, std::source_location::current(), message)
    #define OWEBPP_LOG_WARNING(message)  owebpp::Logger::getInstance().log(owebpp::LogLevel::LOG_WARNING, std::source_location::current(), message)
    #define OWEBPP_LOG_ERROR(message)    owebpp::Logger::getInstance().log(owebpp::LogLevel::LOG_ERROR, std::source_location::current(), message)
    #define OWEBPP_LOG_FATAL(message)    owebpp::Logger::getInstance().log(owebpp::LogLevel::LOG_FATAL, std::source_location::current(), message)
#endif

/** The default time format used by the logger. */
#define DEFAULT_DATE_TIME_FORMAT "%Y-%m-%d %H:%M:%S"

/** This macro needs to be called at the beginning of the program using the framework. */
#define OWEBPP_STATIC_INIT_LOGGER std::shared_ptr<owebpp::Logger> owebpp::Logger::s_logger = nullptr;

namespace owebpp {
    /** Lists the log levels the logger has. */
    enum class LogLevel {
        LOG_DEBUG,
        LOG_INFO,
        LOG_WARNING,
        LOG_ERROR,
        LOG_FATAL
    };

    /** This is the logger used by the framework. */
    class Logger {
        public:
            /* Constructors */
            /**
             * Create a logger.
             * @param log_level The minimal logging level for a log to be written to the ouput.
             * @param output The output stream to which logs shall be written.
             * @param date_time_format The date/time format that should be used when writing logs.
             * See <a href="https://en.cppreference.com/w/cpp/io/manip/put_time">date/time formats</a>.
             */
            Logger(LogLevel minimum_log_level, const std::shared_ptr<std::ostream>& output, const std::string& date_time_format):
                m_minimum_log_level(minimum_log_level),
                m_output(output),
                m_date_time_format(date_time_format) {}

            /** Construct a default logger that writes to clog. */
            Logger():
                Logger(LogLevel::LOG_DEBUG, nullptr, DEFAULT_DATE_TIME_FORMAT) {}

            /* Deleted constructors */
            Logger(const Logger& r) = delete;
            Logger(Logger&& r) = delete;

            /* Deleted assignment operators */
            Logger& operator=(const Logger& r) = delete;
            Logger& operator=(Logger&& r) = delete;

            /* Destructor */
            virtual ~Logger() = default;

            /* Functions */
            /**
             * Convert log level to string.
             * @param log_level LogLevel to convert to string.
             * @return The LogLevel converted to a string.
             */
            static std::string logLevelToString(LogLevel log_level) {
                std::string result;
                switch(log_level) {
                    case LogLevel::LOG_DEBUG:
                        result = "DEBUG";
                        break;
                    case LogLevel::LOG_INFO:
                        result = "INFO";
                        break;
                    case LogLevel::LOG_WARNING:
                        result = "WARNING";
                        break;
                    case LogLevel::LOG_ERROR:
                        result = "ERROR";
                        break;
                    case LogLevel::LOG_FATAL:
                        result = "FATAL";
                        break;
                    default:
                        result = "!UNKNOWN!";
                        break;
                }
                return result;
            }

            /**
             * Log message and include meta data (file, line, column and function.
             * @param log_level The LogLevel of the log.
             * @param location The meta data of the function executing the log.
             * @param message The message to be logged.
             */
            void log(LogLevel log_level, const std::source_location& location, const std::string& message) {
                if(log_level >= m_minimum_log_level) {
                    const std::time_t t_c = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                    getOutput() << std::put_time(std::localtime(&t_c), m_date_time_format.c_str())
                                << " ["
                                << logLevelToString(log_level)
                                << "]: file: "
                                << location.file_name()
                                << '('
                                << location.line()
                                << ':'
                                << location.column()
                                << ") `"
                                << location.function_name()
                                << "`: "
                                << message
                                << std::endl;
                }
            }

            /**
             * Log message.
             * @param log_level The LogLevel of the log.
             * @param message The message to be logged.
             */
            void log(LogLevel log_level, const std::string& message) {
                if(log_level >= m_minimum_log_level) {
                    const std::time_t t_c = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                    getOutput() << std::put_time(std::localtime(&t_c), m_date_time_format.c_str())
                                << " ["
                                << logLevelToString(log_level)
                                << "]: "
                                << message
                                << std::endl;
                }
            }

            /**
             * Set the logger to use for logging.
             * @param logger The logger to use for logging.
             */
            static void setLogger(std::shared_ptr<Logger> logger) {
                s_logger = logger;
            }

            /* Singleton call method */
            /**
             * Get the logger instance.
             * @return The logger instance.
             */
            static Logger& getInstance() {
                if(s_logger==nullptr){
                    s_logger = std::make_unique<Logger>();
                }
                return *s_logger;
            }
        private:
            /**
             * Get the output to use for logging.
             * @return The output defined by a logger or clog.
             */
            std::ostream& getOutput() {
                if(m_output == nullptr) {
                    return std::clog;
                } else {
                    return *m_output;
                }
            }

            /* Members */
            /** The minimal log level for a message to be logged. */
            LogLevel m_minimum_log_level;

            /** The output to use to write logs. */
            std::shared_ptr<std::ostream> m_output;

            /** The date format to use to write date/time in logs. */
            std::string m_date_time_format;

            /** Singleton object */
            static std::shared_ptr<Logger> s_logger;
    };
}

#endif // OWEBPP_LOGGER_HPP
