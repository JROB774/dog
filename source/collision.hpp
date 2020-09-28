#ifndef COLLISION_HPP
#define COLLISION_HPP

INTERNAL bool PointAndRectCollision  (Vec2 p, Rect r);
INTERNAL bool RectAndRectCollision   (Rect a, Rect b);
INTERNAL bool RayAndRectCollision    (Vec2 origin, Vec2 dir, Rect rect, Vec2& contact_point, Vec2& contact_normal, float& t_hit_near);
INTERNAL bool EntityAndTileCollision (Vec2 pos, Rect bounds, Vec2 vel, int tx, int ty, Vec2& contact_point, Vec2& contact_normal, float& contact_time, float dt);
INTERNAL bool EntityAndMapCollision  (Vec2 pos, Rect bounds, Vec2& vel, Map& map, Vec2& contact_normal, float dt); // Also performs collision correction.

#endif /* COLLISION_HPP */