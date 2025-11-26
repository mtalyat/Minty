#pragma once
#include "Minty/Core/Types.h"
#include <iostream>
#include <format>
#include <filesystem>

#pragma region Debug

#ifdef NDEBUG
#define MINTY_RELEASE
#endif // NDEBUG
#if defined(_DEBUG) || !defined(MINTY_RELEASE)
#define MINTY_DEBUG
#endif // _DEBUG
#if !defined(MINTY_DEBUG) && !defined(MINTY_RELEASE)
#error "Either MINTY_DEBUG or MINTY_RELEASE must be defined."
#endif // !MINTY_DEBUG && !MINTY_RELEASE

#pragma endregion

#pragma region Function

#define MINTY_ENUM_OPERATORS(type) inline Bool operator!(type const value) { return static_cast<Size>(value) == 0; } \
inline Bool operator<(type const left, type const right) { return static_cast<Size>(left) < static_cast<Size>(right); } \
inline Bool operator>(type const left, type const right) { return static_cast<Size>(left) > static_cast<Size>(right); }

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
