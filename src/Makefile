#     __ ____  _________
#    /_ \\\  \/   /|    \______
#   //   \\\     /|| D  /_    /.
#  //     \\\_  /.||    \ ___/.
# /___/\___\\__/. |__|\__\__.___  ___ 
#  ....  .......   ...||  _/_\  \////. 
#                     || |.| |\  ///.
#                     |__|.|_|///  \
#                      .... ./__/\__\
#                             ........
# Fixed Point Library
# according to
# ISO/IEC DTR 18037
#
# Version 0.0.5
# Maximilan Rosenblattl, Andreas Wolf 2004-10-12
# Targets:
#  lib         create library file
#  <none>,all  all of the above
#  clean       clean up
#

#-------------------------------------------------------------------------
# project specific things
#-------------------------------------------------------------------------

PROJNAME = avrfix

LIBNAME  = lib$(PROJNAME).a
OBJS     = smulskD.o smulskS.o sdivskD.o sdivskS.o countlssk.o roundskD.o roundskS.o mulkD.o mulkS.o lmullkD.o lmullkS.o divkD.o divkS.o ldivlkD.o ldivlkS.o roundkD.o roundkS.o roundlkD.o roundlkS.o countlsk.o sincosk.o lsincoslk.o lsincosk.o tankD.o tankS.o ltanlkD.o ltanlkS.o ltankD.o ltankS.o atan2k.o latan2lk.o sqrt.o cordicck.o cordichk.o logk.o lloglk.o cordiccsk.o cordichsk.o ssincossk.o

# target architecture
MCU	= atmega328p

#-------------------------------------------------------------------------
# macros for the tools
#-------------------------------------------------------------------------

# Tools
CC	= avr-gcc
AR = ar
AS	= avr-as
ASLD	= avr-gcc -x assembler
LD	= avr-ld
OBJCOPY = avr-objcopy
SRECSIZE = ./srecsize
toupper = $(subst z,Z,$(subst y,Y,$(subst x,X,$(subst w,W,$(subst v,V,$(subst u,U,$(subst t,T,$(subst s,S,$(subst r,R,$(subst q,Q,$(subst p,P,$(subst o,O,$(subst n,N,$(subst m,M,$(subst l,L,$(subst k,K,$(subst j,J,$(subst i,I,$(subst h,H,$(subst g,G,$(subst f,F,$(subst e,E,$(subst d,D,$(subst c,C,$(subst b,B,$(subst a,A,$(1)))))))))))))))))))))))))))

# Flags
CFLAGS  = -mmcu=$(MCU) -Wall -Os -ansi
LDFLAGS = -Wl,-Map=$*.map,-L=. -l$(PROJNAME)

#-------------------------------------------------------------------------
# the targets
#-------------------------------------------------------------------------
all: lib

lib: $(LIBNAME)

# library
$(LIBNAME): $(OBJS)
	$(AR) -rcsv $@ $(OBJS)
	rm -f *.o *.list

$(OBJS):	avrfix.c avrfix.h $(SRECSIZE)
	$(CC) $(CFLAGS) -D $(call toupper,$*) -Wa,-a=$*.list -c -o $@ avrfix.c
	$(OBJCOPY) -O srec $@ $*.srec
	$(SRECSIZE) $* < $*.srec >> sizes.txt
	rm $*.srec

$(SRECSIZE): srecsize.c
	gcc -o $(SRECSIZE) srecsize.c

clean:
	rm -f $(LIBNAME) $(OBJS) *.list sizes.txt $(subst .o,.size,$(OBJS))
