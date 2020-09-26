#ifndef APPLICATION_HPP
#define APPLICATION_HPP

enum ApplicationState
{
    APP_STATE_MENU,
    APP_STATE_GAME,
};

GLOBAL ApplicationState gAppState;

INTERNAL void InitApplication   ();
INTERNAL void QuitApplication   ();
INTERNAL void UpdateApplication (float dt);
INTERNAL void RenderApplication (float dt);

#endif /* APPLICATION_HPP */
