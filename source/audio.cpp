GLOBAL constexpr int AUDIO_FORMAT     = AUDIO_S16LSB;               // SDL_AudioFormat of files (S16 little-endian).
GLOBAL constexpr int AUDIO_FREQUENCY  = 48000;                      // Frequency of the file.
GLOBAL constexpr int AUDIO_CHANNELS   = 2;                          // 1 = mono, 2 = stereo, 4 = quad, 6 = 5.1
GLOBAL constexpr int AUDIO_SAMPLES    = 4096;                       // Specifies a unit of audio data to be used at a time. (MUST BE POWER OF 2)
GLOBAL constexpr int AUDIO_MAX_SOUNDS = 25;                         // Max number of sounds that can be in the audio queue at anytime, stops too much mixing.
GLOBAL constexpr U32 AUDIO_FLAGS      = SDL_AUDIO_ALLOW_ANY_CHANGE; // SDL defined flags that dicate what audio features the device can change.

INTERNAL void LoadAudio (Audio& audio, int volume, const char* file_name)
{
    // @Incomplete: ...
}

INTERNAL void FreeAudio (Audio& audio)
{
    // @Incomplete: ...
}
