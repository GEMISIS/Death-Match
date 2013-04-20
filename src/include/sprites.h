#pragma once

#include <snes.h>
#include "assets.h"
#include "addr.h"

#define TEMP_SPRITE1_PAL_ID 0

static char testFrames[12] = {0,2,4,6,8,10,12,14,32,34,36,38};

typedef struct {
	char *gfx, *pal;
	u16 gfxSize;
	u8 x, y;
	u8 hFlip, vFlip;
	u8 priority, gfxId, palId, size, visible;
	u8 currentFrame; // to be used for animation
}Sprite_s;

void UpdateSprite(u8 index, u8 x, u8 y);
void DummySprites();
