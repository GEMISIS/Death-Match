#pragma once

extern char patterns, patterns_end;
extern char palette, palette_end;
extern char map, map_end;

extern char gfxsprite, gfxsprite_end;
extern char palsprite;

extern char snesfont;

extern char lvl2gfx, lvl2gfx_end, lvl2pal, lvl2pal_end, lvl2map, lvl2map_end;


typedef struct {
	u8 tile;//tile dimension (e.g. SC_32x32)
	char *gfx, *pal, *map;
	u16 gfxSize, palSize, mapSize;
}Gfx_s;

