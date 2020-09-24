#ifndef BREAK_HPP
#define BREAK_HPP

struct BreakableBlock{

	Rect posistion;
	bool dead;
};

GLOBAL Image breakable_block_image;

void InitBreakableBlock();
void CreateBreakableBlock(BreakableBlock& _block, float _x, float _y);

void BreakbleBlockCollision(Rect _bounds, BreakableBlock& _block);
void BreakBlock(BreakableBlock& _block);

void RenderBreakableBlock(BreakableBlock& _block);

void DestroyBreakableBlock();

#endif