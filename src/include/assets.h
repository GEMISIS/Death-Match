#pragma once

extern char lvl1gfx, lvl1gfx_end;
extern char lvl1pal, lvl1pal_end;
extern char lvl1map, lvl1map_end;

extern char gfxsprite, gfxsprite_end;
extern char palsprite;

extern char snesfont;

extern char lvl2gfx, lvl2gfx_end, lvl2pal, lvl2pal_end, lvl2map, lvl2map_end;

typedef struct {
	u8 mapMode;//tile dimension (e.g. SC_32x32) /ARM9: should be u16?? bgInitMapSet (u8 bgNumber, u8 *mapSource, u16 mapSize, >u16 sizeMode<, u16 address)
	char *gfx, *pal, *map;
	u16 gfxSize, palSize, mapSize;
}Gfx_s;

