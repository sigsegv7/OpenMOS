#
# Copyright (c) 2025, Ian Moffett.
# Provided under the BSD-3 clause.
#

CC =
LD =

SYS_CFLAGS =
ARCH =

.PHONY: all
all: arch

.PHONY: arch
arch:
	cd arch/$(ARCH); make CC=$(CC) LD=$(LD) SYS_CFLAGS="$(SYS_CFLAGS)"
