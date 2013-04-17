/*---------------------------------------------------------------------------------
*
*	Death Match game for #palib mini compo by Team BAG
*
*		Authors: BassAceGold, ARM9, GEMISIS
*		Created: April 15 2013
*
---------------------------------------------------------------------------------*/
#include "main.h"

//#define fix_char(chr) (chr+(chr&1))

//---------------------------------------------------------------------------------
int main(void) {
	static u16 x = 2<<5, y = 2<<5;

	Player_s *player1;
	Player_s *player2;

	player1->x = 2<<4;
	player1->y = 2<<5;
	player1->health = 100;

	player2->x = 2<<3;
	player2->y = 2<<3;
	player2->health = 100;

	u8 players = 1;

	consoleInit();

	dummyLoad();
	dummySprites();

	//98-148 A-Z
	//162-212 a-z 
	char pahello[8] = "(pjxx ^";
	pahello[5] = 0x7E;
	char shiz[27] = "bdfhjlnprtvxzBDFHJLNPR\0";

	//shiz[2] = fix_char('a');

	bgSetScroll(BG_P1_HW_LAYER, player1->x, player1->y);
	bgSetScroll(BG_P2_HW_LAYER, x, y);

	//consoleDrawText(0, 1, shiz);
	//consoleDrawText(25, 27, pahello);

	setFadeEffect(2);

	WaitForVBlank();
	//setModeHdmaGradient(31);
	while(1) {
		//WaitVBLFlag;

		//consoleSetTextCol(RGB15(31&player1->x,31&player1->y,4), RGB15(0,0,0));

		scanPads();

		pad0 = padsCurrent(0);

		if(pad0){

			if(pad0 & (KEY_A | KEY_X)){
				player1->health < 254 ? ++player1->health : player1->health = 255;
			}else if(pad0 & (KEY_B | KEY_Y)){
				player1->health > 0 ? --player1->health : player1->health = 0;
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
				--player1->y;
				if(player1->y < 1){
					player1->y = 1;
				}
			}else if(pad0 & KEY_DOWN){
				++player1->y;
			}

			if((pad0 & KEY_UP|KEY_DOWN) || (pad0 & KEY_RIGHT|KEY_LEFT)){
				oamSet(0, (player1->x)&0xFF, (player1->y)&0xFF, 3, 0, 0, 0, 0);
				//consoleDrawText(1, 26, "X = %d Y = %d ", player1->x, player1->y);
			}
		}

		if(players == 1){
			pad1 = padsCurrent(1);
			
			if(pad1){
				if(pad1 & KEY_RIGHT){
					++x;
				}else if(pad1 & KEY_LEFT){
					--x;
					if(x < 1){
						x = 1;
					}
				}

				if(pad1 & KEY_UP){
					--y;
					if(y < 1){
						y = 1;
					}
				}else if(pad1 & KEY_DOWN){
					++y;
				}
				if((pad0 & KEY_UP|KEY_DOWN) || (pad0 & KEY_RIGHT|KEY_LEFT)){
					oamSet(4, x&0xFF, y&0xFF, 3, 0, 0, 0, 0);
				}
			}
		}
		
		bgSetScroll(BG_P1_HW_LAYER, player1->x, player1->y);
		bgSetScroll(BG_P2_HW_LAYER, x, y);

		WaitForVBlank();
	}
	return 0;
}
