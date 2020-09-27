GLOBAL constexpr const char* SETTINGS_FILE = "settings.data";

INTERNAL void SaveSettings ()
{
    FILE* settings = fopen(SETTINGS_FILE, "w");
    if (!settings) LOG_ERROR(ERR_MED, "Failed to save settings!\n");
    else
    {
        fprintf(settings, "window_width %d\n", GetWindowWidth());
        fprintf(settings, "window_height %d\n", GetWindowHeight());
        fprintf(settings, "fullscreen %s\n", (IsFullscreen()) ? "true" : "false");
        fprintf(settings, "sound %s\n", (IsSoundOn()) ? "true" : "false");
        fprintf(settings, "music %s\n", (IsMusicOn()) ? "true" : "false");
        fclose(settings);
    }
}

INTERNAL void LoadSettings ()
{
    if (std::filesystem::exists(SETTINGS_FILE))
    {
        GonObject settings = GonObject::Load(SETTINGS_FILE);
        gSettings.window_width = settings["window_width"].Int(640);
        gSettings.window_height = settings["window_height"].Int(480);
        gSettings.fullscreen = settings["fullscreen"].Bool(false);
        gSettings.sound = settings["sound"].Bool(true);
        gSettings.music = settings["music"].Bool(true);
    }
}

INTERNAL void ResetSettings ()
{
    SetWindowSize(640, 480);
    SetFullscreen(false);
    SetSound(true);
    SetMusic(true);
}
