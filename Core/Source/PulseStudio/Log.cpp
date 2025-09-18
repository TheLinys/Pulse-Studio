#include "pspch.h"

#include "Log.h"

// Get singleton instance
Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

// Constructor
Logger::Logger()
    : m_consoleLevel(LogLevel::Debug)  // Changed to show debug by default
    , m_fileLevel(LogLevel::Debug)
    , m_initialized(false)
#ifdef _WIN32
    , m_consoleHandle(nullptr)
    , m_consoleColorSupported(false)
#endif
{
}

// Destructor
Logger::~Logger() {
    shutdown();
}

// Initialize the logger
void Logger::init(const std::string& logFilePath, LogLevel consoleLevel, LogLevel fileLevel) {
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_initialized) {
        return;
    }

    m_consoleLevel = consoleLevel;
    m_fileLevel = fileLevel;

    // Open log file
    m_logFile.open(logFilePath, std::ios::out | std::ios::app);
    if (!m_logFile.is_open()) {
        std::cerr << "Failed to open log file: " << logFilePath << std::endl;
        return;
    }

    // Initialize console color support
    initConsoleColor();

    m_initialized = true;

    std::string timestamp = getTimestamp();
    std::string message = "Logger initialized successfully";
    std::string fullMessage = "[" + timestamp + "][Success] -> " + message;

    std::cout << "\033[32m" << fullMessage << "\033[0m \n";

    if (m_logFile.is_open()) {
        m_logFile << fullMessage << std::endl;
        m_logFile.flush();
    }
}
// Set console log level
void Logger::setConsoleLevel(LogLevel level) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_consoleLevel = level;
}

// Set file log level
void Logger::setFileLevel(LogLevel level) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_fileLevel = level;
}

// Core logging method
void Logger::log(LogLevel level, const std::string& message,
    const std::string& file, int line) {
    std::lock_guard<std::mutex> lock(m_mutex);

    if (!m_initialized) {
        return;
    }

    // Get timestamp
    std::string timestamp = getTimestamp();

    // Build log message in specified format
    std::stringstream logMessage;
    logMessage << "[" << timestamp << "][" << levelToString(level) << "] -> " << message;

    std::string fullMessage = logMessage.str();

    // Output to console if level is sufficient
    if (static_cast<int>(level) >= static_cast<int>(m_consoleLevel)) {
#ifdef _WIN32
        if (m_consoleColorSupported) {
            // Set console color
            std::cout << getConsoleColor(level);
            std::cout << fullMessage << std::endl;
            std::cout << getResetColor();
        }
        else {
            std::cout << fullMessage << std::endl;
        }
#else
        // Linux/macOS use ANSI color codes
        std::cout << getConsoleColor(level)
            << fullMessage
            << getResetColor()
            << std::endl;
#endif
    }

    // Output to file if level is sufficient
    if (static_cast<int>(level) >= static_cast<int>(m_fileLevel) && m_logFile.is_open()) {
        m_logFile << fullMessage << std::endl;
        m_logFile.flush(); // Ensure immediate write
    }
}

// Convenience logging methods
void Logger::debug(const std::string& message, const std::string& file, int line) {
    log(LogLevel::Debug, message, file, line);
}

void Logger::trace(const std::string& message, const std::string& file, int line) {
    log(LogLevel::Trace, message, file, line);
}

void Logger::info(const std::string& message, const std::string& file, int line) {
    log(LogLevel::Info, message, file, line);
}

void Logger::warn(const std::string& message, const std::string& file, int line) {
    log(LogLevel::Warn, message, file, line);
}

void Logger::error(const std::string& message, const std::string& file, int line) {
    log(LogLevel::Error, message, file, line);
}

void Logger::fatal(const std::string& message, const std::string& file, int line) {
    log(LogLevel::Fatal, message, file, line);
}

// Shutdown the logger
void Logger::shutdown()
{
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_initialized) {
        std::string message = "Logger shutting down";
        std::string timestamp = getTimestamp();
        std::string fullMessage = "[" + timestamp + "][Info] -> " + message;

        std::cout << fullMessage << std::endl;

        if (m_logFile.is_open()) {
            m_logFile << fullMessage << std::endl;
        }

        if (m_logFile.is_open()) {
            m_logFile.close();
        }

        m_initialized = false;
    }
}

// Get current timestamp in specified format
std::string Logger::getTimestamp() 
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;

    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y/%m/%d %H:%M:%S")
        << '.' << std::setfill('0') << std::setw(3) << ms.count();

    return ss.str();
}

// Convert log level to string with first letter capitalized
std::string Logger::levelToString(LogLevel level) 
{
    switch (level) 
    {
    case LogLevel::Debug:    return "Debug";
    case LogLevel::Trace:    return "Trace";
    case LogLevel::Info:     return "Info";
    case LogLevel::Warn:     return "Warn";
    case LogLevel::Error:    return "Error";
    case LogLevel::Fatal:    return "Fatal";
    default:                 return "Unknown";
    }
}

// Get console color code for log level
std::string Logger::getConsoleColor(LogLevel level) {
    switch (level) {
    case LogLevel::Debug:    return "\033[94m";  // Light blue
    case LogLevel::Trace:    return "\033[37m";  // Light gray
    case LogLevel::Info:     return "\033[0m";   // White (default)
    case LogLevel::Warn:     return "\033[33m";  // Orange-yellow
    case LogLevel::Error:    return "\033[91m";  // Bright red
    case LogLevel::Fatal:    return "\033[31m";  // Dark red
    default:                 return "\033[0m";   // Reset
    }
}

// Reset console color
std::string Logger::getResetColor() {
    return "\033[0m";
}

// Initialize console color support (Windows)
void Logger::initConsoleColor() {
#ifdef _WIN32
    m_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (m_consoleHandle != INVALID_HANDLE_VALUE) {
        DWORD mode;
        if (GetConsoleMode(m_consoleHandle, &mode)) {
            if (SetConsoleMode(m_consoleHandle, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING)) {
                m_consoleColorSupported = true;
            }
        }
    }
#endif
}