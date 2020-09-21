#ifndef INPUT_HPP
#define INPUT_HPP

U8 previous_keystates[SDL_NUM_SCANCODES];
U8 current_keystates[SDL_NUM_SCANCODES];



bool IsKeyDown(SDL_Scancode _code);
bool IsKeyUp(SDL_Scancode _code);

bool IsKeyPressed(SDL_Scancode _code);
bool IsKeyReleased(SDL_Scancode _code);

void UpdateKeyboardState();


#endif