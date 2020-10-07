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

INTERNAL void InitCrushBoi();
INTERNAL void QuitCrushBoi();
INTERNAL void CreateCrushBoi(CrushBoi& _boi, float _x, float _y, bool _vertical);
INTERNAL void UpdateCrushBoi(CrushBoi& _boi);
INTERNAL void RenderCrushBoi(CrushBoi& _boi);
INTERNAL void ResetCrushBoi(CrushBoi& _boi);

#endif
