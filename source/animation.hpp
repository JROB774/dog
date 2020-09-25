#ifndef ANIMATION_HPP
#define ANIMATION_HPP

struct AnimationFrame
{
    float duration;
    SDL_Rect clip;
};

struct AnimationState
{
    float timer;
    int frame;
};

struct Animation
{
    std::vector<AnimationFrame> frames;
    bool looped;
    AnimationState state;
};

INTERNAL void LoadAnimation   (Animation& animation, std::string file_name);
INTERNAL void FreeAnimation   (Animation& animation);
INTERNAL void UpdateAnimation (Animation& animation, float dt);
INTERNAL void ResetAnimation  (Animation& animation);
INTERNAL bool IsAnimationDone (Animation& animation);

INTERNAL const SDL_Rect* GetAnimationClip (Animation& animation);

INTERNAL int GetAnimationFrameWidth  (Animation& animation);
INTERNAL int GetAnimationFrameHeight (Animation& animation);

#endif /* ANIMATION_HPP */
