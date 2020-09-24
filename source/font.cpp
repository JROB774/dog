void InitFont()
{
    LoadImage(gfont.image, "font.bmp");

    for(int iy = 0; iy < gfont.row_amount; iy++){
        for(int ix = 0; ix < gfont.column_amount; ix++){
            gfont.bounds[ix + (iy * gfont.column_amount)] = {ix * gfont.base.w, iy * gfont.base.h, gfont.base.w, gfont.base.h};
        }
    }
}

void DrawFont(std::string text, float x, float y)
{
    for(int i = 0; i < text.length(); i++){
        DrawImage(gfont.image, x, y, FLIP_NONE, &gfont.bounds[static_cast<U8>(text.at(i))]);
        x += gfont.base.w;
    }
}

void QuitFont()
{
    FreeImage(gfont.image);
}
