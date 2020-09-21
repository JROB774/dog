#ifndef RENDERER_HPP
#define RENDERER_HPP

INTERNAL void DrawPoint (float x,  float y,                      Color color);
INTERNAL void DrawLine  (float x1, float y1, float x2, float y2, Color color);
INTERNAL void DrawRect  (float x,  float y,  float w,  float h,  Color color);
INTERNAL void DrawFill  (float x,  float y,  float w,  float h,  Color color);

INTERNAL void DrawImage (Image& image, float x, float y, const SDL_Rect* clip = NULL);

#endif /* RENDERER_HPP */
