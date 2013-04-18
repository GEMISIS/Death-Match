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
#define REG_VBLCOUNT    (*(vuint8*)0x4209)
static Player_s player1;
static Player_s player2;

static void customVBL()
{
    unsigned int tt=snes_vblank_count;
    unsigned int count = 0;

    while (tt == snes_vblank_count){
    	if(count < (192>>1))//figure out what value goes here
    	{
		    REG_WH0 = 0x00;//2126 //left x position
		    REG_WH1 = 0xFF;//2127 //to right x position
		    REG_WH2 = 0x00;//2126 //left x position
		    REG_WH3 = 0x00;//2127 //to right x position
    	} else
    	{
		    REG_WH2 = 0x00;//2126 //left x position
		    REG_WH3 = 0xFF;//2127 //to right x position
		    REG_WH0 = 0x00;//2126 //left x position
		    REG_WH1 = 0x00;//2127 //to right x position
    	}
    	++count;
    }
}
int main(void) {
	static u16 x = 2<<5, y = 2<<5;



	player1.x = 2<<4;
	player1.y = 2<<5;
	player1.health = 100;

	player2.x = 2<<3;
	player2.y = 2<<3;
	player2.health = 100;

	u8 players = 1;

	consoleInit();

	Level_Load(1);//load level 0
	DummySprites();
	UpdateSprite(0, player1.x & 0xFF, player1.y & 0xFF);
	UpdateSprite(1, x & 0xFF, y & 0xFF);

	//98-148 A-Z
	//162-212 a-z
	char pahello[8] = "(pjxx ^";
	pahello[5] = 0x7E;
	char stuffz[27] = "bdfhjlnprtvxzBDFHJLNPR\0";
	//max capacity for u8 array 0xD4, max capacity for u6 0x6A

	//stuffz[2] = fix_char('a');

	bgSetScroll(BG_P1_HW_LAYER, player1.x, player1.y);
	bgSetScroll(BG_P2_HW_LAYER, x, y);

	//consoleDrawText(0, 1, stuffz);
	//consoleDrawText(25, 27, pahello);

	//setFadeEffect(2);

	WaitForVBlank();
	u8 fading = 0;
	//setModeHdmaGradient(31);
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
				UpdateSprite(0, player1.x & 0xFF, player1.y & 0xFF);
				//oamSet(0, (player1->x)&0xFF, (player1->y)&0xFF, 3, 0, 0, 0, 0);
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
					UpdateSprite(1, x & 0xFF, y & 0xFF);
					//oamSet(4, x&0xFF, y&0xFF, 3, 0, 0, 0, 0);
				}
			}
		}

		bgSetScroll(BG_P1_HW_LAYER, player1.x, player1.y);
		bgSetScroll(BG_P2_HW_LAYER, x, y);
		customVBL();
		//WaitForVBlank();
	}
	return 0;
}
