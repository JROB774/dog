GLOBAL constexpr const char* SAVE_FILE = "save.data";

GLOBAL constexpr U16 COMPLETE_0_BIT = 0b0000000000000001;
GLOBAL constexpr U16 COMPLETE_1_BIT = 0b0000000000000010;
GLOBAL constexpr U16 COMPLETE_2_BIT = 0b0000000000000100;
GLOBAL constexpr U16 COMPLETE_3_BIT = 0b0000000000001000;
GLOBAL constexpr U16  COLLECT_0_BIT = 0b0000000000010000;
GLOBAL constexpr U16  COLLECT_1_BIT = 0b0000000000100000;
GLOBAL constexpr U16  COLLECT_2_BIT = 0b0000000001000000;
GLOBAL constexpr U16  COLLECT_3_BIT = 0b0000000010000000;
GLOBAL constexpr U16  IRONMAN_0_BIT = 0b0000000100000000;
GLOBAL constexpr U16  IRONMAN_1_BIT = 0b0000001000000000;
GLOBAL constexpr U16  IRONMAN_2_BIT = 0b0000010000000000;
GLOBAL constexpr U16  IRONMAN_3_BIT = 0b0000100000000000;
GLOBAL constexpr U16 SPEEDRUN_0_BIT = 0b0001000000000000;
GLOBAL constexpr U16 SPEEDRUN_1_BIT = 0b0010000000000000;
GLOBAL constexpr U16 SPEEDRUN_2_BIT = 0b0100000000000000;
GLOBAL constexpr U16 SPEEDRUN_3_BIT = 0b1000000000000000;

INTERNAL void SaveData ()
{
    // Pack the flags for each badge's completion status into a 16-bit value
    // where each bit's state corresponds to a particular badge's unlock.
    U16 save_data = 0x0000;

    save_data |= (gBadges.unlocked_complete[0]) ? COMPLETE_0_BIT : 0x0000;
    save_data |= (gBadges.unlocked_complete[1]) ? COMPLETE_1_BIT : 0x0000;
    save_data |= (gBadges.unlocked_complete[2]) ? COMPLETE_2_BIT : 0x0000;
    save_data |= (gBadges.unlocked_complete[3]) ? COMPLETE_3_BIT : 0x0000;
    save_data |= (gBadges.unlocked_collect [0]) ?  COLLECT_0_BIT : 0x0000;
    save_data |= (gBadges.unlocked_collect [1]) ?  COLLECT_1_BIT : 0x0000;
    save_data |= (gBadges.unlocked_collect [2]) ?  COLLECT_2_BIT : 0x0000;
    save_data |= (gBadges.unlocked_collect [3]) ?  COLLECT_3_BIT : 0x0000;
    save_data |= (gBadges.unlocked_ironman [0]) ?  IRONMAN_0_BIT : 0x0000;
    save_data |= (gBadges.unlocked_ironman [1]) ?  IRONMAN_1_BIT : 0x0000;
    save_data |= (gBadges.unlocked_ironman [2]) ?  IRONMAN_2_BIT : 0x0000;
    save_data |= (gBadges.unlocked_ironman [3]) ?  IRONMAN_3_BIT : 0x0000;
    save_data |= (gBadges.unlocked_speedrun[0]) ? SPEEDRUN_0_BIT : 0x0000;
    save_data |= (gBadges.unlocked_speedrun[1]) ? SPEEDRUN_1_BIT : 0x0000;
    save_data |= (gBadges.unlocked_speedrun[2]) ? SPEEDRUN_2_BIT : 0x0000;
    save_data |= (gBadges.unlocked_speedrun[3]) ? SPEEDRUN_3_BIT : 0x0000;

    FILE* file = fopen(SAVE_FILE, "wb");
    if (!file) { LOG_ERROR(ERR_MED, "Failed to save game data!\n"); return; }
    fwrite(&save_data, sizeof(save_data), 1, file);
    fclose(file);
}

INTERNAL void LoadData ()
{
    if (!std::filesystem::exists(SAVE_FILE)) return; // Don't attempt to load if we don't have save data.

    // Unpack the flags for each badge's completion status from a 16-bit value
    // where each bit's state corresponds to a particular badge's unlock.
    U16 save_data = 0x0000;

    FILE* file = fopen(SAVE_FILE, "rb");
    if (!file) { LOG_ERROR(ERR_MED, "Failed to load save data!\n"); return; }
    fread(&save_data, sizeof(save_data), 1, file);
    fclose(file);

    gBadges.unlocked_complete[0] = (save_data & COMPLETE_0_BIT) >>  0;
    gBadges.unlocked_complete[1] = (save_data & COMPLETE_1_BIT) >>  1;
    gBadges.unlocked_complete[2] = (save_data & COMPLETE_2_BIT) >>  2;
    gBadges.unlocked_complete[3] = (save_data & COMPLETE_3_BIT) >>  3;
    gBadges.unlocked_collect [0] = (save_data &  COLLECT_0_BIT) >>  4;
    gBadges.unlocked_collect [1] = (save_data &  COLLECT_1_BIT) >>  5;
    gBadges.unlocked_collect [2] = (save_data &  COLLECT_2_BIT) >>  6;
    gBadges.unlocked_collect [3] = (save_data &  COLLECT_3_BIT) >>  7;
    gBadges.unlocked_ironman [0] = (save_data &  IRONMAN_0_BIT) >>  8;
    gBadges.unlocked_ironman [1] = (save_data &  IRONMAN_1_BIT) >>  9;
    gBadges.unlocked_ironman [2] = (save_data &  IRONMAN_2_BIT) >> 10;
    gBadges.unlocked_ironman [3] = (save_data &  IRONMAN_3_BIT) >> 11;
    gBadges.unlocked_speedrun[0] = (save_data & SPEEDRUN_0_BIT) >> 12;
    gBadges.unlocked_speedrun[1] = (save_data & SPEEDRUN_1_BIT) >> 13;
    gBadges.unlocked_speedrun[2] = (save_data & SPEEDRUN_2_BIT) >> 14;
    gBadges.unlocked_speedrun[3] = (save_data & SPEEDRUN_3_BIT) >> 15;
}
