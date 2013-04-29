#include "background.h"


//Since we can only have one level loaded at a time, make it globally accessable
//reduces pointer usage too
static Level_s _currentLevel;

//size for a 32 x 32 map, or one screen full
static u8 infoBarMap[0x800];


#define LEVEL1_DATA &lvl1gfx, &lvl1gfx_end, &lvl1pal, &lvl1pal_end, &lvl1map, &lvl1map_end
#define LEVEL2_DATA &lvl2gfx, &lvl2gfx_end, &lvl2pal, &lvl2pal_end, &lvl2map, &lvl2map_end

static void setLevel(char *gfx, char *gfxe,
	char *pal, char *pale, char *map, char *mape, u16 tileMode)
{
	_currentLevel.gfx = gfx;
	_currentLevel.gfxSize = (gfxe - gfx);
	_currentLevel.pal = pal;
	_currentLevel.palSize = (pale - pal);
	_currentLevel.map = map;
	_currentLevel.mapSize = (mape - map);
	_currentLevel.mapMode = tileMode;
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
	u16 lvlWd = (_currentLevel.width)>>3;
	u16 *ptr = (u16 *) &_currentLevel.map + (yPix>>3)*lvlWd + (xPix>>3);
	return (*ptr);
}

//Load a background to BG_LAYER_LEVEL
static void levelToVram(void){

	u16 palEntry = (LEVEL_PAL_SLOT<<4);

    setBrightness(0);  // Force VBlank Interrupt
    //WaitForVBlank();

    //copy tiles, palette and map to vram
	dmaCopyVram(_currentLevel.gfx, LEVEL_GFX_ADDR, _currentLevel.gfxSize);
	dmaCopyCGram(_currentLevel.pal, palEntry, _currentLevel.palSize);
	//set gfx for both bg layers
	bgSetGfxPtr(BG_LAYER_LEVEL, LEVEL_GFX_ADDR);
	//WaitForVBlank();
	dmaCopyVram(_currentLevel.map, LEVEL_MAP_ADDR, _currentLevel.mapSize);
	bgSetMapPtr(BG_LAYER_LEVEL, LEVEL_MAP_ADDR, _currentLevel.mapMode);
}
/*
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
*/
static void loadInfoBar(void)
{
	//u16 palEntry = (BG_LAYER_TEXT<<5) + DIVIDER_PAL_SLOT* BG_4COLORS;
	u16 palEntry = (DIVIDER_PAL_SLOT<<4);
	setBrightness(0);

	dmaCopyVram(&divgfx, DIVIDER_GFX_ADDR, (&divgfx_end - &divgfx));
	dmaCopyCGram(&divpal, palEntry, (4<<1));//(&divpal_end - &divpal));
	//set gfx for both bg layers
	bgSetGfxPtr(BG_LAYER_TEXT, DIVIDER_GFX_ADDR);

	//set up divider map
	//tile format: vhopppcc cccccccc
	//vflip		(1<<15)
	//hflip		(1<<14)
	//priority  (1<<13)
	//pal4		(1<<12)
	//pal2		(1<<11)
	//pal1		(1<<10)

	//td512		(1<<9)
	//td256		(1<<8)
	//td128		(1<<7)
	//td64		(1<<6)
	//td32		(1<<5)
	//td16		(1<<4)
	//td8		(1<<3)
	//td4 		(1<<2)
	//td2 		(1<<1)
	//td1 		(1<<0)

	u16 *mapPtr = (u16*)&infoBarMap[0];
	u8 x = 0, y = 0;
	for (y = 0; y < 32; ++y)
	{
		for (x = 0; x < 32; ++x)
		{
			if ((y-1 > 11) && (y-1 < 16)) {
				//infoBarMap[x + ((y-1)<<5)] = 7;//(7);//(base_location_bits << 13) + (8 * color_depth * character_number);
				mapPtr[x + ((y-1)<<5)] = (1<<13) | (1<<10) | ((DIVIDER_GFX_ADDR-DIVIDER_MAP_ADDR)>>4) + (1);
			}
			/*else if (y-1 > 26){
				mapPtr[x + ((y-1)<<5)] = (1<<13) | (1<<10) | ((DIVIDER_GFX_ADDR-DIVIDER_MAP_ADDR)>>4) + (3);
			}*/
			//else{
			//	mapPtr[x + ((y-1)<<5)] = 0x0000;// | (1<<10);
			//}
		}
	}
	/*for (y = 0; y < 64; ++y)
	{
		for (x = 0; x < 64; ++x)
		{
			if ((y-1 > 23) && (y-1 < 32)) {
				infoBarMap[x + ((y-1)<<5)] = 0x27;//(7);//(base_location_bits << 13) + (8 * color_depth * character_number);
			}
			else if(y-1 > 62){
				infoBarMap[x + ((y-1)<<5)] = 0x27;
			}else{
				infoBarMap[x + ((y-1)<<5)] = 0;
			}
		}
	}*/

	//copy new map to vram
	dmaCopyVram(infoBarMap, DIVIDER_MAP_ADDR, 0x800);
	bgSetMapPtr(BG_LAYER_TEXT, DIVIDER_MAP_ADDR, SC_32x32);
}

void Level_Load(u8 levelId)
{


	//set _currentLevel struct to the background we want to load
	switch(levelId){
		default:
			setLevel(LEVEL1_DATA, SC_64x64);
		break;
		case 1:
			setLevel(LEVEL2_DATA, SC_64x64);
		break;
	}
	
	
	//load _currentLevel data to vram
	levelToVram();
	WaitForVBlank();

	loadInfoBar();
	WaitForVBlank();

	setMode(BG_MODE1, BG3_MODE1_PRORITY_HIGH);
	bgSetDisable(2);
	//bgSetDisable(2);
	bgSetDisable(3);
	//setBrightness(0xF);don't set brightness to non-zero anywhere but in main for now
}
