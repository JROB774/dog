GLOBAL constexpr float DOG_MOVE_SPEED = (8 * TILE_W);
GLOBAL constexpr float DOG_MAX_VEL = (20 * TILE_W);

GLOBAL constexpr float DOG_JUMP_FORCE = (25 * TILE_W);
GLOBAL constexpr float DOG_WEIGHT = 0.75f;

GLOBAL constexpr int DOG_CLIP_W = 24;
GLOBAL constexpr int DOG_CLIP_H = 24;

GLOBAL constexpr float DOG_BOUNDS_X =  5;
GLOBAL constexpr float DOG_BOUNDS_Y = 13;
GLOBAL constexpr float DOG_BOUNDS_W = 14;
GLOBAL constexpr float DOG_BOUNDS_H =  7;

INTERNAL void CreateDog (Dog& dog, float x, float y)
{
	dog.pos = { x, y };

	LoadImage(dog.image, "assets/dog.bmp");
	dog.flip = FLIP_NONE;
}

INTERNAL void UpdateDog (Dog& dog, float dt)
{
	// @Incomplete: ...
}

INTERNAL void DrawDog (Dog& dog, float dt)
{
	SDL_Rect clip = { 0,0,DOG_CLIP_W,DOG_CLIP_H };
	DrawImage(dog.image, dog.pos.x, dog.pos.y, dog.flip, &clip);
}
