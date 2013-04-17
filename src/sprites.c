/***********************

TODO:

***********************/

#include "sprites.h"

static Sprite_s Link;

static u8 spriteCount = 0;

static void setSprite(Sprite_s *spr, char *gfx, char *gfxe,
	char *pal)
{
	spr->gfx = gfx;
	spr->gfxSize = (gfxe - gfx);
	spr->pal = pal;
	spr->id = spriteCount++;
}

static void Load_Sprite(Sprite_s *spr)
{
	oamInitGfxSet(spr->gfx, spr->gfxSize, spr->pal, 0, 0x0000, OBJ_SIZE32);

	oamSet(Link.id * 4, 32, 64, 3, 0, 0, 0, 0);
	oamSetEx(Link.id * 4, OBJ_SMALL, OBJ_SHOW);
}

void dummySprites()
{
	setSprite(&Link, &gfxsprite, &gfxsprite_end, &palsprite);
	Load_Sprite(&Link);

	//oamInitGfxSet(gfxsprite, (gfxsprite_end - gfxsprite), palsprite, 0, 0x0000, OBJ_SIZE32);

	//oamSet(0, 32, 64, 3, 0, 0, 0, 0);
	//oamSetEx(0, OBJ_SMALL, OBJ_SHOW);
}
