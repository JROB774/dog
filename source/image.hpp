#ifndef IMAGE_HPP
#define IMAGE_HPP

struct Image
{
    SDL_Texture* texture;
    float w, h;
};

INTERNAL void LoadImage (Image& image, const char* file_name);
INTERNAL void FreeImage (Image& image);

#endif /* IMAGE_HPP */
