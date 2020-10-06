GLOBAL constexpr const char* SAVE_FILE = "save.data";

INTERNAL void SaveData ()
{
    /*
    FILE* save = fopen(SAVE_FILE, "w");
    if (!save) LOG_ERROR(ERR_MED, "Failed to save data!\n");
    else
    {
        fprintf(save, "player_state %d\n",     gGameState.dog.start_state                       );
        fprintf(save, "player_pos_x %f\n",     gGameState.dog.start_pos.x                       );
        fprintf(save, "player_pos_y %f\n",     gGameState.dog.start_pos.y                       );
        fprintf(save, "player_vel_x %f\n",     gGameState.dog.start_vel.x                       );
        fprintf(save, "player_vel_y %f\n",     gGameState.dog.start_vel.y                       );
        fprintf(save, "player_flip %d\n",      gGameState.dog.start_flip                        );
        fprintf(save, "player_deaths %d\n",    gGameState.dog.deaths                            );
        fprintf(save, "player_grounded %s\n", (gGameState.dog.start_grounded) ? "true" : "false");
        fprintf(save, "current_map \"%s\"\n",  gWorld.current_map_name.c_str()                  );

        fprintf(save, "bones [\n");
        for (auto& id: gBoneCollectedIds) fprintf(save, "    \"%s\"\n", id.c_str());
        fprintf(save, "]\n");

        fclose(save);
    }
    */
}

INTERNAL void LoadData ()
{
    /*
    if (IsThereSaveData())
    {
        GonObject save = GonObject::Load(SAVE_FILE);

        gGameState.dog.state    = (DogState)save["player_state"   ].Int   ();
        gGameState.dog.pos.x    = (float   )save["player_pos_x"   ].Number();
        gGameState.dog.pos.y    = (float   )save["player_pos_y"   ].Number();
        gGameState.dog.vel.x    = (float   )save["player_vel_x"   ].Number();
        gGameState.dog.vel.y    = (float   )save["player_vel_y"   ].Number();
        gGameState.dog.flip     = (Flip    )save["player_flip"    ].Int   ();
        gGameState.dog.deaths   =           save["player_deaths"  ].Int   ();
        gGameState.dog.grounded =           save["player_grounded"].Bool  ();

        gGameState.dog.start_state    = gGameState.dog.state;
        gGameState.dog.start_pos      = gGameState.dog.pos;
        gGameState.dog.start_vel      = gGameState.dog.vel;
        gGameState.dog.start_flip     = gGameState.dog.flip;
        gGameState.dog.start_grounded = gGameState.dog.grounded;

        FreeWorld();
        LoadWorld(save["current_map"].String());

        gBoneCollectedIds.clear();
        gTempBoneCollectedIds.clear();
        for (int i=0; i<save["bones"].Size(); ++i) {
            gBoneCollectedIds.push_back(save["bones"][i].String());
        }
    }
    */
}
