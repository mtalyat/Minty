#pragma once
#include <iostream>
#include <format>
#include <filesystem>

#ifdef NDEBUG
#define MINTY_RELEASE
#else
#define MINTY_DEBUG
#endif // NDEBUG

#define MINTY_DEBUG_INFO(message) "[" << std::filesystem::path(__FILE__).filename().string() << "][" << __func__ << "()][line " << __LINE__ << "] -> " << message

#define MINTY_LOG(message) std::cout << message << std::endl;

#define MINTY_ERROR(message) std::cerr << "ERROR: " << MINTY_DEBUG_INFO(message) << std::endl;

#ifdef MINTY_DEBUG
#define MINTY_ABORT(message) { std::cerr << "FATAL ERROR: " << MINTY_DEBUG_INFO(message) << std::endl; throw std::runtime_error(message); }
#else
#define MINTY_ABORT(message)
#endif // MINTY_DEBUG

#ifdef MINTY_DEBUG
#define MINTY_ASSERT(expression, message) if(!(expression)) MINTY_ABORT("(" #expression ") failed: " #message)
#else
#define MINTY_ASSERT(expression, message)
#endif // MINTY_DEBUG