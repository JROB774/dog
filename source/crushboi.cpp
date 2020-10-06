void InitCrushBoi()
{
	LoadImage(gCrushBoiImage, "crushboi.bmp");
}

void CreateCrushBoi(CrushBoi& _boi, float _x, float _y, bool _vertical)
{
	_boi.x = _x;
	_boi.y = _y;
	_boi.vertical = _vertical;
	_boi.active = false;
}

void UpdateCrushBoi(CrushBoi& _boi, float _dt)
{
	if(_boi.active){
		if(_boi.vertical ){_boi.x += 15 * _dt;}
		if(!_boi.vertical){_boi.y += 15 * _dt;}
	}

	if(!_boi.active){
		if(_boi.vertical){
			float temp = gGameState.dog.bounds.x + gGameState.dog.pos.x;
			if(temp < _boi.x && temp + gGameState.dog.bounds.w > _boi.x || temp > _boi.x && temp < _boi.x + 16){printf("true\n");}
		}
	}
}

void RenderCrushBoi(CrushBoi& _boi)
{
	SDL_Rect temp_clip = gCrushBoiClip;
	if(_boi.vertical){temp_clip.x += 16;}
	DrawImage(gCrushBoiImage, _boi.x, _boi.y, SDL_FLIP_NONE, &temp_clip);
}

void DestroyCrushBoi(CrushBoi& _boi)
{

}
