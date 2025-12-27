#
# Copyright (c) 2025, Ian Moffett.
# Provided under the BSD-3 clause.
#

include mk/defaults.mk

.PHONY: all
all: sdk sys
	host/iso-limine

.PHONY: sys
sys:
	cd mos/sys/; make CC=$(CC) LD=$(LD) SYS_CFLAGS="$(SYS_CFLAGS)" ARCH=$(ARCH) BOOT_PROTO=$(BOOT_PROTO)

.PHONY: sdk
sdk:
	cd usr/sdk/; make CC=$(CC) LD=$(LD) AR=$(AR) SYS_CFLAGS="$(SYS_CFLAGS)" ARCH=$(ARCH)

.PHONY: run
run:
	$(QEMU) -cdrom live-mos.iso --enable-kvm -cpu host -m 2G -serial stdio

.PHONY: clean
clean:
	cd mos/sys/; make clean ARCH=$(ARCH)
