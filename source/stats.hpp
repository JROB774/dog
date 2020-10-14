#ifndef STATS_HPP
#define STATS_HPP

GLOBAL struct StatsState
{
    Image back;

} gStatsState;

INTERNAL void InitStats   ();
INTERNAL void QuitStats   ();
INTERNAL void UpdateStats (float dt);
INTERNAL void RenderStats (float dt);
INTERNAL void GoToStats   ();

#endif /* STATS_HPP */
