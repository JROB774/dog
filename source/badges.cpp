INTERNAL void InitBadges ()
{
    LoadImage(gBadges.image, "badges.bmp");

    LoadAnimation(gBadges.anim[BADGE_TYPE_LOCKED_COMPLETE  ], "badge-locked-complete.anim"  );
    LoadAnimation(gBadges.anim[BADGE_TYPE_LOCKED_COLLECT   ], "badge-locked-collect.anim"   );
    LoadAnimation(gBadges.anim[BADGE_TYPE_LOCKED_IRONMAN   ], "badge-locked-ironman.anim"   );
    LoadAnimation(gBadges.anim[BADGE_TYPE_LOCKED_SPEEDRUN  ], "badge-locked-speedrun.anim"  );
    LoadAnimation(gBadges.anim[BADGE_TYPE_UNLOCKED_COMPLETE], "badge-unlocked-complete.anim");
    LoadAnimation(gBadges.anim[BADGE_TYPE_UNLOCKED_COLLECT ], "badge-unlocked-collect.anim" );
    LoadAnimation(gBadges.anim[BADGE_TYPE_UNLOCKED_IRONMAN ], "badge-unlocked-ironman.anim" );
    LoadAnimation(gBadges.anim[BADGE_TYPE_UNLOCKED_SPEEDRUN], "badge-unlocked-speedrun.anim");
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

    FreeImage(gBadges.image);
}
