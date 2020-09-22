#ifndef DOG_HPP
#define DOG_HPP

struct Dog
{
    Vec2 pos, vel;

    Image image;
    Flip flip;

    bool jump, action;
    bool left, right;
};

INTERNAL void CreateDog (Dog& dog, float x, float y);
INTERNAL void UpdateDog (Dog& dog, float dt);
INTERNAL void DrawDog   (Dog& dog, float dt);

#endif /* DOG_HPP */
