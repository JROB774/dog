void CreateFont()
{
	LoadImage(gfont.image, "TEMP_FONT.bmp");

	for(int iy = 0; iy < gfont.column_amount; iy++){
		for(int ix = 0; ix < gfont.row_amount; ix++){
			gfont.bounds[ix + (iy * gfont.row_amount)] = {ix * gfont.base.w, iy * gfont.base.h, gfont.base.w, gfont.base.h};
		}
	}
}

void RenderFont(std::string _text, int _x, int _y)
{
	for(int i = 0; i < _text.length(); i++){
		DrawImage(gfont.image, _x, _y, FLIP_NONE, &gfont.bounds[static_cast<U8>(_text.at(i))]);
		_x += gfont.base.w;
	}
}