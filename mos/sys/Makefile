#
# Copyright (c) 2025, Ian Moffett.
# Provided under the BSD-3 clause.
#

CC =
LD =

SYS_CFLAGS =
ARCH =

.PHONY: all
all: kern arch

.PHONY: kern
kern:
	cd kern/; make CC=$(CC) LD=$(LD) SYS_CFLAGS="$(SYS_CFLAGS)"

.PHONY: arch
arch:
	cd arch/$(ARCH); make CC=$(CC) LD=$(LD) SYS_CFLAGS="$(SYS_CFLAGS)"
