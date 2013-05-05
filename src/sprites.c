/***********************

TODO:

***********************/

#include "sprites.h"

static Sprite_s Link;

static u8 spriteCount = 0;

static void setSpriteData(u8 gfxid, u8 palid, u8 priority, Sprite_s* spr, char *gfx, char *gfxe,
	char *pal)
{
	spr->gfx = gfx;
	spr->gfxSize = (gfxe - gfx);
	spr->pal = pal;
	spr->gfxId = gfxid;
	spr->palId = palid; // need to change this so we can use fewer palettes such as spr->palId = palindex
	spr->size = OBJ_SMALL;
	spr->priority = priority;
	spr->visible = OBJ_SHOW;
	spr->x = 0;
	spr->y = 0;
	spr->hFlip = 0;
	spr->vFlip = 0;
	spr->currentFrame = 0;
}

static void oamSetXYEx(u16 id, u8 x, u8 y) { // DONT PASS SHIFTED ID TO THIS!
	#define OAM_HI_TABLE_START 128*4

	// Set low byte of x position and y position:
	unsigned char x_lo = (unsigned char)x;
	//oamSetXY(id,x,y);

	// Note that id isn't the OAM id, but a direct index into OAM shadow memory;
	// the result is that id/4 is the actual oam index, which is required for determining
	// the OAM high table position.
	unsigned char oam_id = (unsigned char)(id);//>>2

	// Set highest bit of x position: Either at bit 0,2,4,6 depending on oam id,
	// as 4 oam entries are merged into one byte of the OAM high table.
	int bit_shift = (oam_id & 3)<<1; // 2*(oam_id % 4);
	int in_byte_position = 1 << bit_shift;
	int oam_high_table_pos = OAM_HI_TABLE_START + (oam_id>>2); // (oam_id / 4);
	oamMemory[oam_high_table_pos] &= ~in_byte_position; // Clear current high bit of x
	oamMemory[oam_high_table_pos] |= (x>>8)<<bit_shift; // Fill in new high bit of x
}

void UpdateSprite(u8 index, u8 x, u8 y)
{
	u8 *ptrOam;
	ptrOam = (unsigned char *) oamMemory;
	ptrOam = ptrOam + (index<<2);
	*ptrOam++ = (x);
	*ptrOam++ = (y);
	//*ptrOam++ = frame;
	//*ptrOam++ = (gfxFrame); 
	//*ptrOam = (vflip<<7) | (hflip<<6) | (priority<<4) | (paletteoffset<<1) | ((gfxframe>>8) & 1);
}

static void loadSpriteData(Sprite_s* spr)
{//((spr->gfxId<<1)+((spr->gfxId<<7)&0x400))
	oamSet((spr->gfxId<<2), spr->x, spr->y, spr->priority, spr->vFlip, spr->hFlip, SPRITE1_ADDR_OFFSET + (testFrames[spr->gfxId&0xF]), spr->palId);//last parameter here is spr->palId. old spr->gfxId<<7
	oamSetEx((spr->gfxId<<2), spr->size, spr->visible);
	oamSetXYEx((spr->gfxId), spr->x, spr->y);
}

void DummySprites()
{
	setBrightness(0);
	setSpriteData(0, TEMP_SPRITE1_PAL_ID, 2, &Link, &testgfx, &testgfx_end, &testpal);
	dmaCopyCGram(&spritepal, 128+(1<<4), (16<<1)); //16 colors per palette, 2 bytes per color.
	oamInitGfxSet(Link.gfx, Link.gfxSize, Link.pal, Link.palId, SPRITE1_ADDR_OFFSET + (Link.gfxId), OBJ_SIZE16);
	
	u8 i, x = 0, y = 0;
	for(i = 0; i < 129; ++i){
		x=(i-1)&0xF;
		if(((i-1)&0xF) == 0){
			++y;
		}
		//Link.priority = (i-1)&3;
		Link.gfxId = (i-1);
		Link.palId = y&x&1;//;(i-1)&1;
		Link.x = (x<<4);
		Link.y = (y<<4)+32;//((i<<2)+0x10)&0xFF;
		loadSpriteData(&Link);
		//WaitForVBlank(); //Why was this necessary? Seemed to only slow things down
		//UpdateSprite(i, (x<<4)&0xFF, (y<<4)&0xFF);
	}
	i = 0;

	/*setSpriteData(1, 3, &Link, &spritegfx, &spritegfx_end, &testpal, 0);
	Link.x = 32;
	Link.y = 64;
	loadSpriteData(&Link, OBJ_SIZE16);
	WaitForVBlank();

	setSpriteData(2, 3, &Link, &testgfx, &testgfx_end, &spritepal, 1);
	Link.x = 32;
	Link.y = 96;
	loadSpriteData(&Link, OBJ_SIZE16);
	WaitForVBlank();*/
}

