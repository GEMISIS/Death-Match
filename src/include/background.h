#pragma once

#include <snes.h>
#include "assets.h"


#define BG_TILE_ADDR1 0x5000
#define BG_TILE_ADDR2 0x4000
#define BG_MAP_ADDR1  0x1400
#define BG_MAP_ADDR2  0x1800
//snes hardware layer the level will be drawn too
#define BG_P1_HW_LAYER 3
#define BG_P2_HW_LAYER 2

/*
declare backgrounds here:
*/
typedef struct {
	char gfx, gfxEnd, pal, map, mapEnd;
}Map_s;

//e.g.
//extern char mapgfx, mapgfx_end, mapgfx_pal;
//const Map_s groundMap {mapgfx, mapgfx_end, mapgfx_pal };


//map layers
enum { LAYER_GROUND, LAYER_SKY, LAYER_SPACE, LAYER_WATER };

/*Background struct
	An instance of this struct will be required for
	each player.
*/
typedef struct {
	//maps current scroll position
	u16 width, height;

	//points to the current map in use for the level
	//and its 4 layers
	Map_s *map[4];
}Level_s;


/*
Preparing Levels:
use const types to store in rom
*/
//const Level_s Level1 = {width, height, [&groundMap, &skyMap, &spaceMap, &waterMap]};


/*
Players background struct. Each player will have
one of these to keep track of their location on
the background, for proper screen drawing/collision
*/
typedef struct {
	//current map layer of player
	u8 layer;

	//map position based on players screen position
	u16 x, y;

	//pointer to the current level loaded
	Level_s *curLevel;
}BGPos_s;


extern void BG_Draw(u16 x, u16 y, u8 wd, u8 ht, BGPos_s *bg);
extern u16 BG_GetTile(u16 xPix, u16 yPix, BGPos_s *bg);

void dummyLoad();
