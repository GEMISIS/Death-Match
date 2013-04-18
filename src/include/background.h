#pragma once

#include <snes.h>
#include "addr.h"
#include "assets.h"


//snes hardware layer the level will be drawn too
#define BG_P1_HW_LAYER 0
#define BG_P2_HW_LAYER 1

/*Background struct
	An instance of this struct will be required for
	each player.
*/
typedef struct {
	//maps current scroll position
	u16 width, height;

	//points to the current map in use for the level
	//and its 4 layers
	Gfx_s map;
}Level_s;

extern void Level_Load(u8 levelId);
