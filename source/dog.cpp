INTERNAL void CreateDog (Dog& dog, float x, float y)
{
	LoadImage(dog.image, "assets/dog.bmp");
}

INTERNAL void UpdateDog (Dog& dog, float dt)
{

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
}

INTERNAL void DrawDog (Dog& dog, float dt)
{
	SDL_Rect clip = {0,0,24,24};

	DrawImage(dog.image, dog.x, dog.y, &clip);
}
