GLOBAL constexpr float SPIKE_CLIP_W = 24;
GLOBAL constexpr float SPIKE_CLIP_H = 24;

INTERNAL void CreateSpike (Spike& spike, float x, float y, SpikeDir dir)
{
    LoadImage(spike.image, "spike.bmp");

    spike.x = (x + (TILE_W/2)) - (SPIKE_CLIP_W/2);
    spike.y = (y + (TILE_H/2)) - (SPIKE_CLIP_H/2);

    switch (dir)
    {
        case (SPIKE_DIR_U):
        {
            spike.bounds = { 4, 10, 16, 10 };
            spike.clip = { (int)(SPIKE_CLIP_W*0), 0, (int)SPIKE_CLIP_W, (int)SPIKE_CLIP_H };
        } break;
        case (SPIKE_DIR_R):
        {
            spike.bounds = { 4, 4, 10, 16 };
            spike.clip = { (int)(SPIKE_CLIP_W*1), 0, (int)SPIKE_CLIP_W, (int)SPIKE_CLIP_H };
        } break;
        case (SPIKE_DIR_D):
        {
            spike.bounds = { 4, 4, 16, 10 };
            spike.clip = { (int)(SPIKE_CLIP_W*2), 0, (int)SPIKE_CLIP_W, (int)SPIKE_CLIP_H };
        } break;
        case (SPIKE_DIR_L):
        {
            spike.bounds = { 10, 4, 10, 16 };
            spike.clip = { (int)(SPIKE_CLIP_W*3), 0, (int)SPIKE_CLIP_W, (int)SPIKE_CLIP_H };
        } break;
    }
}

INTERNAL void DeleteSpike (Spike& spike)
{
    FreeImage(spike.image);
}

INTERNAL void DrawSpike (Spike& spike)
{
    DrawImage(spike.image, spike.x, spike.y, FLIP_NONE, &spike.clip);
}
