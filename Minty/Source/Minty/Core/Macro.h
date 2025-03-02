#pragma once
#include <iostream>
#include <format>
#include <filesystem>

#define MINTY_DEBUG_INFO(message) "[" << std::filesystem::path(__FILE__).filename().string() << "][" << __func__ << "()][line " << __LINE__ << "] -> " << message

#define MINTY_LOG(message) std::cout << message << std::endl;

#define MINTY_ERROR(message) std::cerr << "ERROR: " << MINTY_DEBUG_INFO(message) << std::endl;

#define MINTY_ABORT(message) { std::cerr << "FATAL ERROR: " << MINTY_DEBUG_INFO(message) << std::endl; throw std::runtime_error(message); }

#define MINTY_ASSERT(expression, message) if(!(expression)) MINTY_ABORT("(" #expression ") failed: " #message)