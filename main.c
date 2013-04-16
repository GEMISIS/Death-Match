/*---------------------------------------------------------------------------------
*
*	Death Match game for #palib mini compo by: Team BAG
*		
*		Authors: BassAceGold, ARM9, GEMISIS
*		Created: April 15 2013
*
---------------------------------------------------------------------------------*/
#include "main.h"

//---------------------------------------------------------------------------------
int main(void) {
	
	consoleInit();

	setBrightness(0xF);
	
	while(1) {
		
		scanPads();
		
		pad0 = padsCurrent(0);
		
		if(pad0){
			if(pad0 & (KEY_A | KEY_X)){
			
			}else if(pad0 & (KEY_B | KEY_Y)){
			
			}
			
			if(pad0 & KEY_RIGHT){
			
			}else if(pad0 & KEY_LEFT){
			
			}
			
			if(pad0 & KEY_UP){
			
			}else if(pad0 & KEY_DOWN){
			
			}
		}
		
		WaitForVBlank();
	}
	return 0;
}
