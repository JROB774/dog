INTERNAL void DrawPoint (float x, float y, Color color)
{
    SDL_Color c = ColorToSDLColor(color);
    SDL_SetRenderDrawColor(gWindow.renderer, c.r,c.g,c.b,c.a);
    SDL_RenderDrawPointF(gWindow.renderer, x,y);
}

INTERNAL void DrawLine (float x1, float y1, float x2, float y2, Color color)
{
    SDL_Color c = ColorToSDLColor(color);
    SDL_SetRenderDrawColor(gWindow.renderer, c.r,c.g,c.b,c.a);
    SDL_RenderDrawLineF(gWindow.renderer, x1,y1,x2,y2);
}

INTERNAL void DrawRect (float x, float y, float w, float h, Color color)
{
    SDL_Color c = ColorToSDLColor(color);
    SDL_SetRenderDrawColor(gWindow.renderer, c.r,c.g,c.b,c.a);
    Rect rect = { x,y,w,h };
    SDL_RenderDrawRectF(gWindow.renderer, &rect);
}

INTERNAL void DrawFill (float x, float y, float w, float h, Color color)
{
    SDL_Color c = ColorToSDLColor(color);
    SDL_SetRenderDrawColor(gWindow.renderer, c.r,c.g,c.b,c.a);
    Rect rect = { x,y,w,h };
    SDL_RenderFillRectF(gWindow.renderer, &rect);
}

INTERNAL void DrawImage (Image& image, float x, float y, Flip flip, const SDL_Rect* clip)
{
    SDL_Color c = ColorToSDLColor(image.color);
    SDL_SetTextureColorMod(image.texture, c.r,c.g,c.b);
    SDL_SetTextureAlphaMod(image.texture, c.a);
    Rect rect = { x,y,image.w,image.h };
    if (clip) { rect.w = (float)clip->w, rect.h = (float)clip->h; }
    rect.x = roundf(rect.x);
    rect.y = roundf(rect.y);
    rect.w = roundf(rect.w);
    rect.h = roundf(rect.h);
    SDL_RenderCopyExF(gWindow.renderer, image.texture, clip, &rect, 0.0f, NULL, flip);
}
