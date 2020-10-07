#ifndef WALKBOY_HPP
#define WALKBOY_HPP

struct WalkBoy
{
    Vec2 start_pos;
    Vec2 pos;
    Rect bounds;
    Flip flip;
};

INTERNAL void   InitWalkBoy ();
INTERNAL void   QuitWalkBoy ();
INTERNAL void CreateWalkBoy (WalkBoy& walkboy, float x, float y);
INTERNAL void UpdateWalkBoy (WalkBoy& walkboy, float dt);
INTERNAL void RenderWalkBoy (WalkBoy& walkboy, float dt);
INTERNAL void  ResetWalkBoy (WalkBoy& walkboy);

// Helpers used internally.
INTERNAL bool WalkBoyCheckRightIsGood (WalkBoy& walkboy, Vec2 pos);
INTERNAL bool WalkBoyCheckLeftIsGood  (WalkBoy& walkboy, Vec2 pos);

#endif /* WALKBOY_HPP */
