void UpdateKeyboardState()
{
	memcpy(previous_keystates, current_keystates, SDL_NUM_SCANCODES * sizeof(U8));
	memcpy(current_keystates, SDL_GetKeyboardState(NULL), SDL_NUM_SCANCODES * sizeof(U8));
}

bool IsKeyDown(SDL_Scancode _code)
{
	if(_code < 0 || _code > SDL_NUM_SCANCODES){return false;}
	return (current_keystates[_code] != 0);
}

bool IsKeyUp(SDL_Scancode _code)
{
	if(_code < 0 || _code > SDL_NUM_SCANCODES){return false;}
	return (current_keystates[_code] == 0); 
}

bool IsKeyPressed(SDL_Scancode _code)
{
	if(_code < 0 || _code > SDL_NUM_SCANCODES){return false;}
	return (current_keystates[_code] == 1 && previous_keystates[_code] == 0);
}

bool IsKeyReleased(SDL_Scancode _code)
{
	if(_code < 0 || _code > SDL_NUM_SCANCODES){return false;}
	return (current_keystates[_code] == 0 && previous_keystates[_code] == 1);
}