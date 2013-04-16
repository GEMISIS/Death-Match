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
	//static u16 x = 0, y = 0;
	Player_s player1;//, player2;
	
	player1.x = 0;
	player1.y = 0;
	player1.health = 100;
	
	players = 0;
	
	dummyLoad();
	
	//bgSetDisable(2);
	consoleDrawText(1, 4, "Errmagerrd");
	
	setFadeEffect(2);
	
	WaitForVBlank();
	
	while(1) {
		consoleDrawText(1, 1, "HP: %d ", player1.health);
		consoleDrawText(1, 22, "X = %d Y = %d ", player1.x, player1.y);
		
		WaitVBLFlag;
		//WaitForVBlank();
		consoleSetTextCol(RGB15(31&player1.x,31&player1.y,4), RGB15(0,0,0));
		
		scanPads();
		
		pad0 = padsCurrent(0);
		
		if(pad0){
			if(pad0 & (KEY_A | KEY_X)){
				player1.health < 254 ? ++player1.health : player1.health = 255;
			}else if(pad0 & (KEY_B | KEY_Y)){
				player1.health > 0 ? --player1.health : player1.health = 0;
			}
		
			if(pad0 & KEY_RIGHT){
				++player1.x;
			}else if(pad0 & KEY_LEFT){
				--player1.x;
			}
		
			if(pad0 & KEY_UP){
				--player1.y;
			}else if(pad0 & KEY_DOWN){
				++player1.y;
			}
		}
		
		/*if(players==1){
			pads1 = padsCurrent(1);
			proccessInput(pad1, player2);
		}*/
		
		bgSetScroll(1, player1.x, player1.y);
		
		//WaitForVBlank();
	}
	return 0;
}
