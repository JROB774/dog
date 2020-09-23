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

INTERNAL void CreateDog (Dog& dog, float x, float y)
{
    dog.state = DOG_STATE_IDLE;

    dog.pos = { x, y };
    dog.vel = { 0, 0 };

    dog.bounds = { DOG_BOUNDS_X,DOG_BOUNDS_Y,DOG_BOUNDS_W,DOG_BOUNDS_H };

    LoadImage(dog.image, "dog.bmp");
    dog.flip = FLIP_NONE;

    LoadAnimation(dog.anim[DOG_STATE_IDLE], "dog-idle.anim");
    LoadAnimation(dog.anim[DOG_STATE_BLNK], "dog-blnk.anim");
    LoadAnimation(dog.anim[DOG_STATE_MOVE], "dog-move.anim");
    LoadAnimation(dog.anim[DOG_STATE_JUMP], "dog-jump.anim");
    LoadAnimation(dog.anim[DOG_STATE_FALL], "dog-fall.anim");
    LoadAnimation(dog.anim[DOG_STATE_BARK], "dog-bark.anim");

    dog.left = false;
    dog.right = false;

    dog.grounded = false;
}

INTERNAL void UpdateDog (Dog& dog, float dt)
{
    dog.right = (IsKeyDown(SDL_SCANCODE_RIGHT) || IsKeyDown(SDL_SCANCODE_D));
    dog.left  = (IsKeyDown(SDL_SCANCODE_LEFT)  || IsKeyDown(SDL_SCANCODE_A));

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
        if (IsKeyPressed(SDL_SCANCODE_Z) || IsKeyPressed(SDL_SCANCODE_SPACE))
        {
            dog.vel.y = -DOG_JUMP_FORCE;
            dog.grounded = false;
            dog.ledge_buffer = 0;
        }
    }

    // Apply a gravity force to the dog.
    if (!dog.grounded){
        dog.vel.y += DOG_WEIGHT * GRAVITY;
        dog.ledge_buffer -= dt;
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
    for (int iy=0; iy<gGameState.map.h; ++iy)
    {
        for (int ix=0; ix<gGameState.map.w; ++ix)
        {
            Tile* tile = &gGameState.map.tiles[iy*gGameState.map.w+ix];
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
                    if(dog.vel.y < 0){
                        //dog.pos.y += intersection.h;
                        dog.vel.y = 0;
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
    for (int iy=0; iy<gGameState.map.h; ++iy)
    {
        for (int ix=0; ix<gGameState.map.w; ++ix)
        {
            Tile* tile = &gGameState.map.tiles[iy*gGameState.map.w+ix];
            if (tile->type == TILE_SOLID)
            {
                Rect intersection;
                if (TileEntityCollision(tpos,dog.bounds, ix,iy, intersection))
                {
                    if (dog.vel.y >= 0) dog.grounded = true;
                }
            }
        }
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
                if (IsKeyPressed(SDL_SCANCODE_X))
                {
                    ResetAnimation(dog.anim[DOG_STATE_BARK]);
                    dog.state = DOG_STATE_BARK;
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
}

INTERNAL void DrawDog (Dog& dog, float dt)
{
    UpdateAnimation(dog.anim[dog.state], dt);

    SDL_Rect clip = { 0,0,DOG_CLIP_W,DOG_CLIP_H };
    DrawImage(dog.image, dog.pos.x, dog.pos.y, dog.flip, GetAnimationClip(dog.anim[dog.state]));
}
