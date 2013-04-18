/***********************

TODO:

***********************/

#include "sprites.h"

static Sprite_s Link;

static u8 spriteCount = 0;

static void setSpriteData(u8 index, Sprite_s *spr, char *gfx, char *gfxe,
	char *pal)
{
	spr->gfx = gfx;
	spr->gfxSize = (gfxe - gfx);
	spr->pal = pal;
	spr->palId = index;
	spr->gfxId = index;
	spr->size = OBJ_SMALL;
	spr->hFlip = 0;
	spr->vFlip = 0;
	spr->prio = 3;
	spr->visible = OBJ_SHOW;
	spr->x = 0<<4;
	spr->y = 0<<5;
}

void updateSprite(u8 index, u16 x, u16 y)
{
	oamSet(index * 4, x, y, 3, 0, 0, index * 128, index);
}

static void loadSpriteData(Sprite_s *spr)
{
	oamInitGfxSet(spr->gfx, spr->gfxSize, spr->pal, spr->palId, SPRITE_ADDR_OFFSET + 0x1000 * spr->gfxId, OBJ_SIZE32);
	oamSet(spr->gfxId * 4, spr->x>>4, spr->y>>5, spr->prio, spr->vFlip, spr->hFlip, spr->gfxId * 0x60, spr->palId);
	oamSetEx(spr->gfxId * 4, spr->size, spr->visible);

	/*#define OAM_HI_TABLE_START 128*4
	u16 tempx, tempy;
    // Set low byte of x position and y position:
    unsigned char x_lo = (unsigned char)tempx;
    oamSetXY(spr->id,tempx,tempy);

    // Note that id isn't the OAM id, but a direct index into OAM shadow memory;
    // the result is that id/4 is the actual oam index, which is required for determining
    // the OAM high table position.
    unsigned char oam_id = (unsigned char)(spr->id >> 2);

    // Set highest bit of x position: Either at bit 0,2,4,6 depending on oam id,
    // as 4 oam entries are merged into one byte of the OAM high table.
    int bit_shift = 2*(oam_id % 4);
    int in_byte_position = 1 << bit_shift;
    int oam_high_table_pos = OAM_HI_TABLE_START + oam_id / 4;
    oamMemory[oam_high_table_pos] &= ~in_byte_position; // Clear current high bit of x
    oamMemory[oam_high_table_pos] |= (tempx>>8)<<bit_shift; // Fill in new high bit of x*/
}

void dummySprites()
{
	setSpriteData(0, &Link, &spritegfx, &spritegfx_end, &spritepal);
	Link.x = 32 << 4;
	Link.y = 32 << 5;
	loadSpriteData(&Link);
	WaitForVBlank();
	setSpriteData(1, &Link, &spritegfx, &spritegfx_end, &spritepal);
	Link.x = 128 << 4;
	Link.y = 64 << 5;
	loadSpriteData(&Link);
}
