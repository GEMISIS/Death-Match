#include "main.h"
#include "background.h"

//grab the current layer the player is on
static char *bgGetLayer(BGPos_s *bg){
	return bg->curLevel->map[bg->layer];
}

//Draw a background at a given screen position for a players BGPos_s
void BG_Draw(u16 x, u16 y, u8 wd, u8 ht, BGPos_s *bg){
	//grab pointer to tiles needed
	//grab pointer to map needed
	//calculate map position to draw from using info->x, info->y
	//for each tile within range of info->x, info->y and info->x + wd, info->y + ht
	//draw to screen at tile position x and y
}


u8 BG_GetTile(u16 playerX, u16 playerY, BGPos_s *bg){
	//return a tile number based on players x and y coords
	//in relation to the map stored in bg
}
