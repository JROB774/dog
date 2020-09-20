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
    SDL_FRect rect = { x,y,w,h };
    SDL_RenderDrawRectF(gWindow.renderer, &rect);
}

INTERNAL void DrawFill (float x, float y, float w, float h, Color color)
{
    SDL_Color c = ColorToSDLColor(color);
    SDL_SetRenderDrawColor(gWindow.renderer, c.r,c.g,c.b,c.a);
    SDL_FRect rect = { x,y,w,h };
    SDL_RenderFillRectF(gWindow.renderer, &rect);
}
