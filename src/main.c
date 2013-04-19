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

static Player_s player1, player2;

//Custom VBL for handling split screen with backgrounds
static void customVBL()
{
    unsigned int tt=snes_vblank_count;
    unsigned int count = 0;

    //first update top screen
    bgSetScroll(BG_LAYER_LEVEL, player1.x, player1.y);
    while (tt == snes_vblank_count)
    {
    	if(++count == 231){//then update bottom
    		bgSetScroll(BG_LAYER_LEVEL, player2.x, player2.y);
    	}
    }

}

static void nmiFun()
{
	//push oam data to screen
	dmaCopyOAram((unsigned char *) &oamMemory,0,0x220);
	snes_vblank_count++;
}

int main(void) {

	player1.x = 2<<4;
	player1.y = 2<<5;
	player1.health = 100;

	player2.x = 2<<3;
	player2.y = 2<<6;
	player2.health = 100;

	u8 players = 1;

	consoleInit();


	nmiSet(nmiFun);
	REG_NMITIMEN = INT_VBLENABLE;

	Level_Load(1);//load level 0
	DummySprites();

	UpdateSprite(0, player1.x & 0xFF, player1.y & 0xFF);
	UpdateSprite(1, player2.x & 0xFF, player2.y & 0xFF);

	//98-148 A-Z
	//162-212 a-z
	//char pahello[8] = "(pjxx ^";
	//pahello[5] = 0x7E;
	//char stuffz[27] = "bdfhjlnprtvxzBDFHJLNPR\0";
	//max capacity for u8 array 0xD4, max capacity for u6 0x6A

	//stuffz[2] = fix_char('a');

	bgSetScroll(BG_LAYER_LEVEL, player1.x, player1.y);

	//consoleDrawText(0, 1, stuffz);
	//consoleDrawText(25, 27, pahello);

	//setFadeEffect(2);
	WaitForVBlank();
	//u8 fading = 0;
	while(1) {

		/*++fading;
		if(fading<60){
			RealtimeFade(1, 0xF);
		}else if(fading<150){
			RealtimeFade(0, 0x8);
		}else if(fading<180){
			RealtimeFade(0, 0x2);
		}else if(fading<230){
			RealtimeFade(1, 0xC);
		}else{
			RealtimeFade(0, 0x0);
		}*/

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
				if(player1.x < 1){
					player1.x = 1;
				}
			}

			if(pad0 & KEY_UP){
				--player1.y;
				if(player1.y < 1){
					player1.y = 1;
				}
			}else if(pad0 & KEY_DOWN){
				++player1.y;
			}

			if((pad0 & KEY_UP|KEY_DOWN) || (pad0 & KEY_RIGHT|KEY_LEFT)){
				UpdateSprite(0, player1.x, player1.y);
				//consoleDrawText(1, 26, "X = %d Y = %d ", player1->x, player1->y);
			}

			if(pad0 & KEY_R){
				Level_Load(1);//load level 1
			} else if (pad0 & KEY_L){
				Level_Load(0);//load level 0
			}
		}

		if(players == 1){
			pad1 = padsCurrent(1);

			if(pad1){
				if(pad1 & KEY_RIGHT){
					++player2.x;
				}else if(pad1 & KEY_LEFT){
					--player2.x;
					if(player2.x < 1){
						player2.x = 1;
					}
				}

				if(pad1 & KEY_UP){
					--player2.y;
					if(player2.y < 1){
						player2.y = 1;
					}
				}else if(pad1 & KEY_DOWN){
					++player2.y;
				}
				if((pad0 & KEY_UP|KEY_DOWN) || (pad0 & KEY_RIGHT|KEY_LEFT)){
					UpdateSprite(1, player2.x, player2.y);
				}
			}
		}

		//background positions updated here
		customVBL();
	}
	return 0;
}
