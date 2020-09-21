void DogCreate()
{
	LoadImage(gDog.image, "assets/dog.bmp");
}

void DogUpdate()
{

}

void DogDraw()
{
	SDL_Rect clip = {0,0,24,24};

	DrawImage(gDog.image, gDog.x, gDog.y, &clip);
}