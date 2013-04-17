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
Setting up our own background system.
Hopefully we should be able to draw both players screens
on one background layer. This means we won't be able to
use hardware scrolling which may be hard to implement
software wise, especially since we can't scroll individual tiles
unless in mode 5 and7 or something.
*/
void BG_Load( u8 BG_HW_LAYER, static Gfx_s *lvlmap, u16 BG_TILE_ADDR, u16 BG_MAP_ADDR, u8 pal)
{
	//initialize background tiles
	bgInitTileSet(BG_HW_LAYER, lvlmap->gfx, lvlmap->pal, pal,
				  lvlmap->gfxSize, lvlmap->palSize,
				  BG_16COLORS, BG_TILE_ADDR);

	bgInitMapSet(BG_HW_LAYER, lvlmap->map,
				 lvlmap->mapSize, lvlmap->mapMode, BG_MAP_ADDR);
}




//==================================================
//Test stuff
//==================================================
/*
Figuring out window documentation

void bgSetWindowsRegions_fix(u8 bgNumber, u8 winNumber, u8 xLeft, u8 xRight) {
    if (winNumber == 0) //window 1
    {

    	if(bgNumber < 2) {
    		//Window BG1/BG2 Mask Settings
    		//bits 7-6: BG2 BG4 MATH Window-2 Area (0 = disabled, 1 = inside window, 2 = outside)
    		//bits 5-4: BG2 BG4 MATH Window-1 Area (0 = disabled, 1 = inside window, 2 = outside)
    		//bits 3-2: BG1 BG3 OBJ Window-2 Area (0 = disabled, 1 = inside window, 2 = outside)
    		//bits 1-0: BG1 BG3 OBJ Window-1 Area  (0 = disabled, 1 = inside window, 2 = outside)
	        REG_W12SEL = 0x03; //bgs 1 and 3 are outside window 1, and inside window 2
	    } else {
	    	//bg's 3 and 4
	    	REG_W34SEL = 0x03;
	    }

	    //left and right window boundaries
	    REG_WH0 = xLeft;
        REG_WH1 = xRight;

	    REG_WOBJSEL = 0x03;


        REG_WBGLOG = 0x01;
        REG_WOBJLOG = 0x01;
        REG_TMW = 0x11;
    }
    else //window 2
    {
    	if(bgNumber < 2) {
	        REG_W12SEL = 0x03;   //XNOR
	    } else {
	    	REG_W34SEL = 0x03;  //XNOR
	    }

	    //left and right window boundaries
        REG_WH2 = xLeft;
        REG_WH3 = xRight;

        //something here should be able to select what objects can display
	    REG_WOBJSEL = 0x03;
        REG_WBGLOG = 0x01;
        REG_WOBJLOG = 0x01;

        //window area main screen.
        //bits 7-5 unused, 4 -enable objects(sprites),
        //bits 3 - bg4, 2 - bg3, 1 - bg2, 0 - bg1
        REG_TMW = 0x11;
    }
}
*/

static Gfx_s TestBg1, TestBg2;

static void setLevel(Gfx_s *lh, char *gfx, char *gfxe,
	char *pal, char *pale, char *map, char *mape, u8 tileMode)
{
	lh->gfx = gfx;
	lh->gfxSize = (gfxe - gfx);
	lh->pal = pal;
	lh->palSize = (pale - pal);
	lh->map = map;
	lh->mapSize = (mape - map);
	lh->mapMode = tileMode;
}

void dummyLoad(){


	consoleInitText(2, 2, &snesfont);

	//consoleSetTextCol(RGB15(26,2,2), RGB15(0,0,0));

	setLevel(&TestBg1, &patterns, &patterns_end, &palette, &palette_end, &map, &map_end, SC_64x64);
	setLevel(&TestBg2, &lvl2gfx, &lvl2gfx_end, &lvl2pal, &lvl2pal_end, &lvl2map, &lvl2map_end, SC_64x64);
	BG_Load(BG_P1_HW_LAYER, &TestBg1, BG_TILE_ADDR1, BG_MAP_ADDR1, 0);
	BG_Load(BG_P2_HW_LAYER, &TestBg2, BG_TILE_ADDR2, BG_MAP_ADDR2, 1);

	setMode(BG_MODE1,BG3_MODE1_PRORITY_HIGH); //bgSetDisable(1);

	//bgSetWindowsRegions(BG_P1_HW_LAYER, BG_P1_HW_LAYER, 0x00, 0x80);

	REG_W12SEL = 0x23;//set bg 1 and 3 inside window 1, 2 and 4 in window 2

	//window 1 position
    REG_WH0 = 0x00;
    REG_WH1 = 0x80;

    //window 2 position
    REG_WH2 = 0x80;
    REG_WH3 = 0xF0;

    //these probably select what objects can be seen in each window
    //haven't figured this out yet
	REG_WOBJSEL = 0x03;

    REG_WBGLOG = 0x01;
    REG_WOBJLOG = 0x01;

    //enable windowing for bg's 1 and 2
    REG_TMW = 0x03;

	// Set BG3 SubScreen and
	//bgSetEnableSub(2);

	setBrightness(0xF);
}
