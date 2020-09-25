void InitBreakableBlock()
{
	LoadImage(breakable_block_image, "break.bmp");
}

void CreateBreakableBlock(BreakableBlock& _block, float _x, float _y)
{
	_block.posistion = {_x - 4, _y - 4, TILE_W, TILE_H};
}

void BreakbleBlockCollision(Rect _bounds, BreakableBlock& _block)
{
	Rect temp = _bounds;
	if(IsKeyDown(SDL_SCANCODE_W)){temp.y -= 5;}
	else if(IsKeyDown(SDL_SCANCODE_D)){temp.w += 5;}
	else if(IsKeyDown(SDL_SCANCODE_S)){temp.h += 5;}
	else if(IsKeyDown(SDL_SCANCODE_A)){temp.x -= 5;}

	if((temp.x + temp.w > _block.posistion.x) && (temp.y +temp.h > _block.posistion.y) &&
        (temp.x < _block.posistion.x + _block.posistion.w) && (temp.y < _block.posistion.y + _block.posistion.h)){
            BreakBlock(_block);
    }
}

void BreakBlock(BreakableBlock& _block)
{
	_block.dead = true;
}

void RenderBreakableBlock(BreakableBlock& _block)
{
	if(!_block.dead){
		DrawImage(breakable_block_image, _block.posistion.x, _block.posistion.y);
	}
}
