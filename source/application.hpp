#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#define APP_VERSION_MAJOR 1
#define APP_VERSION_MINOR 0
#define APP_VERSION_PATCH 0

enum AppState
{
    APP_STATE_MENU,
    APP_STATE_GAME,
    APP_STATE_PAUSE,
    APP_STATE_STATS,
};

GLOBAL struct ApplicationState
{
    Font lfont, sfont;
    AppState state;
    bool screenshot_mode;

} gAppState;

INTERNAL void InitApplication   ();
INTERNAL void QuitApplication   ();
INTERNAL void UpdateApplication (float dt);
INTERNAL void RenderApplication (float dt);

#endif /* APPLICATION_HPP */
