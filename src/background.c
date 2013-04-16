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

void dummyLoad(){
	consoleInit();
	
	consoleInitText(0, 1, &snesfont);
	
	consoleSetTextCol(RGB15(26,2,2), RGB15(0,0,0));
	
	bgInitTileSet(1, &patterns, &palette, 0, (&patterns_end - &patterns), 16*2, BG_16COLORS, 0x5000);//HACKY!!! don't use
	//bgSetMapPtr(1, 0x3000, SC_32x32);
	bgInitMapSet(1, &map, (&map_end - &map), SC_32x32, 0x4000);//HACKY!!! don't use
	
	setMode(BG_MODE1, 0);
	
	setBrightness(0xF);
}
