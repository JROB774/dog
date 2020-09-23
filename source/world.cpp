// CSV parsing taken from here <https://stackoverflow.com/a/30338543>
INTERNAL void LoadWorld ()
{
    enum class CSVState { UnquotedField, QuotedField, QuotedQuote };

    std::ifstream csv("assets/world.csv");
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

    LoadMap(gWorld.current_map, START_MAP);

    // Find the location of the start room on the map.
    int cx = 0, cy = 0;
    bool done = false;
    for (auto& row: gWorld.rooms)
    {
        for (auto& col: row)
        {
            if (col == START_MAP)
            {
                gWorld.current_map_x = cx;
                gWorld.current_map_y = cy;
                done = true;
                break;
            }
            cx++;
        }
        if (done) break;
        cy++;
    }

    // printf("World: %s (%d %d)\n", START_MAP, gWorld.current_map_x, gWorld.current_map_y);
}

INTERNAL void FreeWorld ()
{
    gWorld.rooms.clear();
    FreeMap(gWorld.current_map);
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

    FreeMap(gWorld.current_map);
    LoadMap(gWorld.current_map, new_map);

    if (left)  gGameState.dog.pos.x = (float)((gWorld.current_map.w * TILE_W) - (pw));
    if (up)    gGameState.dog.pos.y = (float)((gWorld.current_map.h * TILE_H) - (ph));
    if (right) gGameState.dog.pos.x = (float)(0);
    if (down)  gGameState.dog.pos.y = (float)(0);

    // Find the location of the start room on the map.
    int cx = 0, cy = 0;
    bool done = false;
    for (auto& row: gWorld.rooms)
    {
        for (auto& col: row)
        {
            if (col == new_map)
            {
                gWorld.current_map_x = cx;
                gWorld.current_map_y = cy;
                done = true;
                break;
            }
            cx++;
        }
        if (done) break;
        cy++;
    }

    // printf("World: %s (%d %d)\n", new_map.c_str(), gWorld.current_map_x, gWorld.current_map_y);
}
