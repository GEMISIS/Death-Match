#pragma once

#include <snes.h>
#include "assets.h"
#include "addr.h"



typedef struct {
	char *gfx, *pal;
	u16 gfxSize;
	u16 x, y;
	u8 prio, id;
}Sprite_s;

extern static void setSprite(Sprite_s *spr, char *gfx, char *gfxe,
	char *pal);

extern static void Load_Sprite();

void dummySprites();
