GLOBAL constexpr int FRAMERATE = 60;

INTERNAL void InitFrameTimer ()
{
    gTimer.performance_frequency = SDL_GetPerformanceFrequency();
    gTimer.last_counter          = SDL_GetPerformanceCounter();
    gTimer.end_counter           = 0;
    gTimer.current_fps           = 0.0f;
    gTimer.fixed_time_step       = 1.0f / (float)FRAMERATE;
    gTimer.delta_time            = gTimer.fixed_time_step;
}

INTERNAL void CapFramerate ()
{
    gTimer.end_counter = SDL_GetPerformanceCounter();
    U64 elapsed_counter = gTimer.end_counter - gTimer.last_counter;

    float elapsed = CounterToSeconds(elapsed_counter);
    while (elapsed < gTimer.fixed_time_step)
    {
        float time_left = gTimer.fixed_time_step - elapsed;
        U32 sleep = (U32)(1000.0f * time_left);
        if (sleep > 0) SDL_Delay(sleep);

        elapsed_counter = SDL_GetPerformanceCounter() - gTimer.last_counter;
        elapsed = CounterToSeconds(elapsed_counter);
    }

    gTimer.current_fps = (float)gTimer.performance_frequency / (float)elapsed_counter;
    gTimer.last_counter = SDL_GetPerformanceCounter();
}
