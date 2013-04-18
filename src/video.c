#include "video.h"

/*realtimeFade(mode, rangeLow, rangeHigh)
	mode: 1 = in, 0 = out
	brightness: brightness to fade in/out to*/
extern void RealtimeFade(u8 mode, u8 brightness)
{
	static u8 level = 0;
	
	if(mode == 1){
		if(level<(brightness&0xF)){
			++level;
		}
	}else{
		if(level>brightness){
			--level;
		}
	}
	REG_INIDISP = level;
}


/*static void FlashScreen(u8 mode, u8 rangeLow, u8 rangeHigh){
	static u8 level = 0xF;
	static u8 in = 0;
	static u8 interval = 0;

	//nmiWait();
	interval = (interval + 1)&0xFF;
	if((~interval)|1){
	if(in == 1){
		if(++level>rangeHigh-1){
			in = 0;
		}
	}else{
		if(--level<rangeLow+1){
			in = 1;
		}
	}
	}
	level &= 0xF;
	REG_INIDISP = level;
}*/
