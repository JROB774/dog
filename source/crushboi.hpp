#ifndef  CRUSHBOI_HPP
#define CRUSHBOI_HPP

//Left and Right Light Lime #B6FF00
//Up and Down Dark Lime #5B7F00

struct CrushBoi
{
    bool vertical;
    bool active;

    Vec2 pos;
    Vec2 start_pos;
    Vec2 vel;

    Rect bounds;
};

GLOBAL SDL_Rect gCrushBoiClip = {0, 0, 16, 16};
GLOBAL Image gCrushBoiImage;
//GLOBAL Sound gCrushBoiMove;
GLOBAL Sound gCrushBoiHitSound;

void InitCrushBoi();
void DeinitCrushBoi();
void CreateCrushBoi(CrushBoi& _boi, float _x, float _y, bool _vertical);
void UpdateCrushBoi(CrushBoi& _boi);
void RenderCrushBoi(CrushBoi& _boi);
void ResetCrushBoi(CrushBoi& _boi);
void DestroyCrushBoi(CrushBoi& _boi);

#endif
