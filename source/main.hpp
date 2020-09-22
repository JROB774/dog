#ifndef MAIN_HPP
#define MAIN_HPP

#include <SDL2/SDL.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Macros for memory allocation functions to perform the C++ casts.
#define MALLOC(t,sz) ((t*)(malloc((sz)*sizeof(t))))
#define FREE(ptr) free(ptr)

// Custom assert macro that just calls C's assert() function. The only
// difference is that this macro can be toggled with BUILD_DEBUG.
#if defined(BUILD_DEBUG)
#include <assert.h>
#define ASSERT(e) assert(e)
#else
#define ASSERT()
#endif

// Maximum and miminum macros.
#define MAX(a,b) (((a)<(b)) ? (b) : (a))
#define MIN(a,b) (((a)<(b)) ? (a) : (b))

// More descriptive definitions for the static keyword.
#define PERSISTENT static
#define GLOBAL     static
#define INTERNAL   static

// Short-hand type definitions for fixed-width integral types.
typedef  uint8_t  U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;
typedef   int8_t  S8;
typedef  int16_t S16;
typedef  int32_t S32;
typedef  int64_t S64;

// Header includes.
#include "utility.hpp"
#include "image.hpp"
#include "window.hpp"
#include "renderer.hpp"
#include "timer.hpp"
#include "input.hpp"
#include "map.hpp"
#include "dog.hpp"
#include "game.hpp"

// Source includes.
#include "utility.cpp"
#include "image.cpp"
#include "window.cpp"
#include "renderer.cpp"
#include "timer.cpp"
#include "input.cpp"
#include "map.cpp"
#include "dog.cpp"
#include "game.cpp"

#endif /* MAIN_HPP */
