/*---------------------------------------------------------------------------------
*
*	Death Match game for #palib mini compo by: Team BAG
*		
*		Authors: BassAceGold, ARM9, GEMISIS
*		Created: April 15 2013
*
---------------------------------------------------------------------------------*/
#include "main.h"

extern char patterns, patterns_end;
extern char palette, palette_end;
extern char map, map_end;

//---------------------------------------------------------------------------------
int main(void) {
	static u16 x = 0, y = 0; //HACKY!!! don't use
	consoleInit();
	
	bgInitTileSet(0, &patterns, &palette, 0, (&patterns_end - &patterns), 16*2, BG_16COLORS, 0x1000);//HACKY!!! don't use
	
	bgInitMapSet(0, &map, (&map_end - &map), SC_32x32, 0x0000);//HACKY!!! don't use
	
	setMode(BG_MODE1, 0);
	//bgSetDisable(1);
	//bgSetDisable(2);
	
	setBrightness(0xF);
	
	while(1) {
		
		scanPads();
		
		pad0 = padsCurrent(0);
		
		if(pad0){
			if(pad0 & (KEY_A | KEY_X)){
			
			}else if(pad0 & (KEY_B | KEY_Y)){
			
			}
			
			if(pad0 & KEY_RIGHT){
				++x;
			}else if(pad0 & KEY_LEFT){
				--x;
			}
			
			if(pad0 & KEY_UP){
				--y;
			}else if(pad0 & KEY_DOWN){
				++y;
			}
		}
		bgSetScroll(0, x, y);
		WaitForVBlank();
	}
	return 0;
}
