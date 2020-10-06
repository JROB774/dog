#ifndef BREAK_HPP
#define BREAK_HPP

struct Dog; // Predeclare because this needs to know about it!

struct BreakableBlock
{
    Vec2 pos;
	Rect bounds;
	bool dead;
};

GLOBAL Image gBreakableBlockImage;
GLOBAL Sound gBreakableBlockSound;

INTERNAL void InitBreakableBlock   ();
INTERNAL void DeleteBreakableBlock ();

INTERNAL void CreateBreakableBlock (BreakableBlock& block, float x, float y);
INTERNAL bool TryBreakABlock       (Dog& dog, BreakableBlock& block);
INTERNAL void BreakBlock           (BreakableBlock& block);
INTERNAL void RenderBreakableBlock (BreakableBlock& block);

INTERNAL void RespawnMapBlocks ();

#endif /* BREAK_HPP */
