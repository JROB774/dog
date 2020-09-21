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

#ifndef AUDIO_HPP
#define AUDIO_HPP

struct Audio;

struct Sound
{
    Audio* audio = NULL;
};
struct Music
{
    Audio* audio = NULL;
};

INTERNAL bool InitAudio    ();
INTERNAL void QuitAudio    ();
INTERNAL void UnpauseAudio ();
INTERNAL void PauseAudio   ();
INTERNAL void LoadSound    (Sound& sound, const char* file_name, int volume);
INTERNAL void FreeSound    (Sound& sound);
INTERNAL void PlaySound    (Sound& sound, int volume);
INTERNAL void LoadMusic    (Music& music, const char* file_name, int volume);
INTERNAL void FreeMusic    (Music& music);
INTERNAL void PlayMusic    (Music& music, int volume);

#endif /* AUDIO_HPP */
