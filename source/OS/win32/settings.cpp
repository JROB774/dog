INTERNAL void SaveSettings ()
{
    FILE* settings = fopen(SETTINGS_FILE, "w");
    if (!settings) LOG_ERROR(ERR_MED, "Failed to save settings!\n");
    else
    {
        fprintf(settings, "window_width %d\n", GetWindowWidth());
        fprintf(settings, "window_height %d\n", GetWindowHeight());
        fprintf(settings, "fullscreen %s\n", (IsFullscreen()) ? "true" : "false");
        fprintf(settings, "sound_volume %f\n", GetSoundVolume());
        fprintf(settings, "music_volume %f\n", GetMusicVolume());
        fclose(settings);
    }
}

INTERNAL void LoadSettings ()
{
    GonObject settings = GonObject::Load(SETTINGS_FILE);
    gSettings.window_width = settings["window_width"].Int(SETTINGS_DEFAULT_WINDOW_WIDTH);
    gSettings.window_height = settings["window_height"].Int(SETTINGS_DEFAULT_WINDOW_HEIGHT);
    gSettings.fullscreen = settings["fullscreen"].Bool(SETTINGS_DEFAULT_FULLSCREEN);
    gSettings.sound_volume = (float)settings["sound_volume"].Number(SETTINGS_DEFAULT_SOUND_VOLUME);
    gSettings.music_volume = (float)settings["music_volume"].Number(SETTINGS_DEFAULT_MUSIC_VOLUME);
}

INTERNAL void ResetSettings ()
{
    SetWindowSize (SETTINGS_DEFAULT_WINDOW_WIDTH, SETTINGS_DEFAULT_WINDOW_HEIGHT);
    SetFullscreen (SETTINGS_DEFAULT_FULLSCREEN);
    SetSoundVolume(SETTINGS_DEFAULT_SOUND_VOLUME);
    SetMusicVolume(SETTINGS_DEFAULT_MUSIC_VOLUME);
}
