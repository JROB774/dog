#ifndef DOG_HPP
#define DOG_HPP

GLOBAL struct Dog
{
	float x;
	float y;
	float vel_x;
	float vel_y;

	const int width = 24;
	const int height = 24;

	Image image;
} gDog;

void DogCreate();
void DogUpdate();
void DogDraw();

#endif