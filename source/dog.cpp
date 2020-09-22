GLOBAL constexpr float DOG_MOVE_SPEED = (8 * TILE_W); // Tiles-per-second.
GLOBAL constexpr float DOG_MAX_VEL = (20 * TILE_W); // Tiles-per-second.

GLOBAL constexpr float DOG_WEIGHT = 1.0f;

GLOBAL constexpr int DOG_CLIP_W = 24;
GLOBAL constexpr int DOG_CLIP_H = 24;

INTERNAL void CreateDog (Dog& dog, float x, float y)
{
	dog.pos = { x, y };
	dog.vel = { 0, 0 };

	LoadImage(dog.image, "assets/dog.bmp");
	dog.flip = FLIP_NONE;

	dog.left = false;
	dog.right = false;
	dog.jump = false;
	dog.action = false;
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

	// Apply a gravity force to the dog.
	dog.vel.y += (DOG_WEIGHT * GRAVITY);

	// Clamp the velocity in range.
	if (dog.vel.y < -DOG_MAX_VEL) dog.vel.y = -DOG_MAX_VEL;
	if (dog.vel.y >  DOG_MAX_VEL) dog.vel.y =  DOG_MAX_VEL;
	if (dog.vel.x < -DOG_MAX_VEL) dog.vel.x = -DOG_MAX_VEL;
	if (dog.vel.x >  DOG_MAX_VEL) dog.vel.x =  DOG_MAX_VEL;

	// Apply velocity to the dog.
	dog.pos.x += (dog.vel.x * dt);
	dog.pos.y += (dog.vel.y * dt);

	// Perform simple collision detection on the dog.

	// @Incomplete: ...

	/*
	if(IsKeyDown(SDL_SCANCODE_D) || IsKeyDown(SDL_SCANCODE_RIGHT)){dog.right = true; dog.left = false;}
		else{dog.right = false;}
	if(IsKeyDown(SDL_SCANCODE_A) || IsKeyDown(SDL_SCANCODE_LEFT)){dog.left = true; dog.right = false;}
		else{dog.left = false;}

	if(IsKeyPressed(SDL_SCANCODE_W) || IsKeyPressed(SDL_SCANCODE_UP) || IsKeyPressed(SDL_SCANCODE_SPACE) || IsKeyPressed(SDL_SCANCODE_Z)){dog.jump = true;}
	if(IsKeyPressed(SDL_SCANCODE_S) || IsKeyPressed(SDL_SCANCODE_DOWN) || IsKeyPressed(SDL_SCANCODE_E) || IsKeyPressed(SDL_SCANCODE_X)){dog.action = true;}

	if(dog.right){
		dog.vel_x += 60;
		if(dog.vel_x > dog.max_vel_x){dog.vel_x = dog.max_vel_x;}
	}

	if(dog.left){
		dog.vel_x -= 60;
		if(dog.vel_x < -dog.max_vel_x){dog.vel_x = -dog.max_vel_x;}
	}

	//Resistance
	if(!dog.right && !dog.left){
		if(dog.vel_x > 0){
			if(dog.vel_x <= 5){dog.vel_x = 0;}
			else{dog.vel_x -= 5;}
		}
		if(dog.vel_x < 0){
			if(dog.vel_x >= -5){dog.vel_x = 0;}
			else{dog.vel_x += 5;}
		}
	}

	dog.x += (dt * dog.vel_x);
	*/
}

INTERNAL void DrawDog (Dog& dog, float dt)
{
	SDL_Rect clip = { 0,0,DOG_CLIP_W,DOG_CLIP_H };
	DrawImage(dog.image, dog.pos.x, dog.pos.y, dog.flip, &clip);
}
