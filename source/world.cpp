// CSV parsing taken from here <https://stackoverflow.com/a/30338543>
INTERNAL void LoadWorld (std::string start_map)
{
    enum class CSVState { UnquotedField, QuotedField, QuotedQuote };

    std::ifstream csv("assets/maps/world.csv");
    if (!csv.is_open())
    {
        LOG_ERROR(ERR_MAX, "Failed to load world!");
        return;
    }

    while (!csv.eof())
    {
        std::string row;

        std::getline(csv, row);
        if (csv.bad() || csv.fail()) break;

        CSVState state = CSVState::UnquotedField;
        std::vector<std::string> fields { "" };

        size_t i = 0; // Index of the current field.

        for (char c: row)
        {
            switch (state)
            {
                case (CSVState::UnquotedField):
                {
                    switch (c)
                    {
                        case (','): fields.push_back(""); i++;     break; // End of field.
                        case ('"'): state = CSVState::QuotedField; break;
                        default   : fields[i].push_back(c);        break;
                    }
                } break;
                case (CSVState::QuotedField):
                {
                    switch (c)
                    {
                        case ('"'): state = CSVState::QuotedQuote; break;
                        default   : fields[i].push_back(c);        break;
                    }
                } break;
                case (CSVState::QuotedQuote):
                {
                    switch (c)
                    {
                        case (','): fields.push_back(""); i++; state = CSVState::UnquotedField; break; // After closing quote.
                        case ('"'): fields[i].push_back('"'); state = CSVState::QuotedField;    break; // "" -> "
                        default   : state = CSVState::UnquotedField;                            break;  // End of quote.
                    }
                } break;
            }
        }

        gWorld.rooms.push_back(fields);
    }

    csv.close();

    /////////////////////////////////////////////////

    gWorld.current_map_name = start_map;
    LoadMap(gWorld.current_map, start_map);

    // Find the location of the start room on the map.
    bool done = false;
    for (int ry=0; ry<gWorld.rooms.size(); ++ry)
    {
        for (int rx=0; rx<gWorld.rooms[ry].size(); ++rx)
        {
            if (gWorld.rooms[ry][rx] == start_map)
            {
                gWorld.current_map_x = rx;
                gWorld.current_map_y = ry;
                done = true;
                break;
            }
        }
        if (done) break;
    }

    // Extract the current zone.
    {
        auto tokens = TokenizeString(start_map, '-');
        ASSERT(tokens.size() == 3); // Tileset-Zone-Map
        gWorld.current_zone = tokens[0];
    }

    // Load all the bones in the current zone for the counter.
    gCurrentZoneBoneTotal = 0;
    std::vector<std::string> rooms_done;
    Map temp_room_map;
    for (int ry=0; ry<gWorld.rooms.size(); ++ry)
    {
        for (int rx=0; rx<gWorld.rooms[ry].size(); ++rx)
        {
            std::string room = gWorld.rooms[ry][rx];
            if (!room.empty())
            {
                auto tokens = TokenizeString(room, '-');
                ASSERT(tokens.size() == 3); // Tileset-Zone-Map
                if (tokens[0] == gWorld.current_zone)
                {
                    if (std::find(rooms_done.begin(), rooms_done.end(), room) == rooms_done.end())
                    {
                        LoadMap(temp_room_map, room);
                        gCurrentZoneBoneTotal += (int)temp_room_map.sbones.size();
                        // gCurrentZoneBoneTotal += (int)temp_room_map.lbones.size() * LARGE_BONE_WORTH;
                        FreeMap(temp_room_map);
                        rooms_done.push_back(room);
                    }
                }
            }
        }
    }

    // printf("World: %s (%d %d)\n", start_map, gWorld.current_map_x, gWorld.current_map_y);

    /////////////////////////////////////////////////

    // Move the camera to the dog's new position in the world.
    float cx = roundf(gGameState.dog.pos.x + (DOG_CLIP_W/2) - (WINDOW_SCREEN_W/2));
    float cy = roundf(gGameState.dog.pos.y + (DOG_CLIP_H/2) - (WINDOW_SCREEN_H/2));
    SetCamera(cx,cy);
}

INTERNAL void FreeWorld ()
{
    ClearParticles();
    gWorld.rooms.clear();
    FreeMap(gWorld.current_map);
    gWorld.current_map_name.clear();
    gWorld.current_zone.clear();
}

INTERNAL void WorldTransitionIfOutOfBounds ()
{
    int px = (int)gGameState.dog.pos.x;
    int py = (int)gGameState.dog.pos.y;
    int pw = DOG_CLIP_W;
    int ph = DOG_CLIP_H;

    int wx = gWorld.current_map_x;
    int wy = gWorld.current_map_y;

    bool need_to_transition = false;

    if (px + (pw/2) < 0)                             need_to_transition = true;
    if (py + (ph/2) < 0)                             need_to_transition = true;
    if (px + (pw/2) > gWorld.current_map.w * TILE_W) need_to_transition = true;
    if (py + (ph/2) > gWorld.current_map.h * TILE_H) need_to_transition = true;

    if (!need_to_transition) return;

    // Cache the collected bones.
    CacheMapBones();

    // Rooms aren't all single screen so add the player's offset to get the correct room grid-space.
    if (px > WINDOW_SCREEN_W) wx += (int)floor(px / WINDOW_SCREEN_W);
    if (py > WINDOW_SCREEN_H) wy += (int)floor(py / WINDOW_SCREEN_H);

    // Perform the actual transition.
    bool left  = false;
    bool up    = false;
    bool right = false;
    bool down  = false;

    if (px + (pw/2) < 0)                             { wx--; left  = true; }
    if (py + (ph/2) < 0)                             { wy--; up    = true; }
    if (px + (pw/2) > gWorld.current_map.w * TILE_W) { wx++; right = true; }
    if (py + (ph/2) > gWorld.current_map.h * TILE_H) { wy++; down  = true; }

    std::string new_map = gWorld.rooms[wy][wx];
    std::string new_zone = TokenizeString(new_map, '-')[0];;

    // Perform the appropriate fade out when transitioninig.
    if (new_zone != gWorld.current_zone)
    {
        gWorld.current_zone = new_zone; // We need to set this so we won't trigger this if again on the fade callback.
        FadeType   fade_type = FADE_NONE;
        if (up   ) fade_type = FADE_UP;
        if (right) fade_type = FADE_RIGHT;
        if (down ) fade_type = FADE_DOWN;
        if (left ) fade_type = FADE_LEFT;
        StartFade(fade_type, [](){ WorldTransitionIfOutOfBounds(); });
        return;
    }

    gWorld.current_map_name = new_map;

    FreeMap(gWorld.current_map);
    LoadMap(gWorld.current_map, new_map);

    // Find the location of the start room on the map.
    bool done = false;
    for (int ry=0; ry<gWorld.rooms.size(); ++ry)
    {
        for (int rx=0; rx<gWorld.rooms[ry].size(); ++rx)
        {
            if (gWorld.rooms[ry][rx] == new_map)
            {
                gWorld.current_map_x = rx;
                gWorld.current_map_y = ry;
                done = true;
                break;
            }
        }
        if (done) break;
    }

    // printf("World: %s (%d %d)\n", new_map.c_str(), gWorld.current_map_x, gWorld.current_map_y);

    // Calculate the player's new position relative to the new room.
    if (left)
    {
        px = ((gWorld.current_map.w * TILE_W) - (pw));
        py = (py % WINDOW_SCREEN_H) + ((wy-gWorld.current_map_y) * WINDOW_SCREEN_H);
    }
    if (up)
    {
        px = (px % WINDOW_SCREEN_W) + ((wx-gWorld.current_map_x) * WINDOW_SCREEN_W);
        py = ((gWorld.current_map.h * TILE_H) - (ph));
    }
    if (right)
    {
        px = 0;
        py = (py % WINDOW_SCREEN_H) + ((wy-gWorld.current_map_y) * WINDOW_SCREEN_H);
    }
    if (down)
    {
        px = (px % WINDOW_SCREEN_W) + ((wx-gWorld.current_map_x) * WINDOW_SCREEN_W);
        py = 0;
    }

    // Apply some extra upward velocity so the player can go upwsrd nicely.
    if (up) gGameState.dog.vel.y -= (DOG_JUMP_FORCE / 2);

    gGameState.dog.pos = { (float)px, (float)py };

    gGameState.dog.start_state    = gGameState.dog.state;
    gGameState.dog.start_pos      = gGameState.dog.pos;
    gGameState.dog.start_vel      = gGameState.dog.vel;
    gGameState.dog.start_flip     = gGameState.dog.flip;
    gGameState.dog.start_grounded = gGameState.dog.grounded;

    // Clear the current particles when we go to a new map.
    ClearParticles();

    // Auto-save game data whenever there's a room transition.
    SaveData();

    // Move the camera to the dog's new position in the world.
    float cx = roundf(gGameState.dog.pos.x + (DOG_CLIP_W/2) - (WINDOW_SCREEN_W/2));
    float cy = roundf(gGameState.dog.pos.y + (DOG_CLIP_H/2) - (WINDOW_SCREEN_H/2));
    SetCamera(cx,cy);
}
