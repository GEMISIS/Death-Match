#include "background.h"

//Grab the current layer the player is on
static Gfx_s *bgGetLayer(BGPos_s *bg)
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
	Gfx_s *layer = bgGetLayer(bg);
	u16 lvlWd = (bg->curLevel->width)>>3;
	u16 *ptr = (u16 *) &layer->map + (yPix>>3)*lvlWd + (xPix>>3);
	return (*ptr);
}

/*
Default background load. Pretty basic for now
*/
void BG_Load(u8 hwLayer, static Gfx_s *lvlmap)
{
	//initialize background tiles
	bgInitTileSet(hwLayer, lvlmap->gfx, lvlmap->pal, 0,
				  lvlmap->gfxSize, 16*2,
				  BG_16COLORS, BG_TILE_ADDR1);

	bgInitMapSet(hwLayer, lvlmap->map,
				 lvlmap->mapSize, SC_32x32, BG_MAP_ADDR1);
}




//==================================================
//Test stuff
//==================================================
static Gfx_s TestLevel;

static void setLevel(Gfx_s *lh, char *gfx, char *gfxe,
	char *pal, char *pale, char *map, char *mape)
{
	lh->gfx = gfx;
	lh->gfxSize = (gfxe - gfx);
	lh->pal = pal;
	lh->palSize = (pale - pal);
	lh->map = map;
	lh->mapSize = (mape - map);
}

void dummyLoad(){
	consoleInit();

	consoleInitText(0, 1, &snesfont);

	consoleSetTextCol(RGB15(26,2,2), RGB15(0,0,0));


	setLevel(&TestLevel, &patterns, &patterns_end, &palette, &palette_end, &map, &map_end);
	BG_Load(BG_P1_HW_LAYER, &TestLevel);

	setMode(BG_MODE1, 0);

	setBrightness(0xF);
}
