#pragma once

#ifdef MINTY_EXPORTS
#define MINTY_API __declspec(dllexport)
#else
#define MINTY_API __declspec(dllimport)
#endif