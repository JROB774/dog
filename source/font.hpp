#ifndef FONT_HPP
#define FONT_HPP

GLOBAL constexpr int FONT_CHAR_COUNT = 256;

struct Font
{
    SDL_Rect bounds[FONT_CHAR_COUNT];
    Image image;
    float charw;
    float charh;
};

INTERNAL void LoadFont (Font& font, float cw, float ch, std::string file_name);
INTERNAL void FreeFont (Font& font);

#endif /* FONT_HPP */
