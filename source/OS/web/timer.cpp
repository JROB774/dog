INTERNAL void InitFrameTimer ()
{
    gTimer.performance_frequency = SDL_GetPerformanceFrequency();
    gTimer.last_counter          = SDL_GetPerformanceCounter();
    gTimer.end_counter           = 0;
    gTimer.current_fps           = 0.0f;
    gTimer.fixed_time_step       = 0.0f;
    gTimer.delta_time            = 0.0f;
}

INTERNAL void CapFramerate ()
{
    gTimer.end_counter = SDL_GetPerformanceCounter();
    U64 elapsed_counter = gTimer.end_counter - gTimer.last_counter;
    gTimer.last_counter = SDL_GetPerformanceCounter();

    gTimer.current_fps = (float)gTimer.performance_frequency / (float)elapsed_counter;

    gTimer.delta_time = CounterToSeconds(elapsed_counter);
    gTimer.fixed_time_step = CounterToSeconds(elapsed_counter);
}
