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

INTERNAL float GetTextLineWidth (Font& font, std::string text, int line)
{
    float linewidth = 0;
    int lineindex = 0;
    for (int i=0; i<text.length(); ++i)
    {
        if (text[i] == '\n')
        {
            if (lineindex++ == line) return linewidth;
            else linewidth = 0;
        }
        else
        {
            linewidth += font.charw;
        }
    }
    return linewidth;
}

INTERNAL float GetTextWidth (Font& font, std::string text)
{
    float linewidth = 0;
    float width = 0;
    for (int i=0; i<text.length(); ++i)
    {
        if (text[i] == '\n')
        {
            width = std::max(width, linewidth);
            linewidth = 0;
        }
        else
        {
            linewidth += font.charw;
        }
    }
    return std::max(width, linewidth);
}

INTERNAL float GetTextHeight (Font& font, std::string text)
{
    float height = font.charh;
    for (int i=0; i<text.length(); ++i)
    {
        if (text[i] == '\n')
        {
            height += font.charh;
        }
    }
    return height;
}
