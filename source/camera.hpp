#ifndef CAMERA_HPP
#define CAMERA_HPP

GLOBAL struct Camera
{
    float x;
    float y;

    float target_x;
    float target_y;

} gCamera;

INTERNAL void UpdateCamera (float dt);

INTERNAL void SetCameraTarget (float x, float y);
INTERNAL void SetCamera       (float x, float y);

// Wrap the section of rendering that should be affected by the camera position in these function calls!
INTERNAL void BeginCamera ();
INTERNAL void EndCamera   ();

#endif /* CAMERA_HPP */
