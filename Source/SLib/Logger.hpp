/**
 * @File Logger.hpp
 * @Author dfnzhc (https://github.com/dfnzhc)
 * @Date 2025/6/29
 * @Brief This file is part of SLib.
 */

#pragma once

#include <source_location>

#include <SLib/String/StringType.hpp>
#include <SLib/Math/Numeric.hpp>

namespace slib {

class Logger
{
public:
    enum class Level
    {
        Fatal,
        Error,
        Warning,
        Info,
        Trace
    };
    using enum Level;

    static Logger& Get()
    {
        static Logger logger;
        return logger;
    }

    void log(Level level, std::string_view msg, u32 indent = 0);
    void setLevel(Level level);

private:
    Logger();
    ~Logger();
};

// @formatter:off

inline void LogTrace(std::string_view msg)
{
    Logger::Get().log(Logger::Level::Trace, msg);
}

template<typename... Args>
inline void LogTrace(fmt::format_string<Args...> format, Args&&... args)
{
    Logger::Get().log(Logger::Level::Trace, fmt::format(format, std::forward<Args>(args)...));
}

inline void LogTrace(u32 indent, std::string_view msg)
{
    Logger::Get().log(Logger::Level::Trace, msg, indent);
}

template<typename... Args>
inline void LogTrace(u32 indent, fmt::format_string<Args...> format, Args&&... args)
{
    Logger::Get().log(Logger::Level::Trace, fmt::format(format, std::forward<Args>(args)...), indent);
}

inline void LogInfo(std::string_view msg)
{
    Logger::Get().log(Logger::Level::Info, msg);
}

template<typename... Args>
inline void LogInfo(fmt::format_string<Args...> format, Args&&... args)
{
    Logger::Get().log(Logger::Level::Info, fmt::format(format, std::forward<Args>(args)...));
}

inline void LogInfo(u32 indent, std::string_view msg)
{
    Logger::Get().log(Logger::Level::Info, msg, indent);
}

template<typename... Args>
inline void LogInfo(u32 indent, fmt::format_string<Args...> format, Args&&... args)
{
    Logger::Get().log(Logger::Level::Info, fmt::format(format, std::forward<Args>(args)...), indent);
}

inline void LogWarn(std::string_view msg)
{
    Logger::Get().log(Logger::Level::Warning, msg);
}

template<typename... Args>
inline void LogWarn(fmt::format_string<Args...> format, Args&&... args)
{
    Logger::Get().log(Logger::Level::Warning, fmt::format(format, std::forward<Args>(args)...));
}

inline void LogWarn(u32 indent, std::string_view msg)
{
    Logger::Get().log(Logger::Level::Warning, msg, indent);
}

template<typename... Args>
inline void LogWarn(u32 indent, fmt::format_string<Args...> format, Args&&... args)
{
    Logger::Get().log(Logger::Level::Warning, fmt::format(format, std::forward<Args>(args)...), indent);
}

namespace detail {

void LogWithSourceLocation(Logger::Level level, std::source_location sl, std::string_view msg);

template<typename... Args>
inline void LogWithSourceLocation(Logger::Level level, std::source_location sl, fmt::format_string<Args...> fmt, Args&&... args)
{
    LogWithSourceLocation(level, sl, fmt::format(fmt, std::forward<Args>(args)...));
}

} // namespace detail

#define LogError(...) detail::LogWithSourceLocation(Logger::Level::Error, std::source_location::current(), __VA_ARGS__)

#define LogFatal(...) detail::LogWithSourceLocation(Logger::Level::Fatal, std::source_location::current(), __VA_ARGS__)

// @formatter:on
} // namespace slib
