#ifndef GUI_HPP
#define GUI_HPP

GLOBAL struct Gui
{
    Image splat;
    float current_x;
    float target_x;
    float timer;

} gGui;

INTERNAL void InitGui ();
INTERNAL void QuitGui ();
INTERNAL void DrawGui (float dt);

// INTERNAL void DisplayGui ();

#endif /* GUI_HPP */
