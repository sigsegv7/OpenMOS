#
# Copyright (c) 2025, Ian Moffett.
# Provided under the BSD-3 clause.
#

CC =
LD =

SYS_CFLAGS =
ARCH =

.PHONY: all
all: target kern arch

.PHONY: kern
kern:
	cd kern/; make CC=$(CC) LD=$(LD) SYS_CFLAGS="$(SYS_CFLAGS)" BOOT_PROTO=$(BOOT_PROTO)

.PHONY: arch
arch:
	cd arch/$(ARCH); make CC=$(CC) LD=$(LD) SYS_CFLAGS="$(SYS_CFLAGS)"

.PHONY: target
target:
	mkdir -p target/inc/md/
	rsync -avr inc/arch/$(ARCH)/* target/inc/md/

.PHONY: clean
clean:
	cd arch/$(ARCH); make clean
