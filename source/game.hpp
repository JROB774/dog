#ifndef GAME_HPP
#define GAME_HPP

GLOBAL constexpr const char* START_GAME_MAP      = "tutorial-main-start.bmp";
GLOBAL constexpr float       START_GAME_X        = 188;
GLOBAL constexpr float       START_GAME_Y        = 140;
GLOBAL constexpr Flip        START_GAME_FLIP     = FLIP_HORZ;
GLOBAL constexpr const char* START_TUTORIAL_MAP  = "tutorial-main-start.bmp";
GLOBAL constexpr float       START_TUTORIAL_X    = 188;
GLOBAL constexpr float       START_TUTORIAL_Y    = 140;
GLOBAL constexpr Flip        START_TUTORIAL_FLIP = FLIP_HORZ;

GLOBAL constexpr float GRAVITY = 32.0f;

GLOBAL struct GameState
{
    Music mus_game;
    Music mus_tutorial;
    Music mus_challenge;

    Dog dog;

} gGameState;

INTERNAL void InitGame   ();
INTERNAL void QuitGame   ();
INTERNAL void UpdateGame (float dt);
INTERNAL void RenderGame (float dt);

INTERNAL void StartGame (std::string start_map, float start_x, float start_y, Flip start_flip, Music& music);
INTERNAL void EndGame   ();

#endif /* GAME_HPP */
