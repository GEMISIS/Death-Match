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
#---------------------------------------------------------------------------------
palibfont.pic: palibfont.bmp
	@echo convert font with no tile reduction ... $(notdir $@)
	$(GFXCONV) -n -gs8 -po2 -pc16 -pe0 -mR! -m! -p! $<

sprite.pic: sprite.bmp
	@echo convert bitmap ... $(notdir $@)
	$(GFXCONV) -gs32 -pc16 -po16 -n -m! $<

lvl1.pic: lvl1.bmp
	@echo convert background ... $(notdir $@)
	$(GFXCONV) -pr -pc16 -n -gs8 -pe0 -fbmp -m $<

lvl2.pic: lvl2.bmp
	@echo convert background ... $(notdir $@)
	$(GFXCONV) -pr -pc16 -n -gs8 -pe1 -fbmp -m $<


bitmaps : lvl1.pic lvl2.pic palibfont.pic sprite.pic

#---------------------------------------------------------------------------------
$(OUTPUT).sfc	: $(OFILES)
