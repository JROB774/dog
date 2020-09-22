#ifndef DOG_HPP
#define DOG_HPP

struct Dog
{
    Vec2 pos, vel;

    Rect bounds;

    Image image;
    Flip flip;

    bool left;
    bool right;

    bool grounded;
};

INTERNAL void CreateDog (Dog& dog, float x, float y);
INTERNAL void UpdateDog (Dog& dog, float dt);
INTERNAL void DrawDog   (Dog& dog, float dt);

#endif /* DOG_HPP */
