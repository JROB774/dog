#ifndef  CRUSHBOI_HPP
#define CRUSHBOI_HPP

//Left and Right Light Lime #B6FF00
//Up and Down Dark Lime #5B7F00

struct CrushBoi
{
	bool vertical;
	bool active;

	float x;
	float y;

	float vel;
	
};

GLOBAL SDL_Rect gCrushBoiClip = {0, 0, 16, 16}; 
GLOBAL Image gCrushBoiImage;
//GLOBAL Sound gCrushBoiMove;
//GLOBAL Sound gCrushBoiCollision; to do later

void InitCrushBoi();
void DeinitCrushBoi();
void CreateCrushBoi(CrushBoi& _boi, float _x, float _y, bool _vertical);
void UpdateCrushBoi(CrushBoi& _boi);
void RenderCrushBoi(CrushBoi& _boi);
void DestroyCrushBoi(CrushBoi& _boi);

#endif