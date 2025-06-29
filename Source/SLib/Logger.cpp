/**
 * @File Logger.cpp
 * @Author dfnzhc (https://github.com/dfnzhc)
 * @Date 2025/6/29
 * @Brief This file is part of SLib.
 */

#include "Logger.hpp"
#include "Error.hpp"

#include <mutex>

using namespace slib;

namespace {
constexpr inline const char* logLevelString(Logger::Level level)
{
    switch (level) {
    case Logger::Level::Fatal   : return "Fatal";
    case Logger::Level::Error   : return "Error";
    case Logger::Level::Warning : return " Warn";
    case Logger::Level::Info    : return " Info";
    case Logger::Level::Trace   : return "Trace";
    }
    SLIB_UNREACHABLE();
}

std::mutex sMutex = {};
Logger::Level sCurrentLevel =
#ifdef SLIB_ENABLE_DEBUG
    Logger::Level::Trace;
#else
    Logger::Level::Info;
#endif
} // namespace

Logger::Logger() { }

Logger::~Logger() { }

void Logger::log(Level level, std::string_view msg, u32 indent)
{
    auto lock = std::lock_guard(sMutex);

    if (level > sCurrentLevel)
        return;

    // TODO: Terminal colors
    // fmt::color color = fmt::color::white;
    // switch (level) {
    // case Fatal   : color = fmt::color::red; break;
    // case Error   : color = fmt::color::magenta; break;
    // case Warning : color = fmt::color::coral; break;
    // case Info    : color = fmt::color::green_yellow; break;
    // case Trace   : color = fmt::color::white_smoke; break;
    // }

    // TODO: [%(time)][%(thread_id)][%(short_source_location)][%(log_level)]%(tags): %(message)
    // std::print?
    const auto s = std::format("[{}]: {}{}", logLevelString(level), std::string(indent * 2, ' '), msg);
    auto& os     = std::cout;
    os << s << '\n';
    std::flush(os);
}

void Logger::setLevel(Level level)
{
    auto lock     = std::lock_guard(sMutex);
    sCurrentLevel = level;
}

void detail::LogWithSourceLocation(Logger::Level level, std::source_location sl, std::string_view msg)
{
    Logger::Get().log(level, std::format("{}: '{}' {}({}:{})", msg, sl.function_name(), sl.file_name(), sl.line(), sl.column()));
}
