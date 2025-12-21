#
# Copyright (c) 2025, Ian Moffett
# Provided under the BSD-3 clause.
#

ASMFILES = $(shell find . -name "*.S")
ASMOFILES = $(ASMFILES:.S=.S.o)
MISC_OFILES = $(shell find ../../ -name "*.o")

CFILES = $(shell find . -name "*.c")
OFILES = $(CFILES:.c=.o)

CC =
LD =

SYS_CFLAGS =
CFLAGS =                    	\
	-I../../target/inc/			\
	-I../../inc/				\
	-I../../../../usr/sdk/inc/	\
	$(SYS_CFLAGS)

LDFLAGS = -Tadmin/mos.lds
MOS_OUT = ../../sys.mos

.PHONY: all
all: $(OFILES) $(ASMOFILES)
	$(LD) $(LDFLAGS) $(MISC_OFILES) -o $(MOS_OUT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.S.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@
