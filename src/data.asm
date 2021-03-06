.include "hdr.asm"

.section ".rodata1" superfree

lvl1gfx:
.incbin "resources/gfx/lvl1.pic"
lvl1gfx_end:

lvl1map:
.incbin "resources/gfx/lvl1.map"
lvl1map_end:

lvl1pal:
.incbin "resources/gfx/lvl1.pal"
lvl1pal_end:

.ends

.section ".rodata2" superfree

lvl2gfx:
.incbin "resources/gfx/lvl2.pic"
lvl2gfx_end:

lvl2map:
.incbin "resources/gfx/lvl2.map"
lvl2map_end:

lvl2pal:
.incbin "resources/gfx/lvl2.pal"
lvl2pal_end:

.ends

.section ".rodata3" superfree

spritegfx:
.incbin "resources/gfx/sprite.pic"
spritegfx_end:

spritepal:
.incbin "resources/gfx/sprite.pal"

testgfx:
.incbin "resources/gfx/mapicons.pic"
testgfx_end:

testpal:
.incbin "resources/gfx/mapicons.pal"

snesfont:
.incbin "resources/gfx/palibfont.pic"
snesfont_end:

.ends

.section ".rodata4" superfree

divgfx:
.incbin "resources/gfx/dividerw.pic"
divgfx_end:

divpal:
.incbin "resources/gfx/dividerw.pal"
;divpal_end:

.ends
