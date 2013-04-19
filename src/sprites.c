/***********************

TODO:

***********************/

#include "sprites.h"

static Sprite_s Link;

static u8 spriteCount = 0;

static void setSpriteData(u8 index, u8 priority, Sprite_s* spr, char *gfx, char *gfxe,
	char *pal)
{
	spr->gfx = gfx;
	spr->gfxSize = (gfxe - gfx);
	spr->pal = pal;
	spr->palId = index; // need to change this so we can use fewer palettes such as spr->palId = palindex
	spr->gfxId = index;
	spr->size = OBJ_SMALL;
	spr->priority = priority;
	spr->visible = OBJ_SHOW;
	spr->x = 0<<4;
	spr->y = 0<<5;
	spr->hFlip = 0;
	spr->vFlip = 0;
}

void UpdateSprite(u8 index, u16 x, u16 y)
{
	u8 *ptrOam;
    ptrOam = (unsigned char *) oamMemory;
    ptrOam = ptrOam + (index << 2);
	*ptrOam++ = (x);
	*ptrOam++ = (y);
}

static void loadSpriteData(Sprite_s* spr)
{	// spr->gfxId<<value   value needs to be based on sprite size
	//                                              v-- this is the spr->palId
	oamInitGfxSet(spr->gfx, spr->gfxSize, spr->pal, 0, SPRITE_ADDR_OFFSET + (spr->gfxId<<9), OBJ_SIZE32);//old spr->gfxId<<12
	oamSet((spr->gfxId<<2), spr->x>>4, spr->y>>5, spr->priority, spr->vFlip, spr->hFlip, (spr->gfxId<<2), 0);//last parameter here is spr->palId. old spr->gfxId<<7
	oamSetEx((spr->gfxId<<2), spr->size, spr->visible);
}

void DummySprites()
{
	setSpriteData(0, 3, &Link, &spritegfx, &spritegfx_end, &spritepal);
	Link.x = 32 << 4;
	Link.y = 32 << 5;
	loadSpriteData(&Link);
	WaitForVBlank();

	setSpriteData(1, 3, &Link, &spritegfx, &spritegfx_end, &spritepal);
	Link.x = 128 << 4;
	Link.y = 64 << 5;
	loadSpriteData(&Link);
	WaitForVBlank();

	setSpriteData(2, 3, &Link, &spritegfx, &spritegfx_end, &spritepal);
	Link.x = 128 << 4;
	Link.y = 64 << 5;
	loadSpriteData(&Link);
	WaitForVBlank();
}
