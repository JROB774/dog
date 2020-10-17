INTERNAL void SaveSettings ()
{
    // Nothing...
}

INTERNAL void LoadSettings ()
{
    gSettings.window_width  = SETTINGS_DEFAULT_WINDOW_WIDTH;
    gSettings.window_height = SETTINGS_DEFAULT_WINDOW_HEIGHT;
    gSettings.fullscreen    = SETTINGS_DEFAULT_FULLSCREEN;
    gSettings.sound_volume  = SETTINGS_DEFAULT_SOUND_VOLUME;
    gSettings.music_volume  = SETTINGS_DEFAULT_MUSIC_VOLUME;
}

INTERNAL void ResetSettings ()
{
    SetWindowSize (SETTINGS_DEFAULT_WINDOW_WIDTH, SETTINGS_DEFAULT_WINDOW_HEIGHT);
    SetFullscreen (SETTINGS_DEFAULT_FULLSCREEN);
    SetSoundVolume(SETTINGS_DEFAULT_SOUND_VOLUME);
    SetMusicVolume(SETTINGS_DEFAULT_MUSIC_VOLUME);
}
