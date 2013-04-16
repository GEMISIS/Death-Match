#pragma once

extern char patterns, patterns_end;
extern char palette, palette_end;
extern char map, map_end;

extern char gfxsprite, gfxsprite_end;
extern char palsprite;

extern char snesfont;


typedef struct {
	char *gfx, *pal, *map;
	u16 gfxSize, palSize, mapSize;
}Gfx_s;

