GLOBAL constexpr int MIXER_FREQUENCY     = MIX_DEFAULT_FREQUENCY;
GLOBAL constexpr U16 MIXER_SAMPLE_FORMAT = MIX_DEFAULT_FORMAT;
GLOBAL constexpr int MIXER_CHANNELS      = 2; // Stereo Sound
GLOBAL constexpr int MIXER_SAMPLE_SIZE   = 2048;

INTERNAL bool InitMixer ()
{
    if (Mix_OpenAudio(MIXER_FREQUENCY, MIXER_SAMPLE_FORMAT, MIXER_CHANNELS, MIXER_SAMPLE_SIZE) != 0)
    {
        LOG_ERROR(ERR_MAX, "Failed to initialize audio mixer! (%s)", Mix_GetError());
        return false;
    }

    return true;
}

INTERNAL void QuitMixer ()
{
    Mix_CloseAudio();
}

INTERNAL void LoadSound (Sound& sound, std::string file_name)
{
    file_name = "assets/sounds/" + file_name;
    sound.data = Mix_LoadWAV(file_name.c_str());
    if (!sound.data)
    {
        LOG_ERROR(ERR_MAX, "Failed to load sound '%s'! (%s)", file_name.c_str(), Mix_GetError());
    }
}

INTERNAL void FreeSound (Sound& sound)
{
    Mix_FreeChunk(sound.data);
    sound.data = NULL;
}

INTERNAL void PlaySound (Sound& sound, int loops)
{
    if (Mix_PlayChannel(-1, sound.data, loops) == -1)
    {
        LOG_ERROR(ERR_MIN, "Failed to play sound effect! (%s)", Mix_GetError());
    }
}
