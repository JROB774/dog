INTERNAL void LoadImage (Image& image, const char* file_name)
{
    SDL_Surface* surface = SDL_LoadBMP(file_name);
    ASSERT(surface);
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0x80,0x80,0x80));

    image.texture = SDL_CreateTextureFromSurface(gWindow.renderer, surface);
    ASSERT(image.texture);

    image.w = (float)surface->w;
    image.h = (float)surface->h;

    image.color = MakeColor(1,1,1,1);

    SDL_FreeSurface(surface);
}

INTERNAL void FreeImage (Image& image)
{
    SDL_DestroyTexture(image.texture);
    image.texture = NULL;
    image.w = 0.0f, image.h = 0.0f;
}
