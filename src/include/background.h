#pragma once

#include <snes.h>
#include "addr.h"
#include "assets.h"


//snes hardware layer the level will be drawn too
#define BG_LAYER_LEVEL 1
#define BG_LAYER_TEXT  2

/*Background struct
	An instance of this struct will be required for
	each player.
*/
typedef struct {
	u16 width, height, mapMode;
	char *gfx, *pal, *map;
	u16 gfxSize, palSize, mapSize;
}Level_s;



extern void Level_Load(u8 levelId);
