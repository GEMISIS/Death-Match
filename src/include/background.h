#pragma once

#include <snes.h>
#include "addr.h"
#include "assets.h"



//snes hardware layer the level will be drawn too
#define BG_P1_HW_LAYER 0
#define BG_P2_HW_LAYER 1

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
extern void BG_Load(u8 BG_HW_LAYER, static Gfx_s *lvlmap, u16 BG_TILE_ADDR, u16 BG_MAP_ADDR, u8 pal);

void dummyLoad();
