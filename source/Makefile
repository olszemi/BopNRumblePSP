TARGET = Bop
OBJS = main.o graphics.o framebuffer.o callback.o menu.o keys.o moveSelect.o timebnb.o mp3player.o sound.o printImage.o preloader.o stage.o bop.o dog.o kong.o

CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LIBS = -lpspgu -lpng -lz -lm -lmad -lpspaudiolib -lpspaudio -lpsppower
LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Bop N Rumble

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
