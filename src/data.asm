.include "hdr.asm"

.section ".rodata1" superfree

patterns:
.incbin "lvl1.pic"
patterns_end:

.ends

.section ".rodata2" superfree
map:
.incbin "lvl1.map"
map_end:

palette:
.incbin "lvl1.pal"
palette_end:

.ends
