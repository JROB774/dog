INTERNAL void InitBones()
{
	LoadImage(small_bone_image, "sbone.bmp");
	LoadImage(big_bone_image, "lbone.bmp");
	LoadSound(small_bone_sound, "sbone.wav");
	LoadSound(big_bone_sound, "lbone.wav");
}

INTERNAL void CreateSmallBone(SmallBone& bone, float x, float y)
{
	bone.id = gWorld.current_map_name + "-" + std::to_string((int)x) + "-" + std::to_string((int)y) + "-s";
	bone.x = x;
	bone.y = y;
	bone.yoff = 0;
	bone.dead = false;
	bone.timer = 0.0f;
}

INTERNAL void CreateBigBone(BigBone& bone, float x, float y)
{
	bone.id = gWorld.current_map_name + "-" + std::to_string((int)x) + "-" + std::to_string((int)y) + "-l";
	bone.x = x-4;
	bone.y = y-4;
	bone.yoff = 0;
	// _bone.bounds = {_x, _y, 16, 16};
	bone.dead = false;
	bone.timer = 0.0f;
}

INTERNAL void RenderBigBone(BigBone& bone, float dt)
{
	if (bone.dead) return;
	bone.timer += dt;
	bone.yoff = SinRange(0, 4, bone.timer*5);
	DrawImage(big_bone_image, bone.x, bone.y-bone.yoff);
}

INTERNAL void RenderSmallBone(SmallBone& bone, float dt)
{
	if (bone.dead) return;
	bone.timer += dt;
	bone.yoff = SinRange(0, 2, bone.timer*5);
	DrawImage(small_bone_image, bone.x, bone.y-bone.yoff);
}

INTERNAL void DeleteBones()
{
	FreeImage(small_bone_image);
	FreeImage(big_bone_image);
	FreeSound(small_bone_sound);
	FreeSound(big_bone_sound);
}
