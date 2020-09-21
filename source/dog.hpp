#ifndef DOG_HPP
#define DOG_HPP

GLOBAL struct Dog
{
	float x;
	float y;
	float vel_x;
	float vel_y;

	bool left = false;
	bool right = false;
	bool jump = false;
	bool action = false;

	const float max_vel_x = 10;
	const float max_vel_y = 10;

	const int width = 24;
	const int height = 24;

	Image image;
} gDog;

void DogCreate();
void DogUpdate();
void DogDraw();

#endif