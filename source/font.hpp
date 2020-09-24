#ifndef FONT_H
#define FONT_H

GLOBAL struct Font
{
    Image image;

    SDL_Rect bounds[255];
    SDL_Rect base = {0,0,32,32};

    int row_amount = 10;
    int column_amount = 10;
} gfont;

void CreateFont();
void RenderFont(std::string text, float x, float y);
void DestroyFont();

#endif /* FONT_HPP */
