void InitCrushBoi()
{
	LoadImage(gCrushBoiImage, "crushboi.bmp");
}

void CreateCrushBoi(CrushBoi& _boi, float _x, float _y, bool _vertical)
{
	_boi.pos = {_x,_y};
	_boi.start_pos = {_x, _y};
	_boi.vel = { 0, 0};
	_boi.vertical = _vertical;
	_boi.active = false;
	_boi.bounds = {0,0,16,16};
}

void UpdateCrushBoi(CrushBoi& _boi, float _dt)
{
	if(_boi.active){
		Vec2 we_arent_using_this = {0,0};
		if(EntityAndMapCollision(_boi.pos,_boi.bounds, _boi.vel, gWorld.current_map, we_arent_using_this, _dt)){
			//This is where particles go
			Vec2 particle_pos = {0,0};
			if(_boi.vertical){
				particle_pos.x =  _boi.pos.x + (_boi.bounds.w/2);
				if(_boi.vel.y > 0){
					particle_pos.y = _boi.pos.y;
					CreateParticles(PARTICLE_TYPE_BASH_UP, (int)particle_pos.x,(int)particle_pos.y,(int)particle_pos.x,(int)particle_pos.y, 4,8);
				}
				if(_boi.vel.y < 0){
					particle_pos.y = _boi.pos.y + _boi.bounds.h;
					CreateParticles(PARTICLE_TYPE_BASH, (int)particle_pos.x,(int)particle_pos.y,(int)particle_pos.x,(int)particle_pos.y, 4,8);
				}	
			}
			
			_boi.active = false;
		}
		if(_boi.vertical ){_boi.pos.y += _boi.vel.y * _dt;}
		if(!_boi.vertical){_boi.pos.x += _boi.vel.x * _dt;}
	}

	if(gGameState.dog.dead){return;}

	if(!_boi.active){
		if(_boi.vertical){
			float temp = gGameState.dog.bounds.x + gGameState.dog.pos.x;
			if(temp < _boi.pos.x && temp + gGameState.dog.bounds.w > _boi.pos.x || temp > _boi.pos.x && temp < _boi.pos.x + 16){
				_boi.active = true;
				temp = gGameState.dog.bounds.y + gGameState.dog.pos.y;
				if(temp < _boi.pos.y){_boi.vel.y = -150;}
				if(temp > _boi.pos.y){_boi.vel.y =  150;}
			}
		}
		if(!_boi.vertical){
			float temp = gGameState.dog.bounds.y + gGameState.dog.pos.y;
			if(temp < _boi.pos.y && temp + gGameState.dog.bounds.h > _boi.pos.y || temp > _boi.pos.y && temp < _boi.pos.y + 16){
				_boi.active = true;
				temp = gGameState.dog.bounds.x + gGameState.dog.pos.x;
				if(temp < _boi.pos.x){_boi.vel.x = -150;}
				if(temp > _boi.pos.x){_boi.vel.x =  150;}
			}
		}
	}
}

void RenderCrushBoi(CrushBoi& _boi)
{
	SDL_Rect temp_clip = gCrushBoiClip;
	if(_boi.vertical){temp_clip.x += 16;}
	DrawImage(gCrushBoiImage, _boi.pos.x, _boi.pos.y, SDL_FLIP_NONE, &temp_clip);
}

void ResetCrushBoi(CrushBoi& _boi)
{
	_boi.pos = _boi.start_pos;
	_boi.active = false;
}

void DestroyCrushBoi(CrushBoi& _boi)
{

}
