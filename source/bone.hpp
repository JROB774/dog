#ifndef BONE_HPP
#define BONE_HPP

GLOBAL constexpr int LARGE_BONE_WORTH = 10; // Large bones are worth 10 bones!

struct SmallBone
{
    std::string id;
    float x, y;
    float yoff;
	Rect bounds = {3,3,10,10};
	bool dead = false;
    float timer;
};

struct BigBone
{
    std::string id;
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

INTERNAL void InitBones();
INTERNAL void CreateSmallBone(SmallBone& bone, float x, float y);
INTERNAL void CreateBigBone(BigBone& bone, float x, float y);
INTERNAL void DeleteBones();
INTERNAL void RenderBigBone(BigBone& bone, float dt);
INTERNAL void RenderSmallBone(SmallBone& bone, float dt);

// COUNTER STUFF

std::vector<std::string> gBoneCollectedIds;
std::vector<std::string> gTempBoneCollectedIds;

int gCurrentZoneBoneTotal;

INTERNAL int  GetBoneCollectedCount ();
INTERNAL int  GetBoneTotalCount     ();
INTERNAL void CacheMapBones         ();
INTERNAL void RespawnMapBones       ();

#endif
