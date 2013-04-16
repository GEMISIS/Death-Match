#pragma once

#include <snes.h>
#include "assets.h"


#define BG_TILE_ADDR1 0x5000
//#define BG_TILE_ADDR2 0x4000
#define BG_MAP_ADDR1  0x4000
//#define BG_MAP_ADDR2  0x1800
//snes hardware layer the level will be drawn too
#define BG_P1_HW_LAYER 1
#define BG_P2_HW_LAYER 2

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
	Gfx_s *map[4];
}Level_s;

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
extern void BG_Load(u8 hwLayer, static Gfx_s *lvlmap);

void dummyLoad();
