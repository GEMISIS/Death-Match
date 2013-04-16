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
	Player_s *player1;//, player2;

	player1->x = 2<<8;
	player1->y = 2<<8;
	player1->health = 100;

	players = 0;

	consoleInit();

	dummySprites();
	dummyLoad();

	//bgSetDisable(0);

	consoleDrawText(1, 4, "Errmagerrd, text on BG3");
	consoleDrawText(1, 1, "HP: %d ", player1->health);
	consoleDrawText(1, 26, "X = %d Y = %d ", player1->x, player1->y);

	bgSetScroll(0, player1->x, player1->y);

	setFadeEffect(2);

	WaitForVBlank();
	//setModeHdmaGradient(31);
	while(1) {



		//WaitVBLFlag;

		consoleSetTextCol(RGB15(31&player1->x,31&player1->y,4), RGB15(0,0,0));

		scanPads();

		pad0 = padsCurrent(0);

		if(pad0){

			if(pad0 & (KEY_A | KEY_X)){
				player1->health < 254 ? ++player1->health : player1->health = 255;
				consoleDrawText(1, 1, "HP: %d ", player1->health);
			}else if(pad0 & (KEY_B | KEY_Y)){
				player1->health > 0 ? --player1->health : player1->health = 0;
				consoleDrawText(1, 1, "HP: %d ", player1->health);
			}

			if(pad0 & KEY_RIGHT){
				++player1->x;
			}else if(pad0 & KEY_LEFT){
				--player1->x;
				if(player1->x < 1){
					player1->x = 1;
				}
			}

			if(pad0 & KEY_UP){
				player1->y--;
				if(player1->y < 1){
					player1->y = 1;
				}
			}else if(pad0 & KEY_DOWN){
				player1->y++;
			}

			if((pad0 & KEY_UP|KEY_DOWN) || (pad0 & KEY_RIGHT|KEY_LEFT)){
				consoleDrawText(1, 26, "X = %d Y = %d ", player1->x, player1->y);
			}
		}

		/*if(players==1){
			pad1 = padsCurrent(1);
			proccessInput(pad1, player2);
		}*/
		WaitForVBlank();
		bgSetScroll(0, player1->x, player1->y);
		bgSetScroll(1, player1->x - 0x80, player1->y);

		//WaitForVBlank();
	}
	return 0;
}
