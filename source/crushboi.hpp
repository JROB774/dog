#ifndef CRUSHBOI_HPP
#define CRUSHBOI_HPP

struct CrushBoi
{
    bool vertical;
    bool active;

    Vec2 pos;
    Vec2 start_pos;
    Vec2 vel;

    Rect bounds;

    float timer;
};

INTERNAL void   InitCrushBoi ();
INTERNAL void   QuitCrushBoi ();
INTERNAL void CreateCrushBoi (CrushBoi& boi, float x, float y, bool vertical);
INTERNAL void UpdateCrushBoi (CrushBoi& boi, float dt);
INTERNAL void RenderCrushBoi (CrushBoi& boi);
INTERNAL void  ResetCrushBoi (CrushBoi& boi);

#endif /* CRUSHBOI_HPP */
