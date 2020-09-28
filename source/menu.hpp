#ifndef MENU_HPP
#define MENU_HPP

enum MenuMode
{
    MENU_MODE_MAINMENU,
    MENU_MODE_CONTROLS,
    MENU_MODE_SETTINGS,
};

GLOBAL struct MenuState
{
    MenuMode mode;
    int selected;

    Image title;
    Image help;
    Image caret;

    Animation help_anim;
    Animation caret_anim;

    Sound snd_change;
    Sound snd_select;

} gMenuState;

INTERNAL void InitMenu   ();
INTERNAL void QuitMenu   ();
INTERNAL void UpdateMenu (float dt);
INTERNAL void RenderMenu (float dt);

#endif /* MENU_HPP */
