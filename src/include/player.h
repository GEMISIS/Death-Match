#pragma once

#include <snes.h>

typedef struct {
	u16 x, y;
	u8 health, direction;
	u16 weapon;
	u8 ammo;
}Player_s;
