#set path to snesdev root and devkitsnes
include $(CURDIR)/../local.mk

#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

ifeq ($(strip $(DEVKIT65XX)),)
$(error "Please set DEVKIT65XX in your environment. export DEVKIT65XX=<path to>devkit65XX")
endif

include $(DEVKIT65XX)/snes_rules

#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# INCLUDES is a list of directories containing extra header files
#---------------------------------------------------------------------------------
PREVDIR		:=  $(realpath $(CURDIR)/..)
TARGET		:=	$(shell basename $(PREVDIR))
BUILD		:=  build
SOURCES		:=	.
INCLUDES	:=  include

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
CFLAGS	+=	$(INCLUDE)

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	:=	$(PVSNESLIB)
LIBOBJS +:= $(BUILD)/*.obj

export OUTPUT	:=	$(CURDIR)/$(TARGET)

CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.asm)))

#---------------------------------------------------------------------------------
export OFILES	:=	$(BINFILES:.bin=.obj) $(CFILES:.c=.obj) $(SFILES:.asm=.obj)

export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
					$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
					-I$(CURDIR)/$(BUILD)

GTITLE 		:= -ht"$(TARGET)"

.PHONY: bitmaps all

#---------------------------------------------------------------------------------
all	:	bitmaps $(OUTPUT).sfc
	$(SNTOOLS) -hi! $(GTITLE) $(TARGET).sfc

clean:
	@echo clean ...
	@rm -f $(OFILES) $(TARGET).sfc  *.pic *.pal *.map *.pc7 *.mp7

run:
	$(DEVKITSNES)/emulators/higan/higan-performance.exe $(OUTPUT).sfc
#--------------------------------------------------------------------------------
# --- gfx2snes options ---
# -gp	Output in packed pixel format
# -gs#	Size of image blocks in pixels (8|16|32|64) (should probably only use 8)
# --- Map options ---
# -m!	Exclude map from output
# -m	Convert the whole picture
# -m7	Convert the whole picture for mode 7 format
# -mc	Generate collision map only
# -mR!	No tile reduction (not advised)
# --- Palette options ---
# -p!	Exclude palette from output
# -pc#	The number of colors (4|16|128|256)
# -po#	The number of colors to output (0 to 256) to filename.pal
# -pe#	The palette entry to add to map tiles (0 to 16), exclusive entry is not required
# -pr	Rearrange palettes and preserve palette numbers in the tilemap
# --- File options ---
# -f[bmp|pcx|tga] convert a bmp or pcx file, test tga viability?
# --- Misc options ---
# -n	No border, not quite sure what this does but might as well use it for now
# -q	Quiet mode (no console output I presume, don't git push with this flag)
palibfont.pic: palibfont.bmp
	@echo convert font with no tile reduction ... $(notdir $@)
	$(GFXCONV) -gs8 -m! -mR! -p! -pc4 -po2 -pe0 -n $<

sprite.pic: sprite.bmp
	@echo convert bitmap ... $(notdir $@)
	$(GFXCONV) -gs8 -pc16 -po16 -pe2 -n $<

lvl1.pic: lvl1.bmp
	@echo convert background ... $(notdir $@)
	$(GFXCONV) -gs8 -m -pc16 -pe0 -pr -fbmp -n $<

lvl2.pic: lvl2.bmp
	@echo convert background ... $(notdir $@)
	$(GFXCONV) -gs8 -m -pc16 -pe0 -pr -fbmp -n $<

bitmaps : lvl1.pic lvl2.pic palibfont.pic sprite.pic

#---------------------------------------------------------------------------------
$(OUTPUT).sfc	: $(OFILES)
