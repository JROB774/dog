#ifndef MIXER_HPP
#define MIXER_HPP

struct Sound
{
    Mix_Chunk* data;
};

INTERNAL bool InitMixer ();
INTERNAL void QuitMixer ();

INTERNAL void LoadSound (Sound& sound, std::string file_name);
INTERNAL void FreeSound (Sound& sound);
INTERNAL void PlaySound (Sound& sound, int loops = 0);

INTERNAL void SetSound  (bool enable);
INTERNAL bool IsSoundOn ();

#endif /* MIXER_HPP */
