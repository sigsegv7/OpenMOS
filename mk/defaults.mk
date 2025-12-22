#
# Copyright (c) 2025, Ian Moffett
# Provided under the BSD-3 clause.
#

BOOT_PROTO = limine
ARCH = x86_64
QEMU = qemu-system-$(ARCH)

CC = $(shell pwd)/var/cc/gcc/bin/$(ARCH)-pc-osmora-gcc
LD = $(shell pwd)/var/cc/toolchain/build-binutils/bin/$(ARCH)-pc-osmora-ld
AR = $(shell pwd)/var/cc/toolchain/build-binutils/bin/$(ARCH)-pc-osmora-ar

SYS_CFLAGS =			\
	-nostdlib			\
	-nostdinc			\
	-ffreestanding		\
	-fexceptions		\
	--std=gnu11			\
	-mcmodel=kernel		\
	-Wno-attributes

ifeq ($(ARCH),x86_64)
	SYS_CFLAGS += 		\
		-mno-sse		\
		-mno-sse2		\
		-mno-sse3		\
		-mno-avx		\
		-mno-avx2		\
		-mno-80387		\
		-mno-3dnow
endif
