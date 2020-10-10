#ifndef BADGES_HPP
#define BADGES_HPP

// Most of this stuff is used by the main menu for displaying the badge
// screen. Look at the "menu.hpp" and "menu.cpp" files for that stuff.

enum BadgeType
{
    BADGE_TYPE_LOCKED_COMPLETE,
    BADGE_TYPE_LOCKED_COLLECT,
    BADGE_TYPE_LOCKED_IRONMAN,
    BADGE_TYPE_LOCKED_SPEEDRUN,
    BADGE_TYPE_UNLOCKED_COMPLETE,
    BADGE_TYPE_UNLOCKED_COLLECT,
    BADGE_TYPE_UNLOCKED_IRONMAN,
    BADGE_TYPE_UNLOCKED_SPEEDRUN,
    BADGE_TYPE_TOTAL
};

GLOBAL struct Badges
{
    Animation anim[BADGE_TYPE_TOTAL];

    Image background;
    Image badges;
    Image caret;

    std::string description[4][4];

    int cursor_x;
    int cursor_y;

    bool unlocked_complete[4];
    bool unlocked_collect [4];
    bool unlocked_ironman [4];
    bool unlocked_speedrun[4];

} gBadges;

INTERNAL void InitBadges ();
INTERNAL void QuitBadges ();

#endif /* BADGES_HPP */
