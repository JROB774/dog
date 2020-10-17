GLOBAL struct InputState
{
    U8 previous_key_state[SDL_NUM_SCANCODES];
    U8 current_key_state[SDL_NUM_SCANCODES];

} gInput;

INTERNAL void QuitInput ()
{
    // Nothing...
}

INTERNAL void UpdateInputState ()
{
    // Update the keyboard state.
    memcpy(gInput.previous_key_state, gInput.current_key_state, SDL_NUM_SCANCODES * sizeof(U8));
    memcpy(gInput.current_key_state, SDL_GetKeyboardState(NULL), SDL_NUM_SCANCODES * sizeof(U8));
}

INTERNAL void HandleInputEvents (SDL_Event event)
{
    // Nothing...
}

// GAMEPAD

INTERNAL bool IsButtonDown (SDL_GameControllerButton button)
{
    return false;
}
INTERNAL bool IsButtonUp (SDL_GameControllerButton button)
{
    return false;
}
INTERNAL bool IsButtonPressed (SDL_GameControllerButton button)
{
    return false;
}
INTERNAL bool IsButtonReleased (SDL_GameControllerButton button)
{
    return false;
}

INTERNAL S16 GetAxis (SDL_GameControllerAxis axis)
{
    return 0;
}

INTERNAL bool IsRightStickUp ()
{
    return false;
}
INTERNAL bool IsRightStickRight ()
{
    return false;
}
INTERNAL bool IsRightStickDown ()
{
    return false;
}
INTERNAL bool IsRightStickLeft ()
{
    return false;
}

INTERNAL bool IsRightStickUpPressed ()
{
    return false;
}
INTERNAL bool IsRightStickRightPressed ()
{
    return false;
}
INTERNAL bool IsRightStickDownPressed ()
{
    return false;
}
INTERNAL bool IsRightStickLeftPressed ()
{
    return false;
}

INTERNAL bool IsLeftStickUp ()
{
    return false;
}
INTERNAL bool IsLeftStickRight ()
{
    return false;
}
INTERNAL bool IsLeftStickDown ()
{
    return false;
}
INTERNAL bool IsLeftStickLeft ()
{
    return false;
}

INTERNAL bool IsLeftStickUpPressed ()
{
    return false;
}
INTERNAL bool IsLeftStickRightPressed ()
{
    return false;
}
INTERNAL bool IsLeftStickDownPressed ()
{
    return false;
}
INTERNAL bool IsLeftStickLeftPressed ()
{
    return false;
}
