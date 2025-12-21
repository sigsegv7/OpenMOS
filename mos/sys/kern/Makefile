#
# Copyright (c) 2025, Ian Moffett.
# Provided under the BSD-3 clause.
#

CFILES = $(shell find . -name "*.c")
OFILES = $(CFILES:.c=.o)

SYS_CFLAGS =
CFLAGS = 					\
	$(SYS_CFLAGS) 			\
	-I../../../usr/sdk/inc/ \
	-I../target/inc/

.PHONY: all
all: $(OFILES)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
