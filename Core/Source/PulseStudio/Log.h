#pragma once

#include "pspch.h"

// Platform-specific console color codes
#ifdef _WIN32
#include <windows.h>
#endif

// Log level enumeration - in the order you specified
enum class LogLevel 
{
    Debug,
    Trace,
    Info,
    Warn,
    Error,
    Fatal
};

// Logger singleton class
class Logger 
{
public:
    // Get singleton instance
    static Logger& getInstance();

    // Initialize the logger
    void init(const std::string& logFilePath = "C:/Log/PulseStudioLog.log",
        LogLevel consoleLevel = LogLevel::Debug,  // Changed to show debug by default
        LogLevel fileLevel = LogLevel::Debug);

    // Set log levels
    void setConsoleLevel(LogLevel level);
    void setFileLevel(LogLevel level);

    // Logging methods
    void log(LogLevel level, const std::string& message,
        const std::string& file = "", int line = -1);

    // Convenience logging methods
    void debug(const std::string& message, const std::string& file = "", int line = -1);
    void trace(const std::string& message, const std::string& file = "", int line = -1);
    void info(const std::string& message, const std::string& file = "", int line = -1);
    void warn(const std::string& message, const std::string& file = "", int line = -1);
    void error(const std::string& message, const std::string& file = "", int line = -1);
    void fatal(const std::string& message, const std::string& file = "", int line = -1);

    // Shutdown the logger
    void shutdown();

    // Disable copying and assignment
    Logger(const Logger&) = delete;
    Logger(const Logger&&) = delete;
    Logger& operator=(const Logger&) = delete;
private:
    Logger();
    ~Logger();

    // Get current timestamp in specified format
    std::string getTimestamp();

    // Convert log level to string with first letter capitalized
    std::string levelToString(LogLevel level);

    // Get console color code for log level
    std::string getConsoleColor(LogLevel level);

    // Reset console color
    std::string getResetColor();

    // Initialize console color support (Windows)
    void initConsoleColor();

    // Member variables
    bool m_initialized;
    std::ofstream m_logFile;
    LogLevel m_consoleLevel;
    LogLevel m_fileLevel;
    std::mutex m_mutex;

#ifdef _WIN32
    HANDLE m_consoleHandle;
    bool m_consoleColorSupported;
#endif
};

// Client logging macros
#define LOG_DEBUG(msg) Logger::getInstance().debug(msg, __FILE__, __LINE__)
#define LOG_TRACE(msg) Logger::getInstance().trace(msg, __FILE__, __LINE__)
#define LOG_INFO(msg) Logger::getInstance().info(msg, __FILE__, __LINE__)
#define LOG_WARN(msg) Logger::getInstance().warn(msg, __FILE__, __LINE__)
#define LOG_ERROR(msg) Logger::getInstance().error(msg, __FILE__, __LINE__)
#define LOG_FATAL(msg) Logger::getInstance().fatal(msg, __FILE__, __LINE__)

// Core logging macros
#define LOG_CORE_DEBUG(msg) Logger::getInstance().debug(msg, __FILE__, __LINE__)
#define LOG_CORE_TRACE(msg) Logger::getInstance().trace(msg, __FILE__, __LINE__)
#define LOG_CORE_INFO(msg) Logger::getInstance().info(msg, __FILE__, __LINE__)
#define LOG_CORE_WARN(msg) Logger::getInstance().warn(msg, __FILE__, __LINE__)
#define LOG_CORE_ERROR(msg) Logger::getInstance().error(msg, __FILE__, __LINE__)
#define LOG_CORE_FATAL(msg) Logger::getInstance().fatal(msg, __FILE__, __LINE__)

// VariPS macros for formatted logging (using fmt library)
#define PS_DEBUG(msg) Logger::getInstance().debug(msg, __FILE__, __LINE__)
#define PS_TRACE(msg) Logger::getInstance().trace(msg, __FILE__, __LINE__)
#define PS_INFO(msg) Logger::getInstance().info(msg, __FILE__, __LINE__)
#define PS_WARN(msg) Logger::getInstance().warn(msg, __FILE__, __LINE__)
#define PS_ERROR(msg) Logger::getInstance().error(msg, __FILE__, __LINE__)
#define PS_FATAL(msg) Logger::getInstance().fatal(msg, __FILE__, __LINE__)

// VariPS_Core macros for formatted logging (using fmt library)
#define PS_CORE_FATAL(...) Logger::getInstance().fatal(__VA_ARGS__)
#define PS_CORE_ERROR(...) Logger::getInstance().error(__VA_ARGS__)
#define PS_CORE_WARN(...) Logger::getInstance().warn(__VA_ARGS__)
#define PS_CORE_INFO(...) Logger::getInstance().info(__VA_ARGS__)
#define PS_CORE_TRACE(...) Logger::getInstance().trace(__VA_ARGS__)
#define PS_CORE_DEBUG(...) Logger::getInstance().debug(__VA_ARGS__)
