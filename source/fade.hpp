#ifndef FADE_HPP
#define FADE_HPP

enum FadeType { FADE_NONE, FADE_UP, FADE_RIGHT, FADE_DOWN, FADE_LEFT, FADE_SPECIAL };

typedef void(*FadeCallback)(void);

INTERNAL void InitFade   ();
INTERNAL void QuitFade   ();
INTERNAL void StartFade  (FadeType type, FadeCallback callback);
INTERNAL void RenderFade (float dt);
INTERNAL bool IsFading   ();

#endif /* FADE_HPP */
