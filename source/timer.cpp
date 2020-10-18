INTERNAL float CounterToSeconds (U64 counter)
{
    return ((float)counter / (float)gTimer.performance_frequency);
}

#if defined(PLATFORM_WIN32)
#include "OS/win32/timer.cpp"
#elif defined(PLATFORM_WEB)
#include "OS/web/timer.cpp"
#endif
