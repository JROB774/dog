GLOBAL constexpr S16 INPUT_GAMEPAD_STICK_DEADZONE = 12000;

GLOBAL struct InputState
{
    U8 previous_key_state[SDL_NUM_SCANCODES];
    U8 current_key_state[SDL_NUM_SCANCODES];

    SDL_GameController* gamepad;

    U8 previous_button_state[SDL_CONTROLLER_BUTTON_MAX];
    U8 current_button_state[SDL_CONTROLLER_BUTTON_MAX];

    S16 previous_left_stick_x, previous_left_stick_y;
    S16 current_left_stick_x, current_left_stick_y;
    S16 previous_right_stick_x, previous_right_stick_y;
    S16 current_right_stick_x, current_right_stick_y;

} gInput;

INTERNAL void RemoveGamepad ()
{
    if (gInput.gamepad)
    {
        SDL_GameControllerClose(gInput.gamepad);
        gInput.gamepad = NULL;
    }
}

INTERNAL void AddGamepad ()
{
    // Search for a plugged in gamepad and if there is one use it.
    RemoveGamepad();
    for (int i=0; i<SDL_NumJoysticks(); ++i)
    {
        if (SDL_IsGameController(i))
        {
            gInput.gamepad = SDL_GameControllerOpen(i);
            if (gInput.gamepad)
            {
                break;
            }
        }
    }
}

INTERNAL void QuitInput ()
{
    RemoveGamepad();
}

INTERNAL void UpdateInputState ()
{
    // Update the keyboard state.
    memcpy(gInput.previous_key_state, gInput.current_key_state, SDL_NUM_SCANCODES * sizeof(U8));
    memcpy(gInput.current_key_state, SDL_GetKeyboardState(NULL), SDL_NUM_SCANCODES * sizeof(U8));

    // Update the gamepad button state.
    if (gInput.gamepad)
    {
        memcpy(gInput.previous_button_state, gInput.current_button_state, SDL_CONTROLLER_BUTTON_MAX * sizeof(U8));
        for (int i=0; i<SDL_CONTROLLER_BUTTON_MAX; ++i)
        {
            gInput.current_button_state[i] = SDL_GameControllerGetButton(gInput.gamepad, (SDL_GameControllerButton)i);
        }

        gInput.previous_left_stick_x = gInput.current_left_stick_x, gInput.previous_left_stick_y = gInput.current_left_stick_y;
        gInput.current_left_stick_x = GetAxis(SDL_CONTROLLER_AXIS_LEFTX), gInput.current_left_stick_y = GetAxis(SDL_CONTROLLER_AXIS_LEFTY);
        gInput.previous_right_stick_x = gInput.current_right_stick_x, gInput.previous_right_stick_y = gInput.current_right_stick_y;
        gInput.current_right_stick_x = GetAxis(SDL_CONTROLLER_AXIS_RIGHTX), gInput.current_right_stick_y = GetAxis(SDL_CONTROLLER_AXIS_RIGHTY);
    }
    else
    {
        memset(gInput.previous_button_state, 0, sizeof(gInput.previous_button_state));
        memset(gInput.current_button_state, 0, sizeof(gInput.current_button_state));

        gInput.previous_left_stick_x = 0, gInput.previous_left_stick_y = 0;
        gInput.current_left_stick_x = 0, gInput.current_left_stick_y = 0;
        gInput.previous_right_stick_x = 0, gInput.previous_right_stick_y = 0;
        gInput.current_right_stick_x = 0, gInput.current_right_stick_y = 0;
    }
}

INTERNAL void HandleInputEvents (SDL_Event event)
{
    switch (event.type)
    {
        case (SDL_CONTROLLERDEVICEADDED): AddGamepad(); break;
        case (SDL_CONTROLLERDEVICEREMOVED): RemoveGamepad(); break;
    }
}

// GAMEPAD

INTERNAL bool IsButtonDown (SDL_GameControllerButton button)
{
    if (IsFading()) return false;
    if (button == SDL_CONTROLLER_BUTTON_INVALID) return false;
    if (button < 0 || button > SDL_CONTROLLER_BUTTON_MAX) return false;
    if (!gInput.gamepad) return false;
    return (gInput.current_button_state[button] != 0);
}

INTERNAL bool IsButtonUp (SDL_GameControllerButton button)
{
    if (IsFading()) return false;
    if (button == SDL_CONTROLLER_BUTTON_INVALID) return false;
    if (button < 0 || button > SDL_CONTROLLER_BUTTON_MAX) return false;
    if (!gInput.gamepad) return false;
    return (gInput.current_button_state[button] == 0);
}

INTERNAL bool IsButtonPressed (SDL_GameControllerButton button)
{
    if (IsFading()) return false;
    if (button == SDL_CONTROLLER_BUTTON_INVALID) return false;
    if (button < 0 || button > SDL_CONTROLLER_BUTTON_MAX) return false;
    if (!gInput.gamepad) return false;
    return (gInput.current_button_state[button] == 1 && gInput.previous_button_state[button] == 0);
}

INTERNAL bool IsButtonReleased (SDL_GameControllerButton button)
{
    if (IsFading()) return false;
    if (button == SDL_CONTROLLER_BUTTON_INVALID) return false;
    if (button < 0 || button > SDL_CONTROLLER_BUTTON_MAX) return false;
    if (!gInput.gamepad) return false;
    return (gInput.current_button_state[button] == 0 && gInput.previous_button_state[button] == 1);
}

INTERNAL S16 GetAxis (SDL_GameControllerAxis axis)
{
    if (IsFading()) return 0;
    if (axis == SDL_CONTROLLER_AXIS_INVALID) return 0;
    if (axis < 0 || axis > SDL_CONTROLLER_AXIS_MAX) return 0;
    if (!gInput.gamepad) return 0;
    return SDL_GameControllerGetAxis(gInput.gamepad, axis);
}

INTERNAL bool IsRightStickUp ()
{
    if (IsFading()) return false;
    if (!gInput.gamepad) return false;
    S16 y = GetAxis(SDL_CONTROLLER_AXIS_RIGHTY);
    return (y < -INPUT_GAMEPAD_STICK_DEADZONE);
}
INTERNAL bool IsRightStickRight ()
{
    if (IsFading()) return false;
    if (!gInput.gamepad) return false;
    S16 x = GetAxis(SDL_CONTROLLER_AXIS_RIGHTX);
    return (x > INPUT_GAMEPAD_STICK_DEADZONE);
}
INTERNAL bool IsRightStickDown ()
{
    if (IsFading()) return false;
    if (!gInput.gamepad) return false;
    S16 y = GetAxis(SDL_CONTROLLER_AXIS_RIGHTY);
    return (y > INPUT_GAMEPAD_STICK_DEADZONE);
}
INTERNAL bool IsRightStickLeft ()
{
    if (IsFading()) return false;
    if (!gInput.gamepad) return false;
    S16 x = GetAxis(SDL_CONTROLLER_AXIS_RIGHTX);
    return (x < -INPUT_GAMEPAD_STICK_DEADZONE);
}

INTERNAL bool IsRightStickUpPressed ()
{
    if (IsFading()) return false;
    if (!gInput.gamepad) return false;
    return (gInput.previous_right_stick_y >= -INPUT_GAMEPAD_STICK_DEADZONE &&
            gInput.current_right_stick_y < -INPUT_GAMEPAD_STICK_DEADZONE);
}
INTERNAL bool IsRightStickRightPressed ()
{
    if (IsFading()) return false;
    if (!gInput.gamepad) return false;
    return (gInput.previous_right_stick_x <= INPUT_GAMEPAD_STICK_DEADZONE &&
            gInput.current_right_stick_x > INPUT_GAMEPAD_STICK_DEADZONE);
}
INTERNAL bool IsRightStickDownPressed ()
{
    if (IsFading()) return false;
    if (!gInput.gamepad) return false;
    return (gInput.previous_right_stick_y <= INPUT_GAMEPAD_STICK_DEADZONE &&
            gInput.current_right_stick_y > INPUT_GAMEPAD_STICK_DEADZONE);
}
INTERNAL bool IsRightStickLeftPressed ()
{
    if (IsFading()) return false;
    if (!gInput.gamepad) return false;
    return (gInput.previous_right_stick_x >= -INPUT_GAMEPAD_STICK_DEADZONE &&
            gInput.current_right_stick_x < -INPUT_GAMEPAD_STICK_DEADZONE);
}

INTERNAL bool IsLeftStickUp ()
{
    if (IsFading()) return false;
    if (!gInput.gamepad) return false;
    S16 y = GetAxis(SDL_CONTROLLER_AXIS_LEFTY);
    return (y < -INPUT_GAMEPAD_STICK_DEADZONE);
}
INTERNAL bool IsLeftStickRight ()
{
    if (IsFading()) return false;
    if (!gInput.gamepad) return false;
    S16 x = GetAxis(SDL_CONTROLLER_AXIS_LEFTX);
    return (x > INPUT_GAMEPAD_STICK_DEADZONE);
}
INTERNAL bool IsLeftStickDown ()
{
    if (IsFading()) return false;
    if (!gInput.gamepad) return false;
    S16 y = GetAxis(SDL_CONTROLLER_AXIS_LEFTY);
    return (y > INPUT_GAMEPAD_STICK_DEADZONE);
}
INTERNAL bool IsLeftStickLeft ()
{
    if (IsFading()) return false;
    if (!gInput.gamepad) return false;
    S16 x = GetAxis(SDL_CONTROLLER_AXIS_LEFTX);
    return (x < -INPUT_GAMEPAD_STICK_DEADZONE);
}

INTERNAL bool IsLeftStickUpPressed ()
{
    if (IsFading()) return false;
    if (!gInput.gamepad) return false;
    return (gInput.previous_left_stick_y >= -INPUT_GAMEPAD_STICK_DEADZONE &&
            gInput.current_left_stick_y < -INPUT_GAMEPAD_STICK_DEADZONE);
}
INTERNAL bool IsLeftStickRightPressed ()
{
    if (IsFading()) return false;
    if (!gInput.gamepad) return false;
    return (gInput.previous_left_stick_x <= INPUT_GAMEPAD_STICK_DEADZONE &&
            gInput.current_left_stick_x > INPUT_GAMEPAD_STICK_DEADZONE);
}
INTERNAL bool IsLeftStickDownPressed ()
{
    if (IsFading()) return false;
    if (!gInput.gamepad) return false;
    return (gInput.previous_left_stick_y <= INPUT_GAMEPAD_STICK_DEADZONE &&
            gInput.current_left_stick_y > INPUT_GAMEPAD_STICK_DEADZONE);
}
INTERNAL bool IsLeftStickLeftPressed ()
{
    if (IsFading()) return false;
    if (!gInput.gamepad) return false;
    return (gInput.previous_left_stick_x >= -INPUT_GAMEPAD_STICK_DEADZONE &&
            gInput.current_left_stick_x < -INPUT_GAMEPAD_STICK_DEADZONE);
}
