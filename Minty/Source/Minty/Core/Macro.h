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

#pragma region Function

#define MINTY_ENUM_FLAGS_OPERATORS(type) inline type operator|(type const left, type const right) { return static_cast<type>(static_cast<Size>(left) | static_cast<Size>(right)); } \
inline type operator|=(type& left, type const right) { left = left | right; return left; } \
inline type operator&(type const left, type const right) { return static_cast<type>(static_cast<Size>(left) & static_cast<Size>(right)); } \
inline type operator&=(type& left, type const right) { left = left & right; return left; } \
inline type operator~(type const value) { return static_cast<type>(~static_cast<Size>(value)); } \
inline Bool operator!(type const value) { return static_cast<Size>(value) == 0; } \
inline Bool operator<(type const left, type const right) { return static_cast<Size>(left) < static_cast<Size>(right); } \
inline Bool operator>(type const left, type const right) { return static_cast<Size>(left) > static_cast<Size>(right); }

#pragma endregion

#pragma region OS

#ifdef _WIN32
#define MINTY_WINDOWS
#elif defined(__APPLE__)
#define MINTY_APPLE
#elif defined(__linux__)
#define MINTY_LINUX
#else
#error "Unsupported operating system."
#endif

#pragma endregion