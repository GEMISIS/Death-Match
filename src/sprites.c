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

	
	oamSet(spr->id * 4, 2<<4, 2<<5, 3, 0, 0, 0, 0);
	oamSetEx(spr->id * 4, OBJ_SMALL, OBJ_SHOW);
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
	setSprite(&Link, &spritegfx, &spritegfx_end, &spritepal);
	Load_Sprite(&Link);

	//for testing vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
	oamInitGfxSet(&spritegfx, (&spritegfx_end - &spritegfx), &spritepal, 0, SPRITE_ADDR_TEMP|0x0F0, OBJ_SIZE32);

	oamSet(4, 2<<5, 2<<5, 3, 0, 0, 0, 0);
	oamSetEx(4, OBJ_SMALL, OBJ_SHOW);
	//for testing ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
}
