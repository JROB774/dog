#ifndef TIMER_HPP
#define TIMER_HPP

GLOBAL constexpr int FRAMERATE = 60;

GLOBAL struct Timer
{
    U64   performance_frequency;
    U64   last_counter;
    U64   end_counter;
    float current_fps;
    float fixed_time_step;
    float delta_time;

} gTimer;

INTERNAL float CounterToSeconds (U64 counter);
INTERNAL void  InitFrameTimer   ();
INTERNAL void  CapFramerate     ();

#endif /* TIMER_HPP */
