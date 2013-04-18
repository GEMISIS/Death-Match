;==LoRom==      ; We'll get to HiRom some other time.

.MEMORYMAP                      ; Begin describing the system architecture.
  SLOTSIZE $8000                ; The slot is $8000 bytes in size. More details on slots later.
  DEFAULTSLOT 0                 ; There's only 1 slot in SNES, there are more in other consoles.
  SLOT 0 $8000                  ; Defines Slot 0's starting address.
  SLOT 1 $0 $2000
  SLOT 2 $2000 $E000
  SLOT 3 $0 $10000
.ENDME          ; End MemoryMap definition

.ROMBANKSIZE $8000              ; Every ROM bank is 32 KBytes in size
.ROMBANKS 8                     ; 2 Mbits - Tell WLA we want to use 8 ROM Banks, use power of 2

.SNESHEADER
  ID "SNES"                     ; 1-4 letter string, just leave it as "SNES"

  NAME "LIBSNES TEMPLATE     "  ; Program Title - can't be over 21 bytes,
  ;    sample name "123456789012345678901"  ; use spaces for unused bytes of the name.

  SLOWROM ; SLOWROM or FASTROM
  LOROM ; LOROM or HIROM, LOROM banks must be $8000 (32KB) and HIROM banks must be $10000 (64KB)

  CARTRIDGETYPE $00             ; $00 = ROM only, ; $00 ROM only, $01 ROM and RAM no sram, $02 ROM and sram. higher than $02 indicates special hardware addon in cartridge, must set rom layout properly, see line 21 and 22
  ; $00 to $0C RAM and ROM size. Values for RAM are $00 (no RAM) to $05 (32KB)
  ; $06 and $07 are apparently unused but are indicated as 64KB and 128KB respectively
  ; $08 to $0C ROM size, $08 is 256KB (minimum allowed ROM size by hardware) and $0C 4MB
  ROMSIZE $08                   ; $08 = 2 Mbits, $08 to $0C, 256KB to 4MB, MUST CHANGE LABELS .ROMBANKSIZE AND .ROMBANKS
  SRAMSIZE $00                  ; No SRAM         see WLA doc for more.. ; $01 to $05    bytes $06 and $07 are unused
  ;  country code $00 => Japanese, $01 => NTSC, $02 to $0c => PAL, $0d => NTSC
  COUNTRY $01                   ; $01 = U.S.  $00 = Japan, that's all I know
  LICENSEECODE $00              ; use $00
  VERSION $00                   ; $00 = 1.00, $01 = 1.01, etc.
.ENDSNES

; .COMPUTESNESCHECKSUM to make checksum, shall investigate

.SNESNATIVEVECTOR               ; Define Native Mode interrupt vector table
  COP EmptyHandler
  BRK EmptyHandler
  ABORT EmptyHandler
  NMI VBlank
  IRQ EmptyHandler
.ENDNATIVEVECTOR

.SNESEMUVECTOR                  ; Define Emulation Mode interrupt vector table
  COP EmptyHandler
  ABORT EmptyHandler
  NMI EmptyHandler
  RESET tcc__start                   ; where execution starts
  IRQBRK EmptyHandler
.ENDEMUVECTOR

