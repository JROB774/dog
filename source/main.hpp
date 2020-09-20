#ifndef MAIN_HPP
#define MAIN_HPP

#include <SDL2/SDL.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

// Custom assert macro that just calls C's assert() function. The only
// difference is that this macro can be toggled with BUILD_DEBUG.
#if defined(BUILD_DEBUG)
#include <assert.h>
#define ASSERT(e) assert(e)
#else
#define ASSERT()
#endif

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
// Source includes.
#include "utility.cpp"
#include "image.cpp"
#include "window.cpp"
#include "renderer.cpp"

#endif /* MAIN_HPP */
