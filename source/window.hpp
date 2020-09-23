#ifndef WINDOW_HPP
#define WINDOW_HPP

GLOBAL struct Window
{
    SDL_Renderer* renderer;
    SDL_Window*   window;
    bool          running;

} gWindow;

INTERNAL bool InitWindow    ();
INTERNAL void QuitWindow    ();
INTERNAL void ClearWindow   (Color color);
INTERNAL void RefreshWindow ();
INTERNAL void ShowWindow    ();
INTERNAL void HideWindow    ();
INTERNAL void SetViewport   ();

#endif /* WINDOW_HPP */
