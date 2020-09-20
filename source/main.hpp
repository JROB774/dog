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
typedef  uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef   int8_t  s8;
typedef  int16_t s16;
typedef  int32_t s32;
typedef  int64_t s64;

// Header includes.
#include "window.hpp"
// Source includes.
#include "window.cpp"

#endif /* MAIN_HPP */
