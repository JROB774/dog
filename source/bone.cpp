void InitBones()
{
	LoadImage(small_bone_image, "sbone.bmp");
	LoadImage(big_bone_image, "lbone.bmp");
}

bool SmallBoneCollision(Rect _bounds, SmallBone _bone)
{
	if((_bounds.x + _bounds.w > _bone.bounds.x) && (_bounds.y +_bounds.h > _bone.bounds.y) &&
		(_bounds.x < _bone.bounds.x + _bone.bounds.w) && (_bounds.y < _bone.bounds.y + _bone.bounds.h)){
			return true;
	}
	return false;
}

bool BigBoneCollision(Rect _bounds, BigBone _bone)
{
	if((_bounds.x + _bounds.w > _bone.bounds.x) && (_bounds.y +_bounds.h > _bone.bounds.y) &&
		(_bounds.x < _bone.bounds.x + _bone.bounds.w) && (_bounds.y < _bone.bounds.y + _bone.bounds.h)){
			return true;
	}
	return false;
}

void RenderBoneCounter(int _x, int _y, BoneCounter _bonecounter)
{
	DrawFont(std::to_string(_bonecounter.small_bones_left),10, 10);
	DrawFont(std::to_string(_bonecounter.large_bones_left),10, 52);
}

void DeleteBones()
{
	FreeImage(small_bone_image);
	FreeImage(big_bone_image);
}