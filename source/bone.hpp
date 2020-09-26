#ifndef BONE_HPP
#define BONE_HPP

struct BoneCounter
{
	int small_bones_collected;
    int small_bones_total;
	int large_bones_collected;
    int large_bones_total;
};

struct SmallBone
{
    float x, y;
    float yoff;
	Rect bounds = {3,3,10,10};
	bool dead = false;
    float timer;
};

struct BigBone
{
    float x, y;
    float yoff;
	Rect bounds = {4,4,16,16};
	bool dead = false;
    float timer;
};

GLOBAL Image small_bone_image;
GLOBAL Image big_bone_image;
GLOBAL Sound small_bone_sound;
GLOBAL Sound big_bone_sound;

void InitBones();
void CreateSmallBone(SmallBone& _bone, float _x, float _y);
void CreateBigBone(BigBone& _bone, float _x, float _y);
// bool SmallBoneCollision(Rect _bounds, SmallBone _bone);
// bool BigBoneCollision(Rect _bounds, BigBone _bone);
// void RenderBoneCounter(int _x, int _y, BoneCounter _bonecounter);
void DeleteBones();
void RenderBigBone(BigBone& _bone, float dt);
void RenderSmallBone(SmallBone& _bone, float dt);

#endif