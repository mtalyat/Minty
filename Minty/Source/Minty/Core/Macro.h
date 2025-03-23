#pragma once
#include "Minty/Debug/Debug.h"
#include <iostream>
#include <format>
#include <filesystem>

#pragma region Debug

#ifdef NDEBUG
#define MINTY_RELEASE
#else
#define MINTY_DEBUG
#endif // NDEBUG

#define MINTY_DEBUG_INFO(message) "[", std::filesystem::path(__FILE__).filename().string(), "][", __func__, "()][line ", __LINE__, "] -> ", message

#define MINTY_WRITE(message, color) do { Debug::set_foreground_color(color); Debug::write(message); Debug::reset(); } while(false)

#define MINTY_TAG(tag, message, color) do { Debug::write("["); MINTY_WRITE(tag, color); Debug::write("] ", message); } while(false)

#ifdef MINTY_DEBUG
#define MINTY_LOG(message) Debug::write(message)
#else
#define MINTY_LOG(message)
#endif // MINTY_DEBUG

#define MINTY_ERROR(message) MINTY_TAG("ERRR", message, Debug::Color::BrightRed)

#ifdef MINTY_DEBUG
#define MINTY_WARNING(message) MINTY_TAG("WARN", message, Debug::Color::BrightYellow)
#else
#define MINTY_WARNING(message)
#endif // MINTY_DEBUG

#ifdef MINTY_DEBUG
//#define MINTY_ABORT(message) do { std::cerr << "FATAL ERROR: " << MINTY_DEBUG_INFO(message) << std::endl; throw std::runtime_error(message); } while(false)
#define MINTY_ABORT(message) do { MINTY_TAG("ABRT", message, Debug::Color::Red); throw std::runtime_error(message); } while(false)
#else
#define MINTY_ABORT(message) MINTY_ERROR(message)
#endif // MINTY_DEBUG

#ifdef MINTY_DEBUG
#define MINTY_ASSERT(expression, message) do { if(!(expression)) { MINTY_ABORT("(" #expression ") failed: " #message); } } while(false)
#else
#define MINTY_ASSERT(expression, message)
#endif // MINTY_DEBUG

#if defined(MINTY_DEBUG)

// if debugging and using Visual Studio, insert debug break
#if defined(_MSC_VER)
#define MINTY_BREAK() __debugbreak()
#else
#define MINTY_BREAK()
#endif

#else
#define MINTY_BREAK()
#endif

#pragma endregion

#pragma region Functions

#define MINTY_TO_STRING(T) String to_string(T const value)

#define MINTY_PARSE(T, t) T parse_to_##t(String const& string);\
Bool parse_try_##t(String const& string, T& value);\
	template<> inline T parse_to<T>(String const& string) { return parse_to_##t(string); }\
	template<> inline Bool parse_try<T>(String const& string, T& value) { return parse_try_##t(string, value); }

#define MINTY_TO_STRING_PARSE(T, t) MINTY_TO_STRING(T);\
MINTY_PARSE(T, t);

#pragma endregion