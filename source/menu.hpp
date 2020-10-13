#ifndef MENU_HPP
#define MENU_HPP

enum MenuMode
{
    MENU_MODE_MAINMENU,
    MENU_MODE_BADGES,
    MENU_MODE_SETTINGS,
    MENU_MODE_CREDITS,
};

GLOBAL struct MenuState
{
    MenuMode mode;
    int selected;

    Image title;
    Image bar;
    Image caret;
    Image credit;

    Animation caret_anim;

    Sound snd_change;
    Sound snd_select;

    Music music;

} gMenuState;

INTERNAL void InitMenu   ();
INTERNAL void QuitMenu   ();
INTERNAL void UpdateMenu (float dt);
INTERNAL void RenderMenu (float dt);
INTERNAL void GoToMenu   ();

INTERNAL void UpdateMenuMain     (float dt, bool up, bool down, bool right, bool left, bool action, bool back);
INTERNAL void RenderMenuMain     (float dt);
INTERNAL void UpdateMenuBadges   (float dt, bool up, bool down, bool right, bool left, bool action, bool back);
INTERNAL void RenderMenuBadges   (float dt);
INTERNAL void UpdateMenuSettings (float dt, bool up, bool down, bool right, bool left, bool action, bool back);
INTERNAL void RenderMenuSettings (float dt);
INTERNAL void UpdateMenuCredits  (float dt, bool up, bool down, bool right, bool left, bool action, bool back);
INTERNAL void RenderMenuCredits  (float dt);

#endif /* MENU_HPP */
