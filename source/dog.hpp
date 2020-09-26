#ifndef DOG_HPP
#define DOG_HPP

enum DogState
{
    DOG_STATE_IDLE,
    DOG_STATE_BLNK,
    DOG_STATE_MOVE,
    DOG_STATE_JUMP,
    DOG_STATE_FALL,
    DOG_STATE_BARK,
    DOG_STATE_TOTAL
};

struct Dog
{
    DogState state;

    Vec2 pos,vel;

    Rect bounds;

    Image image;
    Flip flip;

    float footstep_timer;

    Sound snd_footstep;
    Sound snd_land;
    Sound snd_hithead;
    Sound snd_jump;
    Sound snd_bark;
    Sound snd_explode0;
    Sound snd_explode1;

    Animation anim[DOG_STATE_TOTAL];

    bool up;
    bool right;
    bool left;
    bool down;
    bool jump_press;
    bool jump_release;
    bool action;

    bool grounded;

    float ledge_buffer;
    float jump_height;

    bool dead;
};

INTERNAL void CreateDog (Dog& dog, float x, float y);
INTERNAL void UpdateDog (Dog& dog, float dt);
INTERNAL void DrawDog   (Dog& dog, float dt);
INTERNAL void DeleteDog (Dog& dog);

INTERNAL bool DogCollideWithEntity (Dog& dog, float ex, float ey, Rect ebounds);

#endif /* DOG_HPP */
