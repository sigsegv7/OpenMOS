#
# Copyright (c) 2025, Ian Moffett.
# Provided under the BSD-3 clause.
#

CFILES = $(shell find . -name "*.c")
CFILES += $(shell find ../bpt -name "*.c")
OFILES = $(CFILES:.c=.o)

SYS_CFLAGS =
CFLAGS = 					\
	$(SYS_CFLAGS) 			\
	-I../../../usr/sdk/inc/ \
	-I../inc/				\
	-I../target/inc/		\
	-D_KERNEL				\
	-D_BOOT_PROTO="\"$(BOOT_PROTO)\""

.PHONY: all
all: $(OFILES)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
