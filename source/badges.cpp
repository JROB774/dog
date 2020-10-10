INTERNAL void InitBadges ()
{
    LoadImage(gBadges.background, "badgeback.bmp" );
    LoadImage(gBadges.badges,     "badges.bmp"    );
    LoadImage(gBadges.caret,      "badgecaret.bmp");

    LoadAnimation(gBadges.anim[BADGE_TYPE_LOCKED_COMPLETE  ], "badge-locked-complete.anim"  );
    LoadAnimation(gBadges.anim[BADGE_TYPE_LOCKED_COLLECT   ], "badge-locked-collect.anim"   );
    LoadAnimation(gBadges.anim[BADGE_TYPE_LOCKED_IRONMAN   ], "badge-locked-ironman.anim"   );
    LoadAnimation(gBadges.anim[BADGE_TYPE_LOCKED_SPEEDRUN  ], "badge-locked-speedrun.anim"  );
    LoadAnimation(gBadges.anim[BADGE_TYPE_UNLOCKED_COMPLETE], "badge-unlocked-complete.anim");
    LoadAnimation(gBadges.anim[BADGE_TYPE_UNLOCKED_COLLECT ], "badge-unlocked-collect.anim" );
    LoadAnimation(gBadges.anim[BADGE_TYPE_UNLOCKED_IRONMAN ], "badge-unlocked-ironman.anim" );
    LoadAnimation(gBadges.anim[BADGE_TYPE_UNLOCKED_SPEEDRUN], "badge-unlocked-speedrun.anim");

    gBadges.cursor_x = 0;
    gBadges.cursor_y = 0;

    // COMPLETE
    gBadges.description[0][0] = "COMPLETE THE GAME";
    gBadges.description[0][1] = "COMPLETE THE CHALLENGE";
    gBadges.description[0][2] = "COMPLETE THE GAME\nON HARD MODE";
    gBadges.description[0][3] = "COMPLETE THE CHALLENGE\nON HARD MODE";
    // COLLECT
    gBadges.description[1][0] = "COLLECT ALL GAME BONES";
    gBadges.description[1][1] = "COLLECT ALL CHALLENGE\nBONES";
    gBadges.description[1][2] = "COLLECT ALL GAME BONES\nON HARD MODE";
    gBadges.description[1][3] = "COLLECT ALL CHALLENGE\nBONES ON HARD MODE";
    // IRONMAN
    gBadges.description[2][0] = "COMPLETE THE GAME\nWITHOUT DYING";
    gBadges.description[2][1] = "COMPLETE THE CHALLENGE\nWITHOUT DYING";
    gBadges.description[2][2] = "COMPLETE THE GAME\nON HARD MODE\nWITHOUT DYING";
    gBadges.description[2][3] = "COMPLETE THE CHALLENGE\nON HARD MODE\nWITHOUT DYING";
    // SPEEDRUN
    gBadges.description[3][0] = "COMPLETE THE GAME\nIN 00:00 MINUTES";
    gBadges.description[3][1] = "COMPLETE THE CHALLENGE\nIN 00:00 MINUTES";
    gBadges.description[3][2] = "COMPLETE THE GAME\nON HARD MODE\nIN 00:00 MINUTES";
    gBadges.description[3][3] = "COMPLETE THE CHALLENGE\nON HARD MODE\nIN 00:00 MINUTES";
}

INTERNAL void QuitBadges ()
{
    FreeAnimation(gBadges.anim[BADGE_TYPE_LOCKED_COMPLETE  ]);
    FreeAnimation(gBadges.anim[BADGE_TYPE_LOCKED_COLLECT   ]);
    FreeAnimation(gBadges.anim[BADGE_TYPE_LOCKED_IRONMAN   ]);
    FreeAnimation(gBadges.anim[BADGE_TYPE_LOCKED_SPEEDRUN  ]);
    FreeAnimation(gBadges.anim[BADGE_TYPE_UNLOCKED_COMPLETE]);
    FreeAnimation(gBadges.anim[BADGE_TYPE_UNLOCKED_COLLECT ]);
    FreeAnimation(gBadges.anim[BADGE_TYPE_UNLOCKED_IRONMAN ]);
    FreeAnimation(gBadges.anim[BADGE_TYPE_UNLOCKED_SPEEDRUN]);

    FreeImage(gBadges.background);
    FreeImage(gBadges.badges    );
    FreeImage(gBadges.caret     );
}
