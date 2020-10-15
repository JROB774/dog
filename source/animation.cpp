INTERNAL void LoadAnimation (Animation& animation, std::string file_name)
{
    file_name = "assets/anims/" + file_name;
    GonObject gon = GonObject::Load(file_name);
    if (gon.type != GonObject::FieldType::OBJECT)
    {
        LOG_ERROR(ERR_MAX, "Animation not a GON object! (%s)", file_name.c_str());
        return;
    }

    animation.looped = gon["looped"].Bool();

    int x = gon["start_position"][0].Int();
    int y = gon["start_position"][1].Int();
    int w = gon["frame_size"    ][0].Int();
    int h = gon["frame_size"    ][1].Int();

    int frame_count = gon["frame_count"].Int();
    animation.frames.clear();
    for (int i=0; i<frame_count; ++i)
    {
        float duration = (float)gon["frame_durations"][i].Number();
        animation.frames.push_back({ duration, { x,y,w,h } });
        x += w;
    }

    animation.state.timer = 0;
    animation.state.frame = 0;
}

INTERNAL void FreeAnimation (Animation& animation)
{
    animation.frames.clear();
}

INTERNAL void UpdateAnimation (Animation& animation, float dt)
{
    // We don't want to update animations in debug screenshot mode!
    #if defined(BUILD_DEBUG)
    if (gAppState.screenshot_mode) return;
    #endif

    if (animation.looped || animation.state.frame < animation.frames.size())
    {
        float time = 0.0f;
        for (int i=0; i<animation.frames.size(); ++i)
        {
            time += animation.frames.at(i).duration;
            if (animation.state.timer <= time)
            {
                animation.state.frame = i;
                break;
            }
        }

        animation.state.timer += dt;

        // Handles wrapping back round to the start of the animation if we're looped.
        if (animation.looped)
        {
            float total_time = 0.0f;
            for (auto& frame: animation.frames)
            {
                total_time += frame.duration;
            }

            if (total_time > 0.0f)
            {
                while (animation.state.timer >= total_time)
                {
                    animation.state.timer -= total_time;
                }
            }
        }
    }
}

INTERNAL void ResetAnimation (Animation& animation)
{
    animation.state.timer = 0;
    animation.state.frame = 0;
}

INTERNAL bool IsAnimationDone (Animation& animation)
{
    if (animation.looped) return false;
    float total_time = 0.0f;
    for (auto& frame: animation.frames) total_time += frame.duration;
    if (animation.state.timer >= total_time) return true;
    return false;
}

INTERNAL const SDL_Rect* GetAnimationClip (Animation& animation)
{
    return &animation.frames.at(animation.state.frame).clip;
}

INTERNAL int GetAnimationFrameWidth (Animation& animation)
{
    return GetAnimationClip(animation)->w;
}

INTERNAL int GetAnimationFrameHeight (Animation& animation)
{
    return GetAnimationClip(animation)->h;
}
