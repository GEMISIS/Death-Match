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

/**** Jumpy screen tearing at screen split
***** Something in the nmi or customvbl code is messed up by joypad io, possibly the joypad enable flag,
***** presumably because that's in the same register as nmi, hcount and vcount enable
***** is non-maskable interrupt enabled? Check register $4200, write $80 to enable
from superfamicom.org
Notes: You should preserve most of your main registers in your NMI routine.
Also, you really shouldn't do anything not graphic-related, It's a waste of precious time.
VBLANK doesn't last forever, so you only have ample time to do what you need to do.
It's still plenty of time though, believe me.

Register $4210 is also of importance (I think):
Register $4210: NMI Register
x---vvvv:                       x: NMI V-BLANK flag
								v: Version # ($5A22 (seems irrelevant???))
Bit 7 can be reset to 0 by reading this register.
When "1" is written to "NMI enable" of register $4200, bit 7 will show NMI status.
Status is 0 for "NMI has not occurred" and 1 for "NMI has occurred".
ARM9 note: $4210 might be cleared by pvsneslib assembly or due to compiler on vblank: VBlank label in pvsneslib/source/crt0_snes.asm
*/
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
    		bgSetScroll(BG_LAYER_LEVEL, player2.x, player2.y-127); // offset depending on divider size
    	}
    }
}

static void nmiFun()
{

	consoleVblank();
	//push oam data to screen
	//dmaCopyOAram((unsigned char *) &oamMemory,0,0x220);

    // if buffer need to be update, do it !
    /*if (pvsneslibdirty == 1) {
            dmaCopyVram((unsigned char *) &pvsneslibfont_map, 0x800, 0x800);
            pvsneslibdirty = 0;
    }*/

	//snes_vblank_count++;
}

int main(void) {

	player1.x = 0;
	player1.y = 48;
	player1.health = 100;

	player2.x = 16;
	player2.y = 48;
	player2.health = 100;

	static u8 players = 1;

	consoleInit();

	//nmiSet(nmiFun);
	//REG_NMITIMEN = INT_VBLENABLE;
	
	Level_Load(1);//load level 0
	//sprites working again
	DummySprites();

	UpdateSprite(0, player1.x &0xFF, player1.y &0xFF);
	UpdateSprite(1, player2.x &0xFF, player2.y &0xFF);
	//UpdateSprite(2, 32, 96);

	//98-148 A-Z
	//162-212 a-z
	//char pahello[8] = "(pjxx ^";
	//pahello[5] = 0x7E;
	//char stuffz[27] = "bdfhjlnprtvxzBDFHJLNPR\0";
	//max capacity for u8 array 0xD4, max capacity for u6 0x6A

	//stuffz[2] = fix_char('a');

	//bgSetScroll(BG_LAYER_LEVEL, player1.x, player1.y);
	
	u8 fading = 0;
	static u8 f;
	while(1) {
		
		/*for(f = 0; f < 128; ++f){
				UpdateSprite(f, f, f);
			}*/

		if(fading<20){
			RealtimeFade(1, 0xF);
			++fading;
		}/*else if(fading<150){
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
				player1.health < 255 ? ++player1.health : player1.health = 255;
			}else if(pad0 & (KEY_B | KEY_Y)){
				player1.health > 0 ? --player1.health : player1.health = 0;
			}

			if(pad0 & KEY_RIGHT){
				++player1.x;
			}else if(pad0 & KEY_LEFT){
				if((player1.x < 1)==false){ // not using ! because of compiler bugs
					--player1.x;
				}
			}

			if(pad0 & KEY_UP){
				if((player1.y < 1)==false){
					--player1.y;
				}
			}else if(pad0 & KEY_DOWN){
				++player1.y;
			}

			if((pad0 & KEY_UP|KEY_DOWN) || (pad0 & KEY_RIGHT|KEY_LEFT)){
				UpdateSprite(0, (u8)player1.x, (u8)player1.y);
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
					if((player2.x < 1)==false){
						--player2.x;
					}
				}

				if(pad1 & KEY_UP){
					if((player2.y < 1==false)){
						--player2.y;
					}
				}else if(pad1 & KEY_DOWN){
					++player2.y;
				}
				if((pad0 & KEY_UP|KEY_DOWN) || (pad0 & KEY_RIGHT|KEY_LEFT)){
					UpdateSprite(1, (u8)player2.x, (u8)player2.y);
				}
			}
		}
		customVBL();
		//background positions updated here

	}
	return 0;
}
