#if defined(PLATFORM_WIN32)
#include "OS/win32/input.cpp"
#elif defined(PLATFORM_WEB)
#include "OS/web/input.cpp"
#endif

// KEYBOARD

INTERNAL bool IsKeyDown (SDL_Scancode code)
{
    if (code < 0 || code > SDL_NUM_SCANCODES) return false;
    return (gInput.current_key_state[code] != 0);
}

INTERNAL bool IsKeyUp (SDL_Scancode code)
{
    if (code < 0 || code > SDL_NUM_SCANCODES) return false;
    return (gInput.current_key_state[code] == 0);
}

INTERNAL bool IsKeyPressed (SDL_Scancode code)
{
    if (code < 0 || code > SDL_NUM_SCANCODES) return false;
    return (gInput.current_key_state[code] == 1 && gInput.previous_key_state[code] == 0);
}

INTERNAL bool IsKeyReleased (SDL_Scancode code)
{
    if (code < 0 || code > SDL_NUM_SCANCODES) return false;
    return (gInput.current_key_state[code] == 0 && gInput.previous_key_state[code] == 1);
}
