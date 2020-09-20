#ifndef IMAGE_HPP
#define IMAGE_HPP

struct Image
{
    SDL_Texture* texture;
    float w, h;
    Color color; // Multiply color.
};

INTERNAL void LoadImage (Image& image, const char* file_name);
INTERNAL void FreeImage (Image& image);

#endif /* IMAGE_HPP */
