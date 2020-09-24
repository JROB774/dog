#ifndef FONT_HPP
#define FONT_HPP

GLOBAL constexpr int FONT_CHAR_COUNT = 256;

GLOBAL constexpr int FONT_CHAR_W = 24;
GLOBAL constexpr int FONT_CHAR_H = 24;

GLOBAL constexpr int FONT_ROW_COUNT = 3;
GLOBAL constexpr int FONT_COL_COUNT = 32;

GLOBAL struct Font
{
    Image image;

    SDL_Rect bounds[FONT_CHAR_COUNT];
    SDL_Rect base = {0,0,FONT_CHAR_W,FONT_CHAR_H};

    int row_amount = FONT_ROW_COUNT;
    int column_amount = FONT_COL_COUNT;
} gfont;

void CreateFont();
void RenderFont(std::string text, float x, float y);
void DestroyFont();

#endif /* FONT_HPP */
