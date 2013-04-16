#include <snes.h>
#include "background.h"

//Grab the current layer the player is on
static Map_s *bgGetLayer(BGPos_s *bg)
{
	return bg->curLevel->map[bg->layer];
}

//Draw a background at a given screen position for a players BGPos_s
void BG_Draw(u16 x, u16 y, u8 wd, u8 ht, BGPos_s *bg)
{
	//grab pointer to tiles needed
	//grab pointer to map needed
	//calculate map position to draw from using info->x, info->y
	//for each tile within range of info->x, info->y and info->x + wd, info->y + ht
	//draw to screen from tile position x and y to x+wd, y+wd
}

//Given a pixel location on a map, returns the tile number in its location
//each tile is 8x8 pixels, hence the >>3
u16 BG_GetTile(u16 xPix, u16 yPix, BGPos_s *bg)
{
	Map_s *layer = bgGetLayer(bg);
	u16 lvlWd = (bg->curLevel->width)>>3;
	u16 *ptr = (u16 *) &layer->gfx + (yPix>>3)*lvlWd + (xPix>>3);
	return (*ptr);
}
