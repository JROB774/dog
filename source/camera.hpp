#ifndef CAMERA_HPP
#define CAMERA_HPP

GLOBAL struct Camera
{
    float x;
    float y;

    float target_x;
    float target_y;

    float shake_minx, shake_maxx;
    float shake_miny, shake_maxy;

    float timer;

} gCamera;

INTERNAL void UpdateCamera (float dt);

INTERNAL void SetCameraTarget (float x, float y);
INTERNAL void SetCamera       (float x, float y);

// Wrap the section of rendering that should be affected by the camera position in these function calls!
INTERNAL void BeginCamera ();
INTERNAL void EndCamera   ();

INTERNAL void ShakeCamera (float minx, float miny, float maxx, float maxy, float duration);
INTERNAL void ResetCameraShake ();

#endif /* CAMERA_HPP */
