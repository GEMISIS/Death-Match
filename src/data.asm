.include "hdr.asm"

.section ".rodata1" superfree

patterns:
.incbin "lvl1.pic"
patterns_end:

map:
.incbin "lvl1.map"
map_end:

palette:
.incbin "lvl1.pal"
palette_end:

snesfont:
.incbin "palibfont.pic"
snesfont_end:

;.ends

;.section ".rodata2" superfree

gfxsprite:
.incbin "sprite.pic"
gfxsprite_end:

palsprite:
.incbin "sprite.pal"
;palsprite_end:

.ends