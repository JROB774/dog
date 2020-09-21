/*******************************************************************************
 *
 * This following section of code is based on the Simple-SDL2-Audio library,
 * with some modifications to better suit the purposes of this project. The
 * original library can be found at the following GitHub repository:
 *
 *    https://github.com/jakebesworth/Simple-SDL2-Audio
 *
 * Below is the original copyright notice and license for this C library.
 *
*******************************************************************************/

/*******************************************************************************
 *
 * Simple-SDL2-Audio
 *
 * Copyright 2016 Jake Besworth
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*******************************************************************************/

GLOBAL constexpr int AUDIO_FREQUENCY  = 48000;                      // Frequency of the file.
GLOBAL constexpr int AUDIO_FORMAT     = AUDIO_S16LSB;               // SDL_AudioFormat of files (S16 little-endian).
GLOBAL constexpr int AUDIO_CHANNELS   = 2;                          // 1 = mono, 2 = stereo, 4 = quad, 6 = 5.1
GLOBAL constexpr int AUDIO_SAMPLES    = 4096;                       // Specifies a unit of audio data to be used at a time. (MUST BE POWER OF 2)
GLOBAL constexpr int AUDIO_MAX_SOUNDS = 25;                         // Max number of sounds that can be in the audio queue at anytime, stops too much mixing.
GLOBAL constexpr U32 AUDIO_FLAGS      = SDL_AUDIO_ALLOW_ANY_CHANGE; // SDL defined flags that dicate what audio features the device can change.

struct Audio
{
    SDL_AudioSpec spec;
    Audio* next;

    U32 length;
    U32 length_true;
    U8* buffer;
    U8* buffer_true;
    int loop;
    int fade;
    int free;
    int volume;
};

GLOBAL struct AudioState
{
    SDL_AudioDeviceID device;
    SDL_AudioSpec spec;
    Audio* audio;
    bool enabled;
    int sound_count;

} gAudioState;

INTERNAL void AudioCallback (void* userdata, U8* stream, int length)
{
    // @Incomplete: ...
};

INTERNAL Audio* LoadAudio (const char* file_name, int loop, int volume)
{
    Audio* audio = (Audio*)calloc(1, sizeof(Audio));
    ASSERT(audio);

    audio->next   = NULL;
    audio->loop   = loop;
    audio->fade   = 0;
    audio->free   = 1;
    audio->volume = volume;

    SDL_LoadWAV(file_name, &(audio->spec), &(audio->buffer_true), &(audio->length_true));

    audio->buffer = audio->buffer_true;
    audio->length = audio->length_true;
    audio->spec.callback = NULL;
    audio->spec.userdata = NULL;

    return audio;
}

INTERNAL void FreeAudio (Audio* audio)
{
    Audio* temp;
    while (audio != NULL)
    {
        if (audio->free == 1) SDL_FreeWAV(audio->buffer_true);
        temp = audio;
        audio = audio->next;
        free(temp);
    }
}

INTERNAL void PlayAudio (Audio* audio, int loop, int volume)
{
    if (!gAudioState.enabled) return;

    // If it's a sound check if under max number of sounds allowed, otherwise don't play.
    if (loop == 0)
    {
        if (gAudioState.sound_count >= AUDIO_MAX_SOUNDS) return;
        else gAudioState.sound_count++;
    }

    Audio* new_audio = (Audio*)malloc(sizeof(Audio));
    ASSERT(new_audio);

    memcpy(new_audio, audio, sizeof(Audio));

    new_audio->volume = volume;
    new_audio->loop = loop;
    new_audio->free = 0;
}

INTERNAL bool InitAudio ()
{
    gAudioState.sound_count = 0;
    gAudioState.enabled = false;

    gAudioState.spec.freq      = AUDIO_FREQUENCY;
    gAudioState.spec.format    = AUDIO_FORMAT;
    gAudioState.spec.channels  = AUDIO_CHANNELS;
    gAudioState.spec.samples   = AUDIO_SAMPLES;
    gAudioState.spec.callback  = AudioCallback;
    gAudioState.spec.userdata  = calloc(1, sizeof(Audio));

    gAudioState.audio = (Audio*)gAudioState.spec.userdata;
    ASSERT(gAudioState.audio);

    gAudioState.audio->buffer = NULL;
    gAudioState.audio->next = NULL;

    gAudioState.device = SDL_OpenAudioDevice(NULL, 0, &gAudioState.spec, NULL, AUDIO_FLAGS);
    ASSERT(gAudioState.device);

    gAudioState.enabled = true;
    UnpauseAudio();

    return true;
}

INTERNAL void QuitAudio ()
{
    if (!gAudioState.enabled) return;

    PauseAudio();

    FreeAudio(gAudioState.audio);
    SDL_CloseAudioDevice(gAudioState.device);
}

INTERNAL void UnpauseAudio ()
{
    if (gAudioState.enabled) SDL_PauseAudioDevice(gAudioState.device, 0);
}

INTERNAL void PauseAudio ()
{
    if (gAudioState.enabled) SDL_PauseAudioDevice(gAudioState.device, 1);
}

INTERNAL void LoadSound (Sound& sound, const char* file_name, int volume)
{
    sound.audio = LoadAudio(file_name, 0, volume);
}

INTERNAL void FreeSound (Sound& sound)
{
    FreeAudio(sound.audio);
    sound.audio = NULL;
}

INTERNAL void PlaySound (Sound& sound, int volume)
{
    PlayAudio(sound.audio, 0, volume);
}

INTERNAL void LoadMusic (Music& music, const char* file_name, int volume)
{
    music.audio = LoadAudio(file_name, 1, volume);
}

INTERNAL void FreeMusic (Music& music)
{
    FreeAudio(music.audio);
    music.audio = NULL;
}

INTERNAL void PlayMusic (Music& music, int volume)
{
    PlayAudio(music.audio, 1, volume);
}
