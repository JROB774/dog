#ifndef MENU_HPP
#define MENU_HPP

GLOBAL struct MenuState
{
    Image title;
    Image help;

} gMenuState;

INTERNAL void InitMenu   ();
INTERNAL void QuitMenu   ();
INTERNAL void UpdateMenu (float dt);
INTERNAL void RenderMenu (float dt);

#endif /* MENU_HPP */
