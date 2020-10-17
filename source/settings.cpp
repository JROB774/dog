GLOBAL constexpr const char* SETTINGS_FILE = "settings.data";

GLOBAL constexpr int   SETTINGS_DEFAULT_WINDOW_WIDTH  = 640;
GLOBAL constexpr int   SETTINGS_DEFAULT_WINDOW_HEIGHT = 480;
GLOBAL constexpr bool  SETTINGS_DEFAULT_FULLSCREEN    = false;
GLOBAL constexpr float SETTINGS_DEFAULT_SOUND_VOLUME  = 1.0f;
GLOBAL constexpr float SETTINGS_DEFAULT_MUSIC_VOLUME  = 1.0f;

#if defined(PLATFORM_WIN32)
#include "OS/win32/settings.cpp"
#elif defined(PLATFORM_WEB)
#include "OS/web/settings.cpp"
#endif
