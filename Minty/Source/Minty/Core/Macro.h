#pragma once
#include <iostream>
#include <format>
#include <filesystem>

#pragma region Debug

#ifdef NDEBUG
#define MINTY_RELEASE
#else
#define MINTY_DEBUG
#endif // NDEBUG

#ifdef MINTY_DEBUG

// if debugging and using Visual Studio, insert debug break
#ifdef _MSC_VER
#define MINTY_BREAK() __debugbreak()
#else
#define MINTY_BREAK()
#endif // _MSC_VER

#else
#define MINTY_BREAK()
#endif // MINTY_DEBUG

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

#pragma region Tool

#define MINTY_MAKE_VERSION(major, minor, patch) (((static_cast<uint32_t>(major)) << 22U) | ((static_cast<uint32_t>(minor)) << 12U) | (static_cast<uint32_t>(patch)))

#pragma endregion
