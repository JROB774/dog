#ifndef UTILITY_HPP
#define UTILITY_HPP

struct Vec2  { float x, y;       };
struct Vec3  { float x, y, z;    };
struct Vec4  { float x, y, z, w; };
struct Color { float r, g, b, a; };

// We store colors as four floating-point values whereas SDL handles colors as
// four U8 values. This function is used to map from our color range to SDL's.
// For example the following Color values will map to SDL_Color values like so:
//
//    Color { 1.0, 1.0, 1.0, 1.0 }  ==>  SDL_Color { 255, 255, 255, 255 }
//    Color { 0.5, 0.2, 0.7, 1.0 }  ==>  SDL_Color { 127,  51, 178, 255 }

INTERNAL SDL_Color ColorToSDLColor (Color color);

#endif /* UTILITY_HPP */
