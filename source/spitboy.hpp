#ifndef SPITBOY_HPP
#define SPITBOY_HPP

enum SpitBoyState
{
    SPITBOY_STATE_IDLE,
    SPITBOY_STATE_SPIT,
    SPITBOY_STATE_TOTAL
};

struct Spit
{
    Vec2 pos,vel;
    Rect bounds;
    bool dead;
    Animation anim;
};

struct SpitBoy
{
    SpitBoyState state;
    Vec2 pos;
    float angle;
    Rect bounds;
    std::vector<Spit> spit;
    Flip flip; // Whether to face up or down.
    bool sight;
    float timer;
    Animation anim[SPITBOY_STATE_TOTAL];
};

INTERNAL void   InitSpitBoy ();
INTERNAL void   QuitSpitBoy ();
INTERNAL void CreateSpitBoy (SpitBoy& spitboy, float x, float y, bool flip);
INTERNAL void DeleteSpitBoy (SpitBoy& spitboy);
INTERNAL void UpdateSpitBoy (SpitBoy& spitboy, float dt);
INTERNAL void RenderSpitBoy (SpitBoy& spitboy, float dt);
INTERNAL void  ResetSpitBoy (SpitBoy& spitboy);
INTERNAL void      KillSpit (Spit   & spit);

#endif /* SPITBOY_HPP */
