INTERNAL void SetCamera (float x, float y)
{
    // Lock the camera within the map boundaries and then set its position.
    float xmax = (float)((gWorld.current_map.w * TILE_W) - WINDOW_SCREEN_W);
    float ymax = (float)((gWorld.current_map.h * TILE_H) - WINDOW_SCREEN_H);

    if (x < 0)    x = 0;
    if (y < 0)    y = 0;
    if (x > xmax) x = xmax;
    if (y > ymax) y = ymax;

    gCamera.x = roundf(x);
    gCamera.y = roundf(y);
}

INTERNAL void BeginCamera ()
{
    gRenderOffset.x = gCamera.x;
    gRenderOffset.y = gCamera.y;
}

INTERNAL void EndCamera ()
{
    gRenderOffset.x = 0;
    gRenderOffset.y = 0;
}
