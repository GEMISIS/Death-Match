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
	setSprite(&Link, &spritegfx, &spritegfx_end, &spritepal);
	Load_Sprite(&Link);

	//for testing vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
	oamInitGfxSet(&spritegfx, (&spritegfx_end - &spritegfx), &spritepal, 0, 0x0000, OBJ_SIZE32);

	oamSet(4, 64, 64, 3, 0, 0, 0, 0);
	oamSetEx(4, OBJ_SMALL, OBJ_SHOW);
	//for testing ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
}
