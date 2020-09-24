#ifndef BONE_HPP
#define BONE_HPP

struct BoneCounter
{
	int small_bones_left;
	int large_bones_left;
};

struct SmallBone
{
	Rect bounds = {0,0,10,10};
};

struct BigBone
{
	Rect bounds = {0,0,16,16};
};

GLOBAL Image small_bone_image;
GLOBAL Image big_bone_image;

void InitBones();
bool SmallBoneCollision(Rect _bounds, SmallBone _bone);
bool BigBoneCollision(Rect _bounds, BigBone _bone);
void RenderBoneCounter(int _x, int _y);
void DeleteBones();

#endif