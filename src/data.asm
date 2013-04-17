.include "hdr.asm"

.section ".rodata1" superfree

lvl1gfx:
.incbin "lvl1.pic"
lvl1gfx_end:

lvl1map:
.incbin "lvl1.map"
lvl1map_end:

lvl1pal:
.incbin "lvl1.pal"
lvl1pal_end:

.ends

.section ".rodata2" superfree

lvl2gfx:
.incbin "lvl2.pic"
lvl2gfx_end:

lvl2map:
.incbin "lvl2.map"
lvl2map_end:

lvl2pal:
.incbin "lvl2.pal"
lvl2pal_end:

.ends

.section ".rodata3"

spritegfx:
.incbin "sprite.pic"
spritegfx_end:

spritepal:
.incbin "sprite.pal"

snesfont:
.incbin "palibfont.pic"
snesfont_end:

.ends
