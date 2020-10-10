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

    LoadAnimation(gBadges.caret_anim, "badgecaret.anim");

    gBadges.cursor_x = 0;
    gBadges.cursor_y = 0;

    // COMPLETE
    gBadges.description[0][0] = "COMPLETE NORMAL MODE";
    gBadges.description[0][1] = "COMPLETE CHALLENGE MODE";
    gBadges.description[0][2] = "COMPLETE NORMAL+ MODE";
    gBadges.description[0][3] = "COMPLETE CHALLENGE+ MODE";
    // COLLECT
    gBadges.description[1][0] = "COLLECT ALL NORMAL BONES";
    gBadges.description[1][1] = "COLLECT ALL CHALLENGE\nBONES";
    gBadges.description[1][2] = "COLLECT ALL NORMAL+ BONES";
    gBadges.description[1][3] = "COLLECT ALL CHALLENGE+\nBONES";
    // IRONMAN
    gBadges.description[2][0] = "COMPLETE NORMAL MODE\nWITHOUT DYING";
    gBadges.description[2][1] = "COMPLETE CHALLENGE MODE\nWITHOUT DYING";
    gBadges.description[2][2] = "COMPLETE NORMAL+\nWITHOUT DYING";
    gBadges.description[2][3] = "COMPLETE CHALLENGE+\nWITHOUT DYING";
    // SPEEDRUN
    gBadges.description[3][0] = "COMPLETE NORMAL MODE\nIN 00:00 MINUTES";
    gBadges.description[3][1] = "COMPLETE CHALLENGE MODE\nIN 00:00 MINUTES";
    gBadges.description[3][2] = "COMPLETE NORMAL+ MODE\nIN 00:00 MINUTES";
    gBadges.description[3][3] = "COMPLETE CHALLENGE+ MODE\nIN 00:00 MINUTES";
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

    FreeAnimation(gBadges.caret_anim);

    FreeImage(gBadges.background);
    FreeImage(gBadges.badges    );
    FreeImage(gBadges.caret     );
}
