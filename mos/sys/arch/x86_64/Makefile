#
# Copyright (c) 2025, Ian Moffett
# Provided under the BSD-3 clause.
#

ASMFILES = $(shell find . -name "*.S")
ASMOFILES = $(ASMFILES:.S=.S.o)
MISC_OFILES = $(shell find ../../ -name "*.o")

CC =
LD =

SYS_CFLAGS =
LDFLAGS = -Tadmin/mos.lds
MOS_OUT = ../../sys.mos

.PHONY: all
all: $(ASMOFILES)
	$(LD) $(LDFLAGS) $(MISC_OFILES) -o $(MOS_OUT)

%.S.o: %.S
	$(CC) $(SYS_CFLAGS) -c $< -o $@
