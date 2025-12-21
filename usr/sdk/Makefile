#
# Copyright (c) 2025, Ian Moffett.
# Provided under the BSD-3 clause.
#

CFILES = $(shell find common/ -name "*.c")
OFILES = $(CFILES:.c=.o)

CC =
LD =

ARCH =
SYS_CFLAGS =
CFLAGS = $(SYS_CFLAGS) -Iinc/

.PHONY: all
all: $(OFILES)
	$(AR) rcs libmos.a $(OFILES)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
