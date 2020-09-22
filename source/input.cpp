GLOBAL U8 gPreviousKeystate[SDL_NUM_SCANCODES];
GLOBAL U8 gCurrentKeystate[SDL_NUM_SCANCODES];

INTERNAL void UpdateKeyboardState ()
{
	memcpy(gPreviousKeystate, gCurrentKeystate, SDL_NUM_SCANCODES * sizeof(U8));
	memcpy(gCurrentKeystate, SDL_GetKeyboardState(NULL), SDL_NUM_SCANCODES * sizeof(U8));
}

INTERNAL bool IsKeyDown (SDL_Scancode code)
{
	if (code < 0 || code > SDL_NUM_SCANCODES) return false;
	return (gCurrentKeystate[code] != 0);
}

INTERNAL bool IsKeyUp (SDL_Scancode code)
{
	if (code < 0 || code > SDL_NUM_SCANCODES) return false;
	return (gCurrentKeystate[code] == 0);
}

INTERNAL bool IsKeyPressed (SDL_Scancode code)
{
	if (code < 0 || code > SDL_NUM_SCANCODES) return false;
	return (gCurrentKeystate[code] == 1 && gPreviousKeystate[code] == 0);
}

INTERNAL bool IsKeyReleased (SDL_Scancode code)
{
	if(code < 0 || code > SDL_NUM_SCANCODES) return false;
	return (gCurrentKeystate[code] == 0 && gPreviousKeystate[code] == 1);
}
