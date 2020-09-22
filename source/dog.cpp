GLOBAL constexpr float DOG_MOVE_SPEED = (8 * TILE_W);
GLOBAL constexpr float DOG_MAX_VEL = (20 * TILE_W);

GLOBAL constexpr float DOG_JUMP_FORCE = (25 * TILE_W);

GLOBAL constexpr int DOG_CLIP_W = 24;
GLOBAL constexpr int DOG_CLIP_H = 24;

GLOBAL constexpr float DOG_BOUNDS_X =  5;
GLOBAL constexpr float DOG_BOUNDS_Y = 13;
GLOBAL constexpr float DOG_BOUNDS_W = 14;
GLOBAL constexpr float DOG_BOUNDS_H =  7;

INTERNAL void CreateDog (Dog& dog, float x, float y)
{
	dog.pos = { x, y };
	dog.vel = { 0, 0 };

	dog.bounds = { DOG_BOUNDS_X,DOG_BOUNDS_Y,DOG_BOUNDS_W,DOG_BOUNDS_H };

	LoadImage(dog.image, "assets/dog.bmp");
	dog.flip = FLIP_NONE;

	dog.left = false;
	dog.right = false;

	dog.grounded = false;
}

INTERNAL void UpdateDog (Dog& dog, float dt)
{
	dog.right = IsKeyDown(SDL_SCANCODE_RIGHT);
	dog.left  = IsKeyDown(SDL_SCANCODE_LEFT);

	// Only if one direction is being pressed will we move the dog.
	if (dog.right != dog.left)
	{
		if (dog.right) { dog.pos.x += (DOG_MOVE_SPEED * dt); dog.flip = FLIP_NONE; } // Move right.
		if (dog.left ) { dog.pos.x -= (DOG_MOVE_SPEED * dt); dog.flip = FLIP_HORZ; } // Move left.
	}

	// Apply a jump force if the key is presed.
	if (dog.grounded)
	{
		if (IsKeyPressed(SDL_SCANCODE_Z))
		{
			dog.vel.y -= DOG_JUMP_FORCE;
			dog.grounded = false;
		}
	}

	// Apply a gravity force to the dog.
	if (!dog.grounded) dog.vel.y += GRAVITY; else dog.vel.y = 0.0f;

	// Clamp the velocity in range.
	// if (dog.vel.y < -DOG_MAX_VEL) dog.vel.y = -DOG_MAX_VEL;
	// if (dog.vel.y >  DOG_MAX_VEL) dog.vel.y =  DOG_MAX_VEL;
	// if (dog.vel.x < -DOG_MAX_VEL) dog.vel.x = -DOG_MAX_VEL;
	// if (dog.vel.x >  DOG_MAX_VEL) dog.vel.x =  DOG_MAX_VEL;

	// Apply velocity to the dog.
	dog.pos.x += (dog.vel.x * dt);
	dog.pos.y += (dog.vel.y * dt);

	// Perform simple collision detection on the dog.
	for (int iy=0; iy<gGameState.map.h; ++iy)
	{
		for (int ix=0; ix<gGameState.map.w; ++ix)
		{
			Tile* tile = &gGameState.map.tiles[iy*gGameState.map.w+ix];
			if (tile->type == TILE_SOLID)
			{
				Rect intersection;
				if (TileEntityCollision(dog.pos,dog.bounds, ix,iy, intersection))
				{
					if (intersection.w < intersection.h)
					{
						dog.pos.x -= intersection.w;
					}
					else
					{
						dog.pos.y -= intersection.h;
						dog.grounded = true;
					}
				}
			}
		}
	}
}

INTERNAL void DrawDog (Dog& dog, float dt)
{
	SDL_Rect clip = { 0,0,DOG_CLIP_W,DOG_CLIP_H };
	DrawImage(dog.image, dog.pos.x, dog.pos.y, dog.flip, &clip);

	DrawFill(dog.pos.x+dog.bounds.x,dog.pos.y+dog.bounds.y,dog.bounds.w,dog.bounds.h, MakeColor(1,0,0,0.25f));
}
