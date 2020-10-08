#ifndef UTILITY_HPP
#define UTILITY_HPP

#if defined(BUILD_DEBUG)
#include <assert.h>
#define ASSERT(e) assert(e)
#else
#define ASSERT(e) ((void)0)
#endif

#define PERSISTENT static
#define GLOBAL     static
#define INTERNAL   static

typedef  uint8_t  U8;
typedef uint16_t U16;
typedef uint32_t U32;
typedef uint64_t U64;
typedef   int8_t  S8;
typedef  int16_t S16;
typedef  int32_t S32;
typedef  int64_t S64;

struct Vec2  { float x, y;       };
struct Vec3  { float x, y, z;    };
struct Vec4  { float x, y, z, w; };
struct Color { float r, g, b, a; };
struct Rect  { float x, y, w, h; };

// We store colors as four floating-point values whereas SDL handles colors as
// four U8 values. This function is used to map from our color range to SDL's.
// For example the following Color values will map to SDL_Color values like so:
//
//    Color { 1.0, 1.0, 1.0, 1.0 }  ==>  SDL_Color { 255, 255, 255, 255 }
//    Color { 0.5, 0.2, 0.7, 1.0 }  ==>  SDL_Color { 127,  51, 178, 255 }

INTERNAL SDL_Color ColorToSDLColor (Color color);
INTERNAL Color     MakeColor       (float r, float g, float b, float a = 1.0f);

// Alert message box.

GLOBAL constexpr int ALERT_BUTTON_YES_NO_CANCEL = MB_YESNOCANCEL;
GLOBAL constexpr int ALERT_BUTTON_YES_NO        = MB_YESNO;
GLOBAL constexpr int ALERT_BUTTON_OK            = MB_OK;
GLOBAL constexpr int ALERT_BUTTON_OK_CANCEL     = MB_OKCANCEL;

GLOBAL constexpr int ALERT_TYPE_INFO    = MB_ICONINFORMATION;
GLOBAL constexpr int ALERT_TYPE_WARNING = MB_ICONWARNING;
GLOBAL constexpr int ALERT_TYPE_ERROR   = MB_ICONERROR;

GLOBAL constexpr int ALERT_RESULT_INVALID = 0;
GLOBAL constexpr int ALERT_RESULT_CANCEL  = IDCANCEL;
GLOBAL constexpr int ALERT_RESULT_OK      = IDOK;
GLOBAL constexpr int ALERT_RESULT_NO      = IDNO;
GLOBAL constexpr int ALERT_RESULT_YES     = IDYES;

INTERNAL int ShowAlert (std::string title, std::string msg, int type, int buttons);

// Some utility functions.

INTERNAL std::vector<std::string> TokenizeString (std::string str, char delim);

INTERNAL std::string FixPathSlashes (std::string path_name);
INTERNAL std::string FormatStringV  (const char* format, va_list args);
INTERNAL std::string FormatTime     (const char* format);

INTERNAL float Lerp (float a, float b, float t);

INTERNAL float DegToRad (float deg);
INTERNAL float RadToDeg (float rad);

INTERNAL Vec2 RotateVec2 (Vec2 vec, float rad);

INTERNAL float SinRange (float min, float max, float t);

INTERNAL float RoundToMultiple (float num, float multiple);

// Random functions.

INTERNAL void  RandomSeed       (int seed = -1);
INTERNAL int   RandomRange      (int min, int max); // Inclusive!
INTERNAL int   Random           ();
INTERNAL float RandomFloatRange (float min, float max); // Inclusive!
INTERNAL float RandomFloat      ();

#endif /* UTILITY_HPP */
