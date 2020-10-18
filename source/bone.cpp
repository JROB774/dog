INTERNAL void InitBones ()
{
    LoadImage(gSmallBoneImage, "sbone.bmp");
    LoadImage(gBigBoneImage, "lbone.bmp");
    LoadSound(gSmallBoneSound, "sbone.wav");
    LoadSound(gBigBoneSound, "lbone.wav");
}

INTERNAL void CreateSmallBone (SmallBone& bone, float x, float y)
{
    bone.id    = gWorld.current_map_name + "-" + std::to_string((int)x) + "-" + std::to_string((int)y) + "-s";
    bone.x     = x;
    bone.y     = y;
    bone.yoff  = 0;
    bone.dead  = false;
    bone.timer = 0.0f;
}

INTERNAL void CreateBigBone (BigBone& bone, float x, float y)
{
    bone.id    = gWorld.current_map_name + "-" + std::to_string((int)x) + "-" + std::to_string((int)y) + "-l";
    bone.x     = x-4;
    bone.y     = y-4;
    bone.yoff  = 0;
    bone.dead  = false;
    bone.timer = 0.0f;
}

INTERNAL void RenderBigBone (BigBone& bone, float dt)
{
    bone.timer += dt;
    bone.yoff = SinRange(0, 4, bone.timer*5);
    if (bone.dead) return; // Important it goes here so the bone doesn't go out of sync if it gets respawned!
    DrawImage(gBigBoneImage, bone.x, bone.y-bone.yoff);
}

INTERNAL void RenderSmallBone (SmallBone& bone, float dt)
{
    bone.timer += dt;
    bone.yoff = SinRange(0, 2, bone.timer*5);
    if (bone.dead) return; // Important it goes here so the bone doesn't go out of sync if it gets respawned!
    DrawImage(gSmallBoneImage, bone.x, bone.y-bone.yoff);
}

INTERNAL void DeleteBones ()
{
    FreeImage(gSmallBoneImage);
    FreeImage(gBigBoneImage);
    FreeSound(gSmallBoneSound);
    FreeSound(gBigBoneSound);
}

// COUNTER STUFF

INTERNAL int GetBoneCollectedCount ()
{
    int collected = 0;
    for (auto& id:     gBoneCollectedIds) if (id.back() == 's') collected++;
    for (auto& id: gTempBoneCollectedIds) if (id.back() == 's') collected++;
    return collected;
}

INTERNAL int GetBoneTotalCount ()
{
    return gCurrentZoneBoneTotal;
}

INTERNAL void CacheMapBones ()
{
    gBoneCollectedIds.insert(gBoneCollectedIds.end(), gTempBoneCollectedIds.begin(), gTempBoneCollectedIds.end());
    gTempBoneCollectedIds.clear();
}

INTERNAL void RespawnMapBones ()
{
    // If a bone hasn't been collected and cached then it can be respawned.
    gTempBoneCollectedIds.clear();
    for (auto& sbone: gWorld.current_map.sbones)
    {
        if (std::find(gBoneCollectedIds.begin(), gBoneCollectedIds.end(), sbone.id) == gBoneCollectedIds.end())
        {
            sbone.dead = false;
        }
    }
    for (auto& lbone: gWorld.current_map.lbones)
    {
        if (std::find(gBoneCollectedIds.begin(), gBoneCollectedIds.end(), lbone.id) == gBoneCollectedIds.end())
        {
            lbone.dead = false;
        }
    }
}
