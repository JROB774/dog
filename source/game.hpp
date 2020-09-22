#ifndef GAME_HPP
#define GAME_HPP

GLOBAL constexpr float GRAVITY = 50.0f;

GLOBAL struct GameState
{
    Map map;
    Dog dog;

} gGameState;

INTERNAL void InitGame   ();
INTERNAL void QuitGame   ();
INTERNAL void UpdateGame (float dt);
INTERNAL void RenderGame (float dt);

#endif /* GAME_HPP */
