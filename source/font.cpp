GLOBAL constexpr int FONT_ROW_COUNT = 3;
GLOBAL constexpr int FONT_COL_COUNT = 32;

INTERNAL void LoadFont (Font& font, float cw, float ch, std::string file_name)
{
    LoadImage(font.image, file_name);

    for(int iy = 0; iy < FONT_ROW_COUNT; iy++){
        for(int ix = 0; ix < FONT_COL_COUNT; ix++){
            font.bounds[ix + (iy * FONT_COL_COUNT)] = {ix * (int)cw, iy * (int)ch, (int)cw, (int)ch};
        }
    }

    font.charw = cw;
    font.charh = ch;
}

INTERNAL void FreeFont (Font& font)
{
    FreeImage(font.image);
}
