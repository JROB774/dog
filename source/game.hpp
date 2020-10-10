#ifndef GAME_HPP
#define GAME_HPP

enum GameMode
{
    GAME_MODE_TUTORIAL,
    GAME_MODE_NORMAL,
    GAME_MODE_CHALLENGE,
    GAME_MODE_NORMAL_HARD,
    GAME_MODE_CHALLENGE_HARD,
    GAME_MODE_TOTAL
};

struct GameModeInfo
{
    std::string map;
    Vec2 pos;
    Flip flip;
    Music* music;
};

GLOBAL constexpr float GRAVITY = 32.0f;

GLOBAL struct GameState
{
    Music mus_fanfare;
    Music mus_game;
    Music mus_tutorial;
    Music mus_challenge;

    Dog dog;

    bool challenge_locked; // @TEMPORARY: JUST SO THE CHALLENGE CAN BE LOCKED FOR NOW...
    bool doing_win_sequence;

    GameMode mode;

} gGameState;

GLOBAL const GameModeInfo GAME_MODE_INFO[GAME_MODE_TOTAL]
{
{ "tutorial-grid-00.bmp", { 56, 172 }, FLIP_NONE, &gGameState.mus_tutorial  },
{ "tutorial-grid-00.bmp", { 56, 172 }, FLIP_NONE, &gGameState.mus_game      },
{ "tutorial-grid-00.bmp", { 56, 172 }, FLIP_NONE, &gGameState.mus_challenge },
{ "tutorial-grid-00.bmp", { 56, 172 }, FLIP_NONE, &gGameState.mus_game      },
{ "tutorial-grid-00.bmp", { 56, 172 }, FLIP_NONE, &gGameState.mus_challenge }
};

INTERNAL void InitGame   ();
INTERNAL void QuitGame   ();
INTERNAL void UpdateGame (float dt);
INTERNAL void RenderGame (float dt);

INTERNAL void StartGame (GameMode game_mode);
INTERNAL void EndGame   ();
INTERNAL void RetryGame ();

INTERNAL void StartWinSequence ();
INTERNAL void EndWinSequence   ();
INTERNAL void DoWinSequence    ();

#endif /* GAME_HPP */
