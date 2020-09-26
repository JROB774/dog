void InitBones()
{
	LoadImage(small_bone_image, "sbone.bmp");
	LoadImage(big_bone_image, "lbone.bmp");
	LoadSound(small_bone_sound, "sbone.wav");
	LoadSound(big_bone_sound, "lbone.wav");
}

/*
bool SmallBoneCollision(Rect _bounds, SmallBone _bone)
{
	if(!_bone.dead){
		if((_bounds.x + _bounds.w > _bone.bounds.x) && (_bounds.y +_bounds.h > _bone.bounds.y) &&
			(_bounds.x < _bone.x + _bone.bounds.x + _bone.bounds.w) && (_bounds.y < _bone.y + _bone.bounds.y + _bone.bounds.h)){
				return true;
		}
	}
	return false;
}

bool BigBoneCollision(Rect _bounds, BigBone _bone)
{
	if(!_bone.dead){
		if((_bounds.x + _bounds.w > _bone.bounds.x) && (_bounds.y +_bounds.h > _bone.bounds.y) &&
			(_bounds.x < _bone.x + _bone.bounds.x + _bone.bounds.w) && (_bounds.y < _bone.y + _bone.bounds.y + _bone.bounds.h)){
				return true;
		}
	}
	return false;
}
*/

void CreateSmallBone(SmallBone& _bone, float _x, float _y)
{
	_bone.x = _x;
	_bone.y = _y;
	_bone.yoff = 0;
	// _bone.bounds = {_x, _y, 10, 10};
	_bone.dead = false;
	_bone.timer = 0.0f;
}

void CreateBigBone(BigBone& _bone, float _x, float _y)
{
	_bone.x = _x - 4;
	_bone.y = _y - 4;
	_bone.yoff = 0;
	// _bone.bounds = {_x, _y, 16, 16};
	_bone.dead = false;
	_bone.timer = 0.0f;
}

void RenderBigBone(BigBone& _bone, float dt)
{
	if (_bone.dead) return;
	_bone.timer += dt;
	_bone.yoff = SinRange(0, 4, _bone.timer*5);
	DrawImage(big_bone_image, _bone.x, _bone.y-_bone.yoff);
}

void RenderSmallBone(SmallBone& _bone, float dt)
{
	if (_bone.dead) return;
	_bone.timer += dt;
	_bone.yoff = SinRange(0, 2, _bone.timer*5);
	DrawImage(small_bone_image, _bone.x, _bone.y-_bone.yoff);
}

/*
void RenderBoneCounter(int _x, int _y, BoneCounter _bonecounter)
{
	DrawFont(std::to_string(_bonecounter.small_bones_left),10, 10);
	DrawFont(std::to_string(_bonecounter.large_bones_left),10, 52);
}
*/

void DeleteBones()
{
	FreeImage(small_bone_image);
	FreeImage(big_bone_image);
	FreeSound(small_bone_sound);
	FreeSound(big_bone_sound);
}
