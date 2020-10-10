#ifndef GUI_HPP
#define GUI_HPP

GLOBAL struct Gui
{
    Image splat;

} gGui;

INTERNAL void InitGui ();
INTERNAL void QuitGui ();
INTERNAL void DrawGui (float dt);

#endif /* GUI_HPP */
