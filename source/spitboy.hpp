#ifndef SPITBOY_HPP
#define SPITBOY_HPP

struct Spit
{
    Vec2 pos,vel;
    Rect bounds;
    bool dead;
};

struct SpitBoy
{
    Vec2 pos;
    float angle;
    Rect bounds;
    std::vector<Spit> spit;
    bool sight;
    float timer;
};

INTERNAL void   InitSpitBoy ();
INTERNAL void   QuitSpitBoy ();
INTERNAL void CreateSpitBoy (SpitBoy& spitboy, float x, float y);
INTERNAL void UpdateSpitBoy (SpitBoy& spitboy, float dt);
INTERNAL void RenderSpitBoy (SpitBoy& spitboy, float dt);
INTERNAL void  ResetSpitBoy (SpitBoy& spitboy);
INTERNAL void      KillSpit (Spit   & spit);

#endif /* SPITBOY_HPP */
