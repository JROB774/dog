GLOBAL Vec2 gRenderOffset = { 0,0 };

INTERNAL void DrawPoint (float x, float y, Color color)
{
    SDL_Color c = ColorToSDLColor(color);
    SDL_SetRenderDrawColor(gWindow.renderer, c.r,c.g,c.b,c.a);
    x -= gRenderOffset.x;
    y -= gRenderOffset.y;
    SDL_RenderDrawPointF(gWindow.renderer, x,y);
}

INTERNAL void DrawLine (float x1, float y1, float x2, float y2, Color color)
{
    SDL_Color c = ColorToSDLColor(color);
    SDL_SetRenderDrawColor(gWindow.renderer, c.r,c.g,c.b,c.a);
    x1 -= gRenderOffset.x;
    y1 -= gRenderOffset.y;
    x2 -= gRenderOffset.x;
    y2 -= gRenderOffset.y;
    SDL_RenderDrawLineF(gWindow.renderer, x1,y1,x2,y2);
}

INTERNAL void DrawRect (float x, float y, float w, float h, Color color)
{
    SDL_Color c = ColorToSDLColor(color);
    SDL_SetRenderDrawColor(gWindow.renderer, c.r,c.g,c.b,c.a);
    SDL_FRect rect = { x-gRenderOffset.x,y-gRenderOffset.y,w,h };
    SDL_RenderDrawRectF(gWindow.renderer, &rect);
}

INTERNAL void DrawFill (float x, float y, float w, float h, Color color)
{
    SDL_Color c = ColorToSDLColor(color);
    SDL_SetRenderDrawColor(gWindow.renderer, c.r,c.g,c.b,c.a);
    SDL_FRect rect = { x-gRenderOffset.x,y-gRenderOffset.y,w,h };
    SDL_RenderFillRectF(gWindow.renderer, &rect);
}

INTERNAL void DrawRect (Rect rect, Color color)
{
    DrawRect(rect.x, rect.y, rect.w, rect.h, color);
}

INTERNAL void DrawFill (Rect rect, Color color)
{
    DrawFill(rect.x, rect.y, rect.w, rect.h, color);
}

INTERNAL void DrawImage (Image& image, float x, float y, Flip flip, const SDL_Rect* clip)
{
    SDL_Color c = ColorToSDLColor(image.color);
    SDL_SetTextureColorMod(image.texture, c.r,c.g,c.b);
    SDL_SetTextureAlphaMod(image.texture, c.a);
    SDL_FRect rect = { x,y,image.w,image.h };
    if (clip) { rect.w = (float)clip->w, rect.h = (float)clip->h; }
    rect.x = roundf(rect.x) - gRenderOffset.x;
    rect.y = roundf(rect.y) - gRenderOffset.y;
    rect.w = roundf(rect.w);
    rect.h = roundf(rect.h);
    SDL_RenderCopyExF(gWindow.renderer, image.texture, clip, &rect, 0.0f, NULL, flip);
}

INTERNAL void DrawImageEx (Image& image, float x, float y, float angle, Flip flip, const SDL_Rect* clip)
{
    SDL_Color c = ColorToSDLColor(image.color);
    SDL_SetTextureColorMod(image.texture, c.r,c.g,c.b);
    SDL_SetTextureAlphaMod(image.texture, c.a);
    SDL_FRect rect = { x,y,image.w,image.h };
    if (clip) { rect.w = (float)clip->w, rect.h = (float)clip->h; }
    rect.x = roundf(rect.x) - gRenderOffset.x;
    rect.y = roundf(rect.y) - gRenderOffset.y;
    rect.w = roundf(rect.w);
    rect.h = roundf(rect.h);
    SDL_FPoint center = { image.w/2, image.h/2 };
    if (clip) { center.x = (float)clip->w/2, center.y = (float)clip->h/2; }
    SDL_RenderCopyExF(gWindow.renderer, image.texture, clip, &rect, angle, &center, flip);
}

INTERNAL void DrawText (Font& font, std::string text, float x, float y, Color color)
{
    // NOTE: We just assume the caller wants multi-line text to be center aligned.

    font.image.color = color;

    float ix = x;
    float iy = y;

    int line = 0;

    for (int i=0; i<text.length(); ++i)
    {
        if (text[i] == '\n')
        {
            ix = x + (GetTextLineWidth(font, text, 0)/2) - (GetTextLineWidth(font, text, line+1)/2);
            iy += font.charh;
            line++;
        }
        else
        {
            DrawImage(font.image, ix, iy, FLIP_NONE, &font.bounds[static_cast<U8>(text.at(i))]);
            ix += font.charw;
        }
    }
}
