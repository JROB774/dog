INTERNAL bool PointAndRectCollision (Vec2 p, Rect r)
{
    return ((p.x >= r.x) && (p.y >= r.y) && (p.x < r.x+r.w) && (p.y < r.y+r.h));
}

INTERNAL bool RectAndRectCollision (Rect a, Rect b)
{
    return ((a.x < b.x+b.w) && (a.x+a.w > b.x) && (a.y < b.y+b.h) && (a.y+a.h > b.y));
}

INTERNAL bool RayAndRectCollision (Vec2 origin, Vec2 dir, Rect rect, Vec2& contact_point, Vec2& contact_normal, float& t_hit_near)
{
    contact_point = { 0,0 };
    contact_normal = { 0,0 };

    float t_near_x = (rect.x          - origin.x) * (1 / dir.x);
    float t_near_y = (rect.y          - origin.y) * (1 / dir.y);
    float  t_far_x = (rect.x + rect.w - origin.x) * (1 / dir.x);
    float  t_far_y = (rect.y + rect.h - origin.y) * (1 / dir.y);

    if (std::isnan(t_near_x) || std::isnan(t_far_x)) return false;
    if (std::isnan(t_near_y) || std::isnan(t_far_y)) return false;

    if (t_near_x > t_far_x) std::swap(t_near_x, t_far_x);
    if (t_near_y > t_far_y) std::swap(t_near_y, t_far_y);

    if (t_near_x > t_far_y || t_near_y > t_far_x) return false;

          t_hit_near = std::max(t_near_x, t_near_y);
    float t_hit_far  = std::min(t_far_x, t_far_y);

    if (t_hit_far < 0) return false;

    contact_point.x = origin.x + t_hit_near * dir.x;
    contact_point.y = origin.y + t_hit_near * dir.y;

    if (t_near_x > t_near_y)
    {
        if ((1/dir.x) < 0) contact_normal = { 1,0 }; else contact_normal = { -1,0 };
    }
    else if (t_near_x < t_near_y)
    {
        if ((1/dir.y) < 0) contact_normal = { 0,1 }; else contact_normal = { 0,-1 };
    }

    return true;
}

INTERNAL bool EntityAndTileCollision (Vec2 pos, Rect bounds, Vec2 vel, int tx, int ty, Vec2& contact_point, Vec2& contact_normal, float& contact_time, float dt)
{
    if (vel.x == 0.0f && vel.y == 0.0f) return false;

    Rect expanded_tile;

    expanded_tile.x = (tx * TILE_W) - (bounds.w / 2);
    expanded_tile.y = (ty * TILE_H) - (bounds.h / 2);
    expanded_tile.w = TILE_W + bounds.w;
    expanded_tile.h = TILE_H + bounds.h;

    float ox = (pos.x + bounds.x) + (bounds.w / 2);
    float oy = (pos.y + bounds.y) + (bounds.h / 2);

    float dx = vel.x * dt;
    float dy = vel.y * dt;

    if (RayAndRectCollision({ ox,oy }, { dx,dy }, expanded_tile, contact_point, contact_normal, contact_time))
    {
        return (contact_time >= 0.0f && contact_time <= 1.0f);
    }

    return false;
}

INTERNAL bool EntityAndMapCollision (Vec2 pos, Rect bounds, Vec2& vel, Map& map, Vec2& contact_normal, float dt)
{
    struct Collision
    {
        int ix,iy;
        float t;
    };

    std::vector<Collision> collisions;
    for (int iy=0; iy<map.h; ++iy)
    {
        for (int ix=0; ix<map.w; ++ix)
        {
            int index = iy*map.w+ix;
            Tile* tile = &map.tiles[index];
            if (tile->type == TILE_SOLID)
            {
                Vec2 cp,cn;
                float ct=0;

                if (EntityAndTileCollision(pos,bounds,vel, ix,iy, cp,cn,ct, dt))
                {
                    collisions.push_back({ ix,iy, ct });
                }
            }
        }
    }

    std::sort(collisions.begin(), collisions.end(),
    [](const Collision& a, const Collision& b)
    {
        return (a.t < b.t);
    });

    bool collided = false;

    for (auto c: collisions)
    {
        Vec2 cp,cn;
        float ct=0;
        if (EntityAndTileCollision(pos,bounds,vel, c.ix,c.iy, cp,cn,ct, dt))
        {
            contact_normal = cn;
            vel.x += cn.x * abs(vel.x) * (1-c.t);
            vel.y += cn.y * abs(vel.y) * (1-c.t);
            collided = true;
        }
    }

    return collided;
}

INTERNAL bool ParticleAndMapCollision (Vec2 pos, Rect bounds, Vec2& vel, Map& map, Vec2& contact_normal, float dt)
{
    struct Collision
    {
        int ix,iy;
        float t;
    };

    std::vector<Collision> collisions;
    for (int iy=0; iy<map.h; ++iy)
    {
        for (int ix=0; ix<map.w; ++ix)
        {
            int index = iy*map.w+ix;
            Tile* tile = &map.tiles[index];
            if (tile->type == TILE_SOLID)
            {
                Vec2 cp,cn;
                float ct=0;

                if (EntityAndTileCollision(pos,bounds,vel, ix,iy, cp,cn,ct, dt))
                {
                    collisions.push_back({ ix,iy, ct });
                }
            }
        }
    }

    std::sort(collisions.begin(), collisions.end(),
    [](const Collision& a, const Collision& b)
    {
        return (a.t < b.t);
    });

    bool collided = false;

    for (auto c: collisions)
    {
        Vec2 cp,cn;
        float ct=0;
        if (EntityAndTileCollision(pos,bounds,vel, c.ix,c.iy, cp,cn,ct, dt))
        {
            contact_normal = cn;
            collided = true;
        }
    }

    return collided;
}

INTERNAL bool EntityAndEntityCollision (Vec2 apos, Rect abounds, Vec2 bpos, Rect bbounds)
{
    Rect a,b;

    a.x = apos.x + abounds.x;
    a.y = apos.y + abounds.y;
    a.w =          abounds.w;
    a.h =          abounds.h;
    b.x = bpos.x + bbounds.x;
    b.y = bpos.y + bbounds.y;
    b.w =          bbounds.w;
    b.h =          bbounds.h;

    return ((a.x + a.w > b.x) && (a.y + a.h > b.y) &&
            (a.x < b.x + b.w) && (a.y < b.y + b.h));
}

INTERNAL bool EntityLineOfSight (Vec2 apos, Rect abounds, Vec2 bpos, Rect bbounds, Map& map)
{
    float ax = apos.x + abounds.x + (abounds.w/2);
    float ay = apos.y + abounds.y + (abounds.h/2);
    float bx = bpos.x + bbounds.x + (bbounds.w/2);
    float by = bpos.y + bbounds.y + (bbounds.h/2);

    Vec2 delta = { bx-ax, by-ay };

    for (int iy=0; iy<map.h; ++iy)
    {
        for (int ix=0; ix<map.w; ++ix)
        {
            int index = iy*map.w+ix;
            Tile* tile = &map.tiles[index];
            if (tile->type == TILE_SOLID)
            {
                Vec2 cp,cn;
                float ct=0;

                if (EntityAndTileCollision({ ax,ay },{ 0,0,1,1 },delta, ix,iy, cp,cn,ct, 1.0f))
                {
                    return false;
                }
            }
        }
    }

    return true;
}
