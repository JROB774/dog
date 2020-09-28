#ifndef PAUSE_HPP
#define PAUSE_HPP

GLOBAL struct PauseState
{
    int selected;

    Image title;
    Image caret;

    Animation caret_anim;

    Sound snd_change;
    Sound snd_select;

} gPauseState;

INTERNAL void InitPause   ();
INTERNAL void QuitPause   ();
INTERNAL void UpdatePause (float dt);
INTERNAL void RenderPause (float dt);

INTERNAL void Unpause ();
INTERNAL void Pause   ();

#endif /* PAUSE_HPP */
