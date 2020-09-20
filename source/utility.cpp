INTERNAL SDL_Color ColorToSDLColor (Color color)
{
    SDL_Color c;
    c.r = (U8)(color.r * 255.0f);
    c.g = (U8)(color.g * 255.0f);
    c.b = (U8)(color.b * 255.0f);
    c.a = (U8)(color.a * 255.0f);
    return c;
}

INTERNAL Color MakeColor (float r, float g, float b, float a)
{
    return Color { r,g,b,a };
}
