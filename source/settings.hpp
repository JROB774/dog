#ifndef SETTINGS_HPP
#define SETTINGS_HPP

GLOBAL struct Settings
{
    int window_width;
    int window_height;
    bool fullscreen;
    float sound_volume;
    float music_volume;

} gSettings;

INTERNAL void  SaveSettings ();
INTERNAL void  LoadSettings ();
INTERNAL void ResetSettings ();

#endif /* SETTINGS_HPP */
