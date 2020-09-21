void DogCreate()
{
	LoadImage(gDog.image, "assets/dog.bmp");
}

void DogUpdate(float _dt)
{

	if(IsKeyDown(SDL_SCANCODE_D) || IsKeyDown(SDL_SCANCODE_RIGHT)){gDog.right = true; gDog.left = false;}
		else{gDog.right = false;}
	if(IsKeyDown(SDL_SCANCODE_A) || IsKeyDown(SDL_SCANCODE_LEFT)){gDog.left = true; gDog.right = false;}
		else{gDog.left = false;}

	if(IsKeyPressed(SDL_SCANCODE_W) || IsKeyPressed(SDL_SCANCODE_UP) || IsKeyPressed(SDL_SCANCODE_SPACE) || IsKeyPressed(SDL_SCANCODE_Z)){gDog.jump = true;}
	if(IsKeyPressed(SDL_SCANCODE_S) || IsKeyPressed(SDL_SCANCODE_DOWN) || IsKeyPressed(SDL_SCANCODE_E) || IsKeyPressed(SDL_SCANCODE_X)){gDog.action = true;}

	if(gDog.right){
		gDog.vel_x += 60;
		if(gDog.vel_x > gDog.max_vel_x){gDog.vel_x = gDog.max_vel_x;}
	}

	if(gDog.left){
		gDog.vel_x -= 60;
		if(gDog.vel_x < -gDog.max_vel_x){gDog.vel_x = -gDog.max_vel_x;}
	}

	//Resistance
	if(!gDog.right && !gDog.left){
		if(gDog.vel_x > 0){
			if(gDog.vel_x <= 5){gDog.vel_x = 0;}
			else{gDog.vel_x -= 5;}
		}
		if(gDog.vel_x < 0){
			if(gDog.vel_x >= -5){gDog.vel_x = 0;}
			else{gDog.vel_x += 5;}
		}
	}

	gDog.x += (_dt * gDog.vel_x);
}

void DogDraw()
{
	SDL_Rect clip = {0,0,24,24};

	DrawImage(gDog.image, gDog.x, gDog.y, &clip);
}