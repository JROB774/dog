#ifndef WINDOW_HPP
#define WINDOW_HPP

GLOBAL constexpr const char* WINDOW_TITLE = "DOG!";

GLOBAL constexpr int WINDOW_SCREEN_W = 320;
GLOBAL constexpr int WINDOW_SCREEN_H = 240;

GLOBAL constexpr int WINDOW_START_W = 640;
GLOBAL constexpr int WINDOW_START_H = 480;

GLOBAL struct Window
{
    SDL_Renderer* renderer;
    SDL_Window*   window;
    int           width; // Used to cache size when in fullscreen!!!
    int           height; // Used to cache size when in fullscreen!!!
    bool          fullscreen;
    bool          running;
    bool          reset;

} gWindow;

INTERNAL bool InitWindow      ();
INTERNAL void QuitWindow      ();
INTERNAL void ClearWindow     (Color color);
INTERNAL void RefreshWindow   ();
INTERNAL void ShowWindow      ();
INTERNAL void HideWindow      ();
INTERNAL void SetViewport     ();
INTERNAL void SetFullscreen   (bool enable);
INTERNAL bool IsFullscreen    ();
INTERNAL void SetWindowSize   (int width, int height);
INTERNAL int  GetWindowWidth  ();
INTERNAL int  GetWindowHeight ();

#endif /* WINDOW_HPP */
