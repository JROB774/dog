#ifndef DOG_HPP
#define DOG_HPP

enum DogState
{
    DOG_STATE_IDLE,
    DOG_STATE_BLINK,
    DOG_STATE_MOVE,
    DOG_STATE_JUMP,
    DOG_STATE_FALL,
    DOG_STATE_TOTAL
};

struct Dog
{
    DogState state;

    Vec2 pos,vel;

    Rect bounds;

    Image image;
    Flip flip;

    Animation anim[DOG_STATE_TOTAL];

    bool left;
    bool right;

    bool grounded;

    float ledge_buffer;
};

INTERNAL void CreateDog (Dog& dog, float x, float y);
INTERNAL void UpdateDog (Dog& dog, float dt);
INTERNAL void DrawDog   (Dog& dog, float dt);

#endif /* DOG_HPP */
