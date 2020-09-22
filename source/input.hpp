#ifndef INPUT_HPP
#define INPUT_HPP

INTERNAL void UpdateKeyboardState ();

INTERNAL bool IsKeyDown     (SDL_Scancode code);
INTERNAL bool IsKeyUp       (SDL_Scancode code);
INTERNAL bool IsKeyPressed  (SDL_Scancode code);
INTERNAL bool IsKeyReleased (SDL_Scancode code);

#endif /* INPUT_HPP */
