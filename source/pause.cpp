#if defined(PLATFORM_WIN32)
#include "OS/win32/pause.cpp"
#elif defined(PLATFORM_WEB)
#include "OS/web/pause.cpp"
#endif

INTERNAL void InitPause ()
{
    gPauseState.selected = 0;

    LoadImage(gPauseState.title, "pause.bmp");
    LoadImage(gPauseState.caret, "caret.bmp");

    LoadAnimation(gPauseState.caret_anim, "caret.anim");

    LoadSound(gPauseState.snd_change, "change.wav");
    LoadSound(gPauseState.snd_select, "select.wav");
}

INTERNAL void QuitPause ()
{
    FreeSound(gPauseState.snd_change);
    FreeSound(gPauseState.snd_select);

    FreeAnimation(gPauseState.caret_anim);

    FreeImage(gPauseState.title);
    FreeImage(gPauseState.caret);
}

INTERNAL void Unpause ()
{
    PlaySound(gPauseState.snd_select);
    gAppState.state = APP_STATE_GAME;
}

INTERNAL void Pause ()
{
    PlaySound(gPauseState.snd_select);
    gAppState.state = APP_STATE_PAUSE;
    gPauseState.selected = 0;
}
