#ifndef MAIN_HPP
#define MAIN_HPP

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <windows.h>
#include <dbghelp.h>

#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <ctime>

#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <random>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <SDL2/SDL_mixer.h>

#include <GON/GON.hpp>
#include <GON/GON.cpp>

// Header includes.
#include "utility.hpp"
#include "error.hpp"
#include "image.hpp"
#include "window.hpp"
#include "renderer.hpp"
#include "timer.hpp"
#include "input.hpp"
#include "mixer.hpp"
#include "animation.hpp"
#include "map.hpp"
#include "dog.hpp"
#include "world.hpp"
#include "camera.hpp"
#include "game.hpp"

// Source includes.
#include "utility.cpp"
#include "error.cpp"
#include "image.cpp"
#include "window.cpp"
#include "renderer.cpp"
#include "timer.cpp"
#include "input.cpp"
#include "mixer.cpp"
#include "animation.cpp"
#include "map.cpp"
#include "dog.cpp"
#include "world.cpp"
#include "camera.cpp"
#include "game.cpp"

#endif /* MAIN_HPP */
