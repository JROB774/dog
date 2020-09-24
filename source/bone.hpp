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
	bool dead = false;
};

struct BigBone
{
	Rect bounds = {0,0,16,16};
	bool dead = false;
};

GLOBAL Image small_bone_image;
GLOBAL Image big_bone_image;

void InitBones();
void CreateSmallBone(SmallBone& _bone, float _x, float _y);
void CreateBigBone(BigBone& _bone, float _x, float _y);
bool SmallBoneCollision(Rect _bounds, SmallBone _bone);
bool BigBoneCollision(Rect _bounds, BigBone _bone);
void RenderBoneCounter(int _x, int _y, BoneCounter _bonecounter);
void DeleteBones();

#endif