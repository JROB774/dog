INTERNAL void UpdateCamera (float dt)
{
    if (gCamera.timer > 0.0f)
    {
        gCamera.timer -= dt;
        if (gCamera.timer <= 0.0f)
        {
            gCamera.shake_minx = 0.0f;
            gCamera.shake_miny = 0.0f;
            gCamera.shake_maxx = 0.0f;
            gCamera.shake_maxy = 0.0f;
        }
    }

    gCamera.x = Lerp(gCamera.x, gCamera.target_x, dt*5);
    gCamera.y = Lerp(gCamera.y, gCamera.target_y, dt*5);
}

INTERNAL void SetCameraTarget (float x, float y)
{
    // Lock the camera within the map boundaries and then set its position.
    float xmax = (float)((gWorld.current_map.w * TILE_W) - WINDOW_SCREEN_W);
    float ymax = (float)((gWorld.current_map.h * TILE_H) - WINDOW_SCREEN_H);

    if (x < 0)    x = 0;
    if (y < 0)    y = 0;
    if (x > xmax) x = xmax;
    if (y > ymax) y = ymax;

    gCamera.target_x = roundf(x);
    gCamera.target_y = roundf(y);
}

INTERNAL void SetCamera (float x, float y)
{
    // Lock the camera within the map boundaries and then set its position.
    float xmax = (float)((gWorld.current_map.w * TILE_W) - WINDOW_SCREEN_W);
    float ymax = (float)((gWorld.current_map.h * TILE_H) - WINDOW_SCREEN_H);

    if (x < 0)    x = 0;
    if (y < 0)    y = 0;
    if (x > xmax) x = xmax;
    if (y > ymax) y = ymax;

    gCamera.x        = roundf(x);
    gCamera.y        = roundf(y);
    gCamera.target_x = roundf(x);
    gCamera.target_y = roundf(y);
}

INTERNAL void BeginCamera ()
{
    gRenderOffset.x = gCamera.x;
    gRenderOffset.y = gCamera.y;

    if (gCamera.timer)
    {
        gRenderOffset.x += RandomFloatRange(gCamera.shake_minx, gCamera.shake_maxx);
        gRenderOffset.y += RandomFloatRange(gCamera.shake_miny, gCamera.shake_maxy);
    }
}

INTERNAL void EndCamera ()
{
    gRenderOffset.x = 0;
    gRenderOffset.y = 0;
}

INTERNAL void ShakeCamera (float minx, float miny, float maxx, float maxy, float duration)
{
    gCamera.shake_minx += minx;
    gCamera.shake_miny += miny;
    gCamera.shake_maxx += maxx;
    gCamera.shake_maxy += maxy;

    gCamera.timer += duration;
}

INTERNAL void ResetCameraShake ()
{
    gCamera.shake_minx = 0.0f;
    gCamera.shake_miny = 0.0f;
    gCamera.shake_maxx = 0.0f;
    gCamera.shake_maxy = 0.0f;

    gCamera.timer = 0.0f;
}
