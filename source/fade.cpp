GLOBAL constexpr float FADE_SPEED = 450.0f;

enum FadeState { FADE_OUT, FADE_BLACK, FADE_IN };

GLOBAL struct Fade
{
    Image up,right,down,left;
    FadeType type;
    FadeCallback callback;
    FadeState state;
    float x1,y1;
    float x2,y2;

} gFade;

////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////

// FADE_UP

INTERNAL void StartFadeUp ()
{
    gFade.x1 = 0.0f;
    gFade.y1 = WINDOW_SCREEN_H;
}
INTERNAL void DoFadeUp (float dt)
{
    if (gFade.state == FADE_OUT)
    {
        gFade.y1 -= FADE_SPEED * dt;
        DrawImage(gFade.up, gFade.x1,gFade.y1);
        if (gFade.y1 <= -16)
        {
            gFade.state = FADE_BLACK;
            // Setup for the fade in.
            gFade.x1 = 0.0f;
            gFade.y1 = 0.0f;
        }
    }
    else if (gFade.state == FADE_IN)
    {
        gFade.y1 -= FADE_SPEED * dt;
        DrawImage(gFade.down, gFade.x1,gFade.y1);
        if (gFade.y1 <= -gFade.down.h)
        {
            gFade.type = FADE_NONE;
        }
    }
}

// FADE_RIGHT

INTERNAL void StartFadeRight ()
{
    gFade.x1 = -gFade.right.w;
    gFade.y1 = 0.0f;
}
INTERNAL void DoFadeRight (float dt)
{
    if (gFade.state == FADE_OUT)
    {
        gFade.x1 += FADE_SPEED * dt;
        DrawImage(gFade.right, gFade.x1,gFade.y1);
        if (gFade.x1 >= 0.0f)
        {
            gFade.state = FADE_BLACK;
            // Setup for the fade in.
            gFade.x1 = -16.0f;
            gFade.y1 = 0.0f;
        }
    }
    else if (gFade.state == FADE_IN)
    {
        gFade.x1 += FADE_SPEED * dt;
        DrawImage(gFade.left, gFade.x1,gFade.y1);
        if (gFade.x1 >= WINDOW_SCREEN_W)
        {
            gFade.type = FADE_NONE;
        }
    }
}

// FADE_DOWN

INTERNAL void StartFadeDown ()
{
    gFade.x1 = 0.0f;
    gFade.y1 = -gFade.down.h;
}
INTERNAL void DoFadeDown (float dt)
{
    if (gFade.state == FADE_OUT)
    {
        gFade.y1 += FADE_SPEED * dt;
        DrawImage(gFade.down, gFade.x1,gFade.y1);
        if (gFade.y1 >= 0.0f)
        {
            gFade.state = FADE_BLACK;
            // Setup for the fade in.
            gFade.x1 = 0.0f;
            gFade.y1 = -16.0f;
        }
    }
    else if (gFade.state == FADE_IN)
    {
        gFade.y1 += FADE_SPEED * dt;
        DrawImage(gFade.up, gFade.x1,gFade.y1);
        if (gFade.y1 >= WINDOW_SCREEN_H)
        {
            gFade.type = FADE_NONE;
        }
    }
}

// FADE_LEFT

INTERNAL void StartFadeLeft ()
{
    gFade.x1 = WINDOW_SCREEN_W;
    gFade.y1 = 0.0f;
}
INTERNAL void DoFadeLeft (float dt)
{
    if (gFade.state == FADE_OUT)
    {
        gFade.x1 -= FADE_SPEED * dt;
        DrawImage(gFade.left, gFade.x1,gFade.y1);
        if (gFade.x1 <= -16)
        {
            gFade.state = FADE_BLACK;
            // Setup for the fade in.
            gFade.x1 = 0.0f;
            gFade.y1 = 0.0f;
        }
    }
    else if (gFade.state == FADE_IN)
    {
        gFade.x1 -= FADE_SPEED * dt;
        DrawImage(gFade.right, gFade.x1,gFade.y1);
        if (gFade.x1 <= -gFade.right.w)
        {
            gFade.type = FADE_NONE;
        }
    }
}

// FADE_SPECIAL

INTERNAL void StartFadeSpecial ()
{
    gFade.x1 = 0.0f;
    gFade.y1 = (float)-gFade.down.h;
    gFade.x2 = 0.0f;
    gFade.y2 = (float)WINDOW_SCREEN_H;
}
INTERNAL void DoFadeSpecial (float dt)
{
    if (gFade.state == FADE_OUT)
    {
        gFade.y1 += FADE_SPEED * dt;
        gFade.y2 -= FADE_SPEED * dt;

        DrawImage(gFade.down, gFade.x1,gFade.y1);
        DrawImage(gFade.up, gFade.x2,gFade.y2);

        if (gFade.y1 >= 0)
        {
            gFade.state = FADE_BLACK;
            // Setup for the fade in.
            gFade.x1 = 0.0f;
            gFade.y1 = 0.0f;
            gFade.x2 = (float)WINDOW_SCREEN_W-gFade.left.w;
            gFade.y2 = 0.0f;
        }
    }
    else if (gFade.state == FADE_IN)
    {
        gFade.x1 -= FADE_SPEED * dt;
        gFade.x2 += FADE_SPEED * dt;

        DrawImage(gFade.right, gFade.x1,gFade.y1);
        DrawImage(gFade.left, gFade.x2,gFade.y2);

        if (gFade.x1 <= -gFade.right.w)
        {
            gFade.type = FADE_NONE;
        }
    }
}

////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////

INTERNAL void InitFade ()
{
    LoadImage(gFade.up,    "fadeu.bmp");
    LoadImage(gFade.right, "fader.bmp");
    LoadImage(gFade.down,  "faded.bmp");
    LoadImage(gFade.left,  "fadel.bmp");

    gFade.type = FADE_NONE;
}

INTERNAL void QuitFade ()
{
    FreeImage(gFade.up);
    FreeImage(gFade.right);
    FreeImage(gFade.down);
    FreeImage(gFade.left);
}

INTERNAL void StartFade (FadeType type, FadeCallback callback)
{
    gFade.type = type;
    gFade.callback = callback;
    gFade.state = FADE_OUT;

    switch (gFade.type)
    {
        case (FADE_UP     ): StartFadeUp     (); break;
        case (FADE_RIGHT  ): StartFadeRight  (); break;
        case (FADE_DOWN   ): StartFadeDown   (); break;
        case (FADE_LEFT   ): StartFadeLeft   (); break;
        case (FADE_SPECIAL): StartFadeSpecial(); break;
    }
}

INTERNAL void RenderFade (float dt)
{
    if (gFade.state == FADE_BLACK)
    {
        if (gFade.callback) gFade.callback();
        gFade.state = FADE_IN;
    }
    switch (gFade.type)
    {
        case (FADE_UP     ): DoFadeUp     (dt); break;
        case (FADE_RIGHT  ): DoFadeRight  (dt); break;
        case (FADE_DOWN   ): DoFadeDown   (dt); break;
        case (FADE_LEFT   ): DoFadeLeft   (dt); break;
        case (FADE_SPECIAL): DoFadeSpecial(dt); break;
    }
}

INTERNAL bool IsFading ()
{
    return (gFade.type != FADE_NONE);
}
