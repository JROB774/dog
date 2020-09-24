#ifndef SPIKE_HPP
#define SPIKE_HPP

enum SpikeDir
{
    SPIKE_DIR_U,
    SPIKE_DIR_R,
    SPIKE_DIR_D,
    SPIKE_DIR_L
};

struct Spike
{
    Image image;
    float x,y;
    Rect bounds;
    SDL_Rect clip;
};

INTERNAL void CreateSpike (Spike& spike, float x, float y, SpikeDir dir);
INTERNAL void DeleteSpike (Spike& spike);

INTERNAL void DrawSpike (Spike& spike);

#endif /* SPIKE_HPP */
