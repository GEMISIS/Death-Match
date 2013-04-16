#pragma once

#include <snes.h>

/*
declare backgrounds here:
e.g.
extern char mapgfx, mapgfx_end;
*/


enum {LAYER_GROUND, LAYER_SKY, LAYER_SPACE, LAYER_WATER}

/*Background struct
	An instance of this struct will be required for
	each player.
*/
typedef struct {
	//maps current scroll position
	u16 width, height;

	//points to the current maps in use for the level
	extern char *map[4];
}Level_s;


/*
Storing backgrounds
*/
//Background_s Level1 = {0, 0, 0, width, height, &groundMap, &skyMap, &spaceMap, &waterMap};




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

