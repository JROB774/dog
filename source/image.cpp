INTERNAL void LoadImage (Image& image, std::string file_name)
{
    file_name = "assets/" + file_name;
    SDL_Surface* surface = SDL_LoadBMP(file_name.c_str());
    if (!surface)
    {
        LOG_ERROR(ERR_MAX, "Failed to load image file '%s'! (%s)", file_name.c_str(), SDL_GetError());
        return;
    }

    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0x00,0x7F,0x7F));

    image.texture = SDL_CreateTextureFromSurface(gWindow.renderer, surface);
    if (!image.texture)
    {
        LOG_ERROR(ERR_MAX, "Failed to create texture '%s'! (%s)", file_name.c_str(), SDL_GetError());
        return;
    }

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
