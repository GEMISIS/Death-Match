#include "background.h"


//Since we can only have one level loaded at a time, make it globally accessable
//reduces pointer usage too
static Level_s _currentLevel;


#define LEVEL1_DATA &lvl1gfx, &lvl1gfx_end, &lvl1pal, &lvl1pal_end, &lvl1map, &lvl1map_end
#define LEVEL2_DATA &lvl2gfx, &lvl2gfx_end, &lvl2pal, &lvl2pal_end, &lvl2map, &lvl2map_end

static void setLevel(char *gfx, char *gfxe,
	char *pal, char *pale, char *map, char *mape, u8 tileMode)
{
	_currentLevel.map.gfx = gfx;
	_currentLevel.map.gfxSize = (gfxe - gfx);
	_currentLevel.map.pal = pal;
	_currentLevel.map.palSize = (pale - pal);
	_currentLevel.map.map = map;//lol
	_currentLevel.map.mapSize = (mape - map);
	_currentLevel.map.mapMode = tileMode;
}



//Draw a background at a given screen position for a players BGPos_s
void BG_Draw(/*player info*/)
{
	//should update the scroll position of a background based
	//on a players x and y coordinates, and what hw layer they use.
}

//Given a pixel location on a map, returns the tile number in its location
//each tile is 8x8 pixels, hence the >>3
u16 BG_GetTile(u16 xPix, u16 yPix)
{
	Gfx_s *layer = &_currentLevel.map;
	u16 lvlWd = (_currentLevel.width)>>3;
	u16 *ptr = (u16 *) &layer->map + (yPix>>3)*lvlWd + (xPix>>3);
	return (*ptr);
}

//Moving away from generic code to more optimized specifics.
//Load a 16 color backgound on 2 hardware layers. Both bg's
//share the same tile, pal, and map data, but can be scrolled
//individually on their own hardware background layer.
static void levelToVram(void){
	Gfx_s *lvlmap = &_currentLevel.map;

	u16 palEntry = LEVEL_PAL_SLOT*BG_16COLORS;

    setBrightness(0);  // Force VBlank Interrupt
    WaitForVBlank();

    //copy tiles, palette and map to vram
	dmaCopyVram(lvlmap->gfx, LEVEL_GFX_ADDR, lvlmap->gfxSize);
	dmaCopyCGram(lvlmap->pal, palEntry, lvlmap->palSize);
	//set gfx for both bg layers
	bgSetGfxPtr(BG_P1_HW_LAYER, LEVEL_GFX_ADDR);
	//bgSetGfxPtr(BG_P2_HW_LAYER, LEVEL_GFX_ADDR);

	WaitForVBlank();
	dmaCopyVram(lvlmap->map, LEVEL_MAP_ADDR, lvlmap->mapSize);
	//set map for both bg layers
	bgSetMapPtr(BG_P1_HW_LAYER, LEVEL_MAP_ADDR, lvlmap->mapMode);
	//bgSetMapPtr(BG_P2_HW_LAYER, LEVEL_MAP_ADDR, lvlmap->mapMode);
}

void windowClipTop(u16 left, u16 right){
	REG_W12SEL = (1<<1) | (1<<0);
    REG_WH0 = left;//2126 //left x position
    REG_WH1 = right;//2127 //to right x position
    REG_WOBJSEL = (1<<1) | (1<<0);
	REG_WOBJLOG = 0;
    REG_TMW = (1<<4) | (1<<0) ; //bg 1 enable
}

void windowDisable(void){
	//REG_TMW = (1<<4) | (1<<0);
	REG_WOBJSEL = (1<<1);
}

static void initSplitScreen(void){
	//split screen with bg layers 1 and 2

	//REG_W34SEL = 0x00;//2124 same bits as W12SEL but for bg's 3 and 4
	REG_W12SEL = //bg 1
				 //(1<<3) | //enable window 2
				 //(1<<2) | //clip window 2 in or out
				 (1<<1) | //enable window 1
				 (1<<0) | //clip window 1 in or out
				 //bg 2
				 (1<<7) | //enable window 2
				 (1<<6);// | //clip window 2 in or out
				 //(1<<5)// | //enable window 1
				 //(1<<4) ; //clip window 1 in or out

	//window 1 position
    REG_WH0 = 0x00;//2126 //left x position
    REG_WH1 = 0x60;//2127 //to right x position

    //window 2 position
    REG_WH2 = 0x90;//2128 //left x position
    REG_WH3 = 0xFF;//2129 //to right x position

    //2125 //ccccssss - color, sprites
	REG_WOBJSEL =
				  (1<<7) | //A Enable window 2 for BG2/BG4/Color
				  //(1<<6) | //B Window 2 Inversion for BG2/BG4/Color
				  //(1<<5) | //C Enable window 1 for BG2/BG4/Color
				  //(1<<4) | //D Window 1 Inversion for BG2/BG4/Color
				  (1<<3) | //a Enable window 2 for BG1/BG3/OBJ
				  //(1<<2) | //b Window 2 Inversion for BG1/BG3/OBJ
				  (1<<1) ; //c Enable window 1 for BG1/BG3/OBJ
				  //(1<<0) ; //d Window 1 Inversion for BG1/BG3/OBJ


	//fiddling with these don't really produce much
	//212b (00 or, 10 xor, 01 and, 11 xnr)
	REG_WOBJLOG =
				  //(1<<7) | //?
				  //(1<<6) | //?
				  //(1<<5) | //?
				  //(1<<4) | //?
				  //(1<<3) | //color windows
				  //(1<<2) | //color windows
				  (1<<1) | //sprites
				  (1<<0) ; //sprites

	//212a (00 or, 10 xor, 01 and, 11 xnr)
    REG_WBGLOG = 0;
    			 //(1<<7) | //bg 4
    			 //(1<<6) | //bg 4
    			 //(1<<5) | //bg 3
    			 //(1<<4) | //bg 3
    			 //(1<<3) | //bg 2
    			 //(1<<2) | //bg 2
    			 //(1<<1) | //bg 1
    			 //(1<<0) ; //bg 1

    //212e - enable windowing for bg's 1 and 2
    REG_TMW = //(1<<7) | //unused
    		  //(1<<6) | //unused
    		  //(1<<5) | //unused
    		  (1<<4) | //sprites enable
    		  //(1<<3) | //bg 4 enable
    		  //(1<<2) | //bg 3 enable
    		  (1<<1) | //bg 2 enable
    		  (1<<0) ; //bg 1 enable
}


void Level_Load(u8 levelId)
{
	//consoleInitText(2, 2, &snesfont);

	//consoleSetTextCol(RGB15(26,2,2), RGB15(0,0,0));

	//set _currentLevel struct to the background we want to load
	switch(levelId){
		default:
			//could probably create a macro to shorten some of this
			setLevel(LEVEL1_DATA, SC_64x64);
		break;
		case 1:
			setLevel(LEVEL2_DATA, SC_64x64);
		break;
	}

	//load _currentLevel data to vram
	levelToVram();

	setMode(BG_MODE1, BG3_MODE1_PRORITY_HIGH); //
	bgSetDisable(1);bgSetDisable(2); bgSetDisable(3);

	setBrightness(0xF);
	//initSplitScreen();
}
