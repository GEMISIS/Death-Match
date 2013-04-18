#pragma once

#include <snes.h>
#include "assets.h"
#include "addr.h"

typedef struct {
	char *gfx, *pal;
	u16 gfxSize;
	u16 x, y;
	u8 hFlip, vFlip;
	u8 priority, gfxId, palId, size, visible;
}Sprite_s;

void updateSprite(u8 index, u16 x, u16 y);
void dummySprites();
