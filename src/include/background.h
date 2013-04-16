#pragma once

#include <snes.h>

/*
declare backgrounds here:
*/
typedef struct {
	char gfx, end, pal;
}Map_s;

//e.g.
//extern char mapgfx, mapgfx_end, mapgfx_pal;
//const Map_s groundMap {mapgfx, mapgfx_end, mapgfx_pal };


//map layers
enum {LAYER_GROUND, LAYER_SKY, LAYER_SPACE, LAYER_WATER};

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
Storing backgrounds
use const types to store in rom
*/
//const Background_s Level1 = {0, 0, 0, width, height, [&groundMap, &skyMap, &spaceMap, &waterMap]};


/*
Players background struct

*/
typedef struct {
	//current map layer of player
	u8 layer;

	//map position based on players screen position
	u16 x, y;

	//pointer to the current level loaded
	Level_s *curLevel;
}BGPos_s;

