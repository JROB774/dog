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
	printf("boundsx: %f, boundsy: %f, boundsw: %f, boundsh: %f\n",_bounds.x,_bounds.y,_bounds.w,_bounds.h);
	printf("tempx: %f, tempy: %f, tempw: %f, temph: %f\n",temp.x,temp.y,temp.w,temp.h);
	printf("_block: %f, _blocky: %f, _blockw: %f, _blockh: %f\n",_block.posistion.x,_block.posistion.y,_block.posistion.w,_block.posistion.h);



	if((temp.x < _block.posistion.x + _block.posistion.w) && (temp.x + temp.w > _block.posistion.x) &&
        (temp.y < _block.posistion.y + _block.posistion.h) && (temp.y + temp.h > _block.posistion.y)){
			printf("COMMAND");
            _block.dead = true;
    }
}

void BreakBlock(BreakableBlock& _block)
{
	_block.dead = true;
	printf("NOM\n");
}

void RenderBreakableBlock(BreakableBlock& _block)
{
	if(!_block.dead){
		DrawImage(breakable_block_image, _block.posistion.x, _block.posistion.y);
	}
}
