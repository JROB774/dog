#ifndef APPLICATION_HPP
#define APPLICATION_HPP

enum AppState
{
    APP_STATE_MENU,
    APP_STATE_GAME,
};

GLOBAL struct ApplicationState
{
    Font lfont, sfont;
    AppState state;

} gAppState;

INTERNAL void InitApplication   ();
INTERNAL void QuitApplication   ();
INTERNAL void UpdateApplication (float dt);
INTERNAL void RenderApplication (float dt);

#endif /* APPLICATION_HPP */
