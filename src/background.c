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
	bgSetGfxPtr(BG_P2_HW_LAYER, LEVEL_GFX_ADDR);

	WaitForVBlank();
	dmaCopyVram(lvlmap->map, LEVEL_MAP_ADDR, lvlmap->mapSize);
	//set map for both bg layers
	bgSetMapPtr(BG_P1_HW_LAYER, LEVEL_MAP_ADDR, lvlmap->mapMode);
	bgSetMapPtr(BG_P2_HW_LAYER, LEVEL_MAP_ADDR, lvlmap->mapMode);
}

static void initSplitScreen(void){
	//split screen with bg layers 1 and 2

	REG_W12SEL = 0x23;//set bg 1 and 3 inside window 1, 2 and 4 in window 2

	//window 1 position
    REG_WH0 = 0x00;
    REG_WH1 = 0x80;

    //window 2 position
    REG_WH2 = 0x80;
    REG_WH3 = 0x10;

    //these probably select what objects can be seen in each window
    //haven't figured this out yet
	REG_WOBJSEL = 0x03;

    REG_WBGLOG = 0x01;
    REG_WOBJLOG = 0x01;

    //enable windowing for bg's 1 and 2
    REG_TMW = 0x03;
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
	bgSetDisable(2); bgSetDisable(3);

	initSplitScreen();
	setBrightness(0xF);
}
