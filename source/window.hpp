#ifndef WINDOW_HPP
#define WINDOW_HPP

GLOBAL struct Window
{
    SDL_Renderer* renderer;
    SDL_Window*   window;

} gWindow;

INTERNAL bool InitWindow    (const char* title, int w, int h);
INTERNAL void QuitWindow    ();
INTERNAL void ClearWindow   (Color color);
INTERNAL void RefreshWindow ();
INTERNAL void ShowWindow    ();
INTERNAL void HideWindow    ();

#endif /* WINDOW_HPP */
