INTERNAL void InitCrushBoi()
{
    LoadImage(gCrushBoiImage, "crushboi.bmp");
    LoadSound(gCrushBoiHitSound, "crush.wav");
}

INTERNAL void QuitCrushBoi()
{
    FreeSound(gCrushBoiHitSound);
    FreeImage(gCrushBoiImage);
}

INTERNAL void CreateCrushBoi(CrushBoi& _boi, float _x, float _y, bool _vertical)
{
    _boi.pos = {_x,_y};
    _boi.start_pos = {_x, _y};
    _boi.vel = { 0, 0};
    _boi.vertical = _vertical;
    _boi.active = false;
    _boi.bounds = {0,0,16,16};
}

INTERNAL void UpdateCrushBoi(CrushBoi& _boi, float _dt)
{
    if(_boi.active){
        Vec2 we_arent_using_this = {0,0};
        if(EntityAndMapCollision(_boi.pos,_boi.bounds, _boi.vel, gWorld.current_map, we_arent_using_this, _dt)){
            //This is where particles go
            Vec2 particle_pos = {0,0};
            if(_boi.vertical){
                particle_pos.x = _boi.pos.x;
                if(_boi.vel.y < 0){
                    particle_pos.y = _boi.pos.y;
                    CreateParticlesRotated(PARTICLE_TYPE_PUFF_D, (int)particle_pos.x-2,(int)particle_pos.y,(int)particle_pos.x + 16,(int)particle_pos.y + 2, 4, 8, DegToRad(180));
                    PlaySound(gCrushBoiHitSound);
                }
                if(_boi.vel.y > 0){
                    particle_pos.y = _boi.pos.y + _boi.bounds.h;
                    CreateParticlesRotated(PARTICLE_TYPE_PUFF_D, (int)particle_pos.x-2,(int)particle_pos.y,(int)particle_pos.x + 16,(int)particle_pos.y, 4, 8, DegToRad(0));
                    PlaySound(gCrushBoiHitSound);
                }
            }
            if(!_boi.vertical){
                particle_pos.y = _boi.pos.y;
                if(_boi.vel.x < 0){
                    particle_pos.x = _boi.pos.x;
                    CreateParticlesRotated(PARTICLE_TYPE_PUFF_D, (int)particle_pos.x,(int)particle_pos.y - 2,(int)particle_pos.x,(int)particle_pos.y + 16, 4, 8, DegToRad(90));
                    PlaySound(gCrushBoiHitSound);
                }
                if(_boi.vel.x > 0){
                    particle_pos.x = _boi.pos.x + _boi.bounds.w;
                    CreateParticlesRotated(PARTICLE_TYPE_PUFF_D, (int)particle_pos.x,(int)particle_pos.y - 2,(int)particle_pos.x,(int)particle_pos.y + 16, 4, 8, DegToRad(180));
                    PlaySound(gCrushBoiHitSound);
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
                if(temp < _boi.pos.y){_boi.vel.y = -225;}
                if(temp > _boi.pos.y){_boi.vel.y =  225;}
            }
        }
        if(!_boi.vertical){
            float temp = gGameState.dog.bounds.y + gGameState.dog.pos.y;
            if(temp < _boi.pos.y && temp + gGameState.dog.bounds.h > _boi.pos.y || temp > _boi.pos.y && temp < _boi.pos.y + 16){
                _boi.active = true;
                temp = gGameState.dog.bounds.x + gGameState.dog.pos.x;
                if(temp < _boi.pos.x){_boi.vel.x = -225;}
                if(temp > _boi.pos.x){_boi.vel.x =  225;}
            }
        }
    }
}

INTERNAL void RenderCrushBoi(CrushBoi& _boi)
{
    SDL_Rect temp_clip = gCrushBoiClip;
    if(_boi.vertical){temp_clip.x += 16;}
    DrawImage(gCrushBoiImage, _boi.pos.x, _boi.pos.y, SDL_FLIP_NONE, &temp_clip);
}

INTERNAL void ResetCrushBoi(CrushBoi& _boi)
{
    _boi.pos = _boi.start_pos;
    _boi.active = false;
}
