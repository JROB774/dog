void DogCreate()
{
	LoadImage(gDog.image, "assets/dog.bmp");
}

void DogUpdate()
{

	if(IsKeyDown(SDL_SCANCODE_D) || IsKeyDown(SDL_SCANCODE_RIGHT)){gDog.right = true;}
	if(IsKeyDown(SDL_SCANCODE_A) || IsKeyDown(SDL_SCANCODE_LEFT)){gDog.left = true;}
	if(IsKeyPressed(SDL_SCANCODE_W) || IsKeyPressed(SDL_SCANCODE_UP) || IsKeyPressed(SDL_SCANCODE_SPACE) || IsKeyPressed(SDL_SCANCODE_Z)){gDog.jump = true;}
	if(IsKeyPressed(SDL_SCANCODE_S) || IsKeyPressed(SDL_SCANCODE_DOWN) || IsKeyPressed(SDL_SCANCODE_E) || IsKeyPressed(SDL_SCANCODE_X)){gDog.action = true;}

	if(gDog.right){gDog.vel_x += 2;}






}

void DogDraw()
{
	SDL_Rect clip = {0,0,24,24};

	DrawImage(gDog.image, gDog.x, gDog.y, &clip);
}