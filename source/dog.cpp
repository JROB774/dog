GLOBAL constexpr float DOG_MOVE_SPEED = (10 * TILE_W);
GLOBAL constexpr float DOG_MAX_VEL = (20 * TILE_W);

GLOBAL constexpr float DOG_JUMP_FORCE = (25 * TILE_W);
GLOBAL constexpr float DOG_WEIGHT = 0.75f;

GLOBAL constexpr int DOG_CLIP_W = 24;
GLOBAL constexpr int DOG_CLIP_H = 24;

GLOBAL constexpr float DOG_BOUNDS_X =  5;
GLOBAL constexpr float DOG_BOUNDS_Y = 13;
GLOBAL constexpr float DOG_BOUNDS_W = 14;
GLOBAL constexpr float DOG_BOUNDS_H =  7;

GLOBAL constexpr float DOG_DEAD_TIME = 2.0f;

INTERNAL void CreateDog (Dog& dog, float x, float y)
{
    dog.state = DOG_STATE_IDLE;

    dog.pos = { x, y };
    dog.vel = { 0, 0 };

    dog.bounds = { DOG_BOUNDS_X,DOG_BOUNDS_Y,DOG_BOUNDS_W,DOG_BOUNDS_H };

    LoadImage(dog.image, "dog.bmp");
    dog.flip = FLIP_NONE;

    dog.footstep_timer = 0.0f;

    LoadSound(dog.snd_footstep, "footstep.wav");
    LoadSound(dog.snd_land, "land.wav");
    LoadSound(dog.snd_hithead, "hithead.wav");
    LoadSound(dog.snd_jump, "jump.wav");
    LoadSound(dog.snd_bark, "bark.wav");
    LoadSound(dog.snd_explode0, "explode0.wav");
    LoadSound(dog.snd_explode1, "explode1.wav");

    LoadAnimation(dog.anim[DOG_STATE_IDLE], "dog-idle.anim");
    LoadAnimation(dog.anim[DOG_STATE_BLNK], "dog-blnk.anim");
    LoadAnimation(dog.anim[DOG_STATE_MOVE], "dog-move.anim");
    LoadAnimation(dog.anim[DOG_STATE_JUMP], "dog-jump.anim");
    LoadAnimation(dog.anim[DOG_STATE_FALL], "dog-fall.anim");
    LoadAnimation(dog.anim[DOG_STATE_BARK], "dog-bark.anim");

    dog.up           = false;
    dog.right        = false;
    dog.down         = false;
    dog.left         = false;
    dog.jump_press   = false;
    dog.jump_release = false;
    dog.action       = false;

    dog.grounded = true;

    dog.ledge_buffer = 0.0f;
    dog.jump_height = 0.0f;

    dog.dead_timer = 0.0f;
    dog.dead = false;

    // This gets updated whenever the dog transitions from room-to-room and acts as the respawn point.
    dog.start_state    = dog.state;
    dog.start_pos      = dog.pos;
    dog.start_vel      = dog.vel;
    dog.start_flip     = dog.flip;
    dog.start_grounded = dog.grounded;
}

INTERNAL void UpdateDog (Dog& dog, float dt)
{
    bool old_grounded = dog.grounded;
    Vec2 old_vel = dog.vel;

    // CreateParticles(PARTICLE_TYPE_TEST, (int)gGameState.dog.pos.x,(int)gGameState.dog.pos.y,(int)gGameState.dog.pos.x+24,(int)gGameState.dog.pos.y+24, 4,10);

    // Handle controls!!!
    dog.up           = (IsKeyDown(SDL_SCANCODE_UP)    || IsKeyDown(SDL_SCANCODE_W)         || IsButtonDown(SDL_CONTROLLER_BUTTON_DPAD_UP)    || IsLeftStickUp());
    dog.right        = (IsKeyDown(SDL_SCANCODE_RIGHT) || IsKeyDown(SDL_SCANCODE_D)         || IsButtonDown(SDL_CONTROLLER_BUTTON_DPAD_RIGHT) || IsLeftStickRight());
    dog.down         = (IsKeyDown(SDL_SCANCODE_DOWN)  || IsKeyDown(SDL_SCANCODE_S)         || IsButtonDown(SDL_CONTROLLER_BUTTON_DPAD_DOWN)  || IsLeftStickDown());
    dog.left         = (IsKeyDown(SDL_SCANCODE_LEFT)  || IsKeyDown(SDL_SCANCODE_A)         || IsButtonDown(SDL_CONTROLLER_BUTTON_DPAD_LEFT)  || IsLeftStickLeft());
    dog.jump_press   = (IsKeyPressed(SDL_SCANCODE_Z)  || IsKeyPressed(SDL_SCANCODE_SPACE)  || IsButtonPressed(SDL_CONTROLLER_BUTTON_A));
    dog.jump_release = (IsKeyReleased(SDL_SCANCODE_Z) || IsKeyReleased(SDL_SCANCODE_SPACE) || IsButtonReleased(SDL_CONTROLLER_BUTTON_A));
    dog.action       = (IsKeyPressed(SDL_SCANCODE_X)  || IsButtonPressed(SDL_CONTROLLER_BUTTON_X));

    // If the dog is dead respawn when a button is pressed or after some time.
    if (dog.dead)
    {
        dog.dead_timer -= dt;
        if (dog.jump_press || dog.action || dog.dead_timer <= 0.0f)
        {
            StartFade(FADE_SPECIAL, [](){ RespawnDog(gGameState.dog); });
        }
        return;
    }

    // Only if one direction is being pressed will we move the dog.
    if (dog.right != dog.left)
    {
        if (dog.right) { dog.vel.x =  DOG_MOVE_SPEED; dog.flip = FLIP_NONE; } // Move right.
        if (dog.left ) { dog.vel.x = -DOG_MOVE_SPEED; dog.flip = FLIP_HORZ; } // Move left.
    }
    if (!dog.left && !dog.right)
    {
        dog.vel.x = 0.0f;
    }

    // Apply a jump force if the key is presed.
    if (dog.grounded || dog.ledge_buffer > 0)
    {
        if (dog.jump_press)
        {
            dog.vel.y = (-DOG_JUMP_FORCE/2);
            dog.grounded = false;
            dog.ledge_buffer = 0;
            dog.jump_height = 0.18f;
            PlaySound(dog.snd_jump);
        }
    }

    if(dog.jump_release){
        dog.jump_height = 0;
    }

    // Apply a gravity force to the dog.
    if (!dog.grounded){
        if(dog.jump_height <= 0){
            dog.vel.y += DOG_WEIGHT * GRAVITY;
        }
        dog.ledge_buffer -= dt;
        dog.jump_height -= dt;
    }
    else{
        dog.vel.y = 0.0f;
        dog.ledge_buffer = 0.08f;
    }

    // Clamp the velocity in range.
    // if (dog.vel.y < -DOG_MAX_VEL) dog.vel.y = -DOG_MAX_VEL;
    // if (dog.vel.y >  DOG_MAX_VEL) dog.vel.y =  DOG_MAX_VEL;
    // if (dog.vel.x < -DOG_MAX_VEL) dog.vel.x = -DOG_MAX_VEL;
    // if (dog.vel.x >  DOG_MAX_VEL) dog.vel.x =  DOG_MAX_VEL;

    Vec2 test = dog.pos;
    Vec2 output = {0,0};

    // Perform simple tile collision on the dog to correct the player's position.
    // It works but its a pretty bad solution... it should cover all game scenarios.
    for (int iy=0; iy<gWorld.current_map.h; ++iy)
    {
        for (int ix=0; ix<gWorld.current_map.w; ++ix)
        {
            Tile* tile = &gWorld.current_map.tiles[iy*gWorld.current_map.w+ix];
            if (tile->type == TILE_SOLID)
            {
                //Testing X Posistion
                test.x = dog.pos.x + (dog.vel.x * dt);
                test.y = dog.pos.y;

                Rect intersection;
                if (TileEntityCollision(test,dog.bounds, ix,iy, intersection))
                {
                    if(dog.vel.x < 0){
                        dog.vel.x = 0;
                    }
                    if(dog.vel.x > 0){
                        //dog.pos.x -= intersection.w;
                        dog.vel.x = 0;
                    }
                }

                test.x = dog.pos.x;
                test.y = dog.pos.y + (dog.vel.y * dt);

                //Testing Y Posistion


                if (TileEntityCollision(test,dog.bounds, ix,iy, intersection))
                {
                    // Hit head!
                    if(dog.vel.y < 0){
                        //dog.pos.y += intersection.h;
                        CreateParticles(PARTICLE_TYPE_BASH, (int)dog.pos.x+12,(int)dog.pos.y+12,(int)dog.pos.x+12,(int)dog.pos.y+12, 4,8);
                        dog.vel.y = 0;
                        dog.jump_height = 0;
                        PlaySound(dog.snd_hithead);
                        //dog.grounded = true;
                    }
                    else{
                        //dog.pos.y -= intersection.h;
                        dog.vel.y = 0;
                    }
                }
            }
        }
    }

    // Check if the dog is grounded or not after correcting position.
    Vec2 tpos = dog.pos;
    tpos.y++;
    dog.grounded = false;
    for (int iy=0; iy<gWorld.current_map.h; ++iy)
    {
        for (int ix=0; ix<gWorld.current_map.w; ++ix)
        {
            Tile* tile = &gWorld.current_map.tiles[iy*gWorld.current_map.w+ix];
            if (tile->type == TILE_SOLID)
            {
                Rect intersection;
                if (TileEntityCollision(tpos,dog.bounds, ix,iy, intersection))
                {
                    if (dog.vel.y >= 0)
                    {
                        dog.grounded = true;
                    }
                }
            }
        }
    }

    // If the dog goes from still to moving on the ground create some dust puff particles.
    if (dog.grounded)
    {
        if (old_vel.x != dog.vel.x)
        {
            if (dog.vel.x < 0.0f) // Left!
            {
                CreateParticles(PARTICLE_TYPE_PUFF, (int)dog.pos.x+16,(int)dog.pos.y+18,(int)dog.pos.x+DOG_CLIP_W,(int)dog.pos.y+DOG_CLIP_H, 2,5);
                dog.footstep_timer = 0.2f;
            }
            else if (dog.vel.x > 0.0f) // Right!
            {
                CreateParticles(PARTICLE_TYPE_PUFF, (int)dog.pos.x,(int)dog.pos.y+18,(int)dog.pos.x+DOG_CLIP_W-16,(int)dog.pos.y+DOG_CLIP_H, 2,5);
                dog.footstep_timer = 0.2f;
            }
        }
    }

    // If the dog landed on the ground spawn some dust puff particles and play the landing sound.
    if ((old_grounded != dog.grounded) && (dog.grounded))
    {
        CreateParticles(PARTICLE_TYPE_PUFF, (int)dog.pos.x+4,(int)dog.pos.y+18,(int)dog.pos.x+DOG_CLIP_W-4,(int)dog.pos.y+DOG_CLIP_H, 2,5);
        PlaySound(dog.snd_land);
    }

    // Apply velocity to the dog.
    dog.pos.x += (dog.vel.x * dt);
    dog.pos.y += (dog.vel.y * dt);

    // Handle setting the dog's current animation state.
    if (!dog.grounded)
    {
        if (dog.vel.y <= 0.0f)
        {
            dog.state = DOG_STATE_JUMP;
        }
        else
        {
            dog.state = DOG_STATE_FALL;
        }
    }
    else
    {
        if (dog.vel.x != 0.0f)
        {
            dog.state = DOG_STATE_MOVE;
        }
        else
        {
            if (dog.state != DOG_STATE_BARK)
            {
            	if(!dog.up && !dog.right && !dog.left && !dog.down){
	                if (dog.action)
	                {
	                    ResetAnimation(dog.anim[DOG_STATE_BARK]);
	                    dog.state = DOG_STATE_BARK;
	                    PlaySound(dog.snd_bark);
	                }
	            }
            }

            if (dog.state == DOG_STATE_BARK || dog.state == DOG_STATE_BLNK)
            {
                if (IsAnimationDone(dog.anim[dog.state]))
                {
                    dog.state = DOG_STATE_IDLE;
                }
            }
            else
            {
                dog.state = DOG_STATE_IDLE;
                if (RandomRange(0, 1000) <= 10)
                {
                    ResetAnimation(dog.anim[DOG_STATE_BLNK]);
                    dog.state = DOG_STATE_BLNK;
                }
            }
        }
    }

    // Play the footstep sound periodically whilst moving.
    if (dog.grounded && dog.state == DOG_STATE_MOVE)
    {
        dog.footstep_timer += dt;
        if (dog.footstep_timer >= 0.2f)
        {
            PlaySound(dog.snd_footstep);
            dog.footstep_timer -= 0.2f;
        }
    }

    // The camera tracks the dogs current position!
    float cx = roundf(dog.pos.x + (DOG_CLIP_W/2) - (WINDOW_SCREEN_W/2));
    float cy = roundf(dog.pos.y + (DOG_CLIP_H/2) - (WINDOW_SCREEN_H/2));

    SetCameraTarget(cx,cy);

    // Check dog collision with entities and perform the appropriate actions!

    for (auto& spike: gWorld.current_map.spikes)
    {
        if (DogCollideWithEntity(dog, spike.x, spike.y, spike.bounds))
        {
            PlaySound(dog.snd_explode0);
            KillDog(dog);
            CreateParticles(PARTICLE_TYPE_EXPLODE1, (int)dog.pos.x-16,(int)dog.pos.y-16,(int)dog.pos.x+DOG_CLIP_W+16,(int)dog.pos.y+DOG_CLIP_H+16, 4,8);
            CreateParticles(PARTICLE_TYPE_SMOKE, (int)dog.pos.x,(int)dog.pos.y,(int)dog.pos.x+DOG_CLIP_W,(int)dog.pos.y+DOG_CLIP_H, 4,8);
        }
    }
    for (auto& sbone: gWorld.current_map.sbones)
    {
        if (!sbone.dead)
        {
            if (DogCollideWithEntity(dog, sbone.x, sbone.y, sbone.bounds))
            {
                CreateParticles(PARTICLE_TYPE_SBONE, (int)sbone.x+8,(int)sbone.y+8,(int)sbone.x+8,(int)sbone.y+8, 1);
                gTempBoneCollectedIds.push_back(sbone.id);
                sbone.dead = true;
                PlaySound(small_bone_sound);
            }
        }
    }
    for (auto& lbone: gWorld.current_map.lbones)
    {
        if (!lbone.dead)
        {
            if (DogCollideWithEntity(dog, lbone.x, lbone.y, lbone.bounds))
            {
                CreateParticles(PARTICLE_TYPE_SPEC, (int)lbone.x+12,(int)lbone.y+12,(int)lbone.x+12,(int)lbone.y+12, 40,72, 1.5f);
                gTempBoneCollectedIds.push_back(lbone.id);
                lbone.dead = true;
                PlaySound(small_bone_sound);
                PlaySound(big_bone_sound);
            }
        }
    }
    for (auto& bblocks: gWorld.current_map.bblocks)
    {
    	if(!bblocks.dead){
    		BreakbleBlockCollision(dog.bounds, bblocks);
    	}
    }
}

INTERNAL void DrawDog (Dog& dog, float dt)
{
    if (dog.dead) return;

    UpdateAnimation(dog.anim[dog.state], dt);

    SDL_Rect clip = { 0,0,DOG_CLIP_W,DOG_CLIP_H };
    DrawImage(dog.image, dog.pos.x, dog.pos.y, dog.flip, GetAnimationClip(dog.anim[dog.state]));
}

INTERNAL void KillDog (Dog& dog)
{
    dog.dead_timer = DOG_DEAD_TIME;
    dog.dead = true;
}

INTERNAL void RespawnDog (Dog& dog)
{
    dog.dead     = false;
    dog.state    = dog.start_state;
    dog.pos      = dog.start_pos;
    dog.vel      = dog.start_vel;
    dog.flip     = dog.start_flip;
    dog.grounded = dog.start_grounded;
    // Update camera.
    float cx = roundf(dog.pos.x + (DOG_CLIP_W/2) - (WINDOW_SCREEN_W/2));
    float cy = roundf(dog.pos.y + (DOG_CLIP_H/2) - (WINDOW_SCREEN_H/2));
    SetCamera(cx,cy);
    // Clear particles.
    ClearParticles();
    // Respawn bones.
    RespawnMapBones();
}

INTERNAL void DeleteDog (Dog& dog)
{
    FreeImage(dog.image);

    FreeSound(dog.snd_footstep);
    FreeSound(dog.snd_land);
    FreeSound(dog.snd_hithead);
    FreeSound(dog.snd_jump);
    FreeSound(dog.snd_bark);
    FreeSound(dog.snd_explode0);
    FreeSound(dog.snd_explode1);
}

INTERNAL bool DogCollideWithEntity (Dog& dog, float ex, float ey, Rect ebounds)
{
    Rect a,b;

    a.x = dog.pos.x + dog.bounds.x;
    a.y = dog.pos.y + dog.bounds.y;
    a.w =             dog.bounds.w;
    a.h =             dog.bounds.h;
    b.x = ex        +    ebounds.x;
    b.y = ey        +    ebounds.y;
    b.w =                ebounds.w;
    b.h =                ebounds.h;

    return ((a.x + a.w > b.x) && (a.y + a.h > b.y) &&
            (a.x < b.x + b.w) && (a.y < b.y + b.h));
}
