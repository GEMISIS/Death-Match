#pragma once

#include <snes.h>
#include "assets.h"

#define SPRITE_ADDR_TEMP 0x9000

typedef struct {
	char *gfx, *pal;
	u16 gfxSize;
	//u8 palSize; //palSize unused for now
	u16 x, y;
	u8 prio, id;
}Sprite_s;

extern static void setSprite(Sprite_s *spr, char *gfx, char *gfxe,
	char *pal);

extern static void Load_Sprite();

void dummySprites();
