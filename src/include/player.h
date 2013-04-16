#pragma once

#include <snes.h>

typedef struct{
	u16 x, y;
	u8 direction;
	u8 health;
	u8 weapon;
}Player_s;

/*
typedef struct _Bg_s{
	u16 scrollX, scrollY;
	u8 layer;
}Bg_s;
*/