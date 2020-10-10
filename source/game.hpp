#ifndef GAME_HPP
#define GAME_HPP

enum GameMode
{
    GAME_MODE_NORMAL,
    GAME_MODE_CHALLENGE,
    GAME_MODE_NORMALPLUS,
    GAME_MODE_CHALLENGEPLUS,
    GAME_MODE_TUTORIAL, // IMPORTANT: This needs to go after the above four so that they can map to the badge unlock array!
    GAME_MODE_TOTAL
};

struct GameModeInfo
{
    std::string map;
    Vec2 pos;
    Flip flip;
    Music* music;
    float speedrun_time; // In seconds!
};

GLOBAL constexpr float GRAVITY = 32.0f;

GLOBAL struct GameState
{
    Music mus_fanfare;
    Music mus_game;
    Music mus_tutorial;
    Music mus_challenge;

    float timer;

    Dog dog;

    bool doing_win_sequence;

    GameMode mode;

} gGameState;

GLOBAL const GameModeInfo GAME_MODE_INFO[GAME_MODE_TOTAL]
{
{   "normal-main-00.bmp", { 180, 140 }, FLIP_HORZ, &gGameState.mus_game,      60 },
{ "tutorial-grid-00.bmp", {  56, 172 }, FLIP_NONE, &gGameState.mus_challenge, 60 },
{ "tutorial-grid-00.bmp", {  56, 172 }, FLIP_NONE, &gGameState.mus_game,      60 },
{ "tutorial-grid-00.bmp", {  56, 172 }, FLIP_NONE, &gGameState.mus_challenge, 60 },
{ "tutorial-grid-00.bmp", {  56, 172 }, FLIP_NONE, &gGameState.mus_tutorial,  60 }
};

INTERNAL void InitGame   ();
INTERNAL void QuitGame   ();
INTERNAL void UpdateGame (float dt);
INTERNAL void RenderGame (float dt);

INTERNAL void StartGame (GameMode game_mode, bool retry = false);
INTERNAL void EndGame   ();
INTERNAL void RetryGame ();

INTERNAL void StartWinSequence ();
INTERNAL void EndWinSequence   ();
INTERNAL void DoWinSequence    ();

#endif /* GAME_HPP */
