CC = gcc
CCFLAGS = -ansi -g -lm

PROGS := $(shell find . -maxdepth 1 -type f -name "*.c" -exec basename {} .c ';')

all: $(PROGS)

$(PROGS): %: %.c
	$(CC) $(CCFLAGS) -o $@ $<

clean:
	rm -rf $(PROGS)

.PHONY: clean
