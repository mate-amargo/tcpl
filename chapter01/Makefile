CC = gcc
CCFLAGS = -ansi -g

PROGS := $(shell find . -type f -name "*.c" -exec basename {} .c ';')

all: $(PROGS)

$(PROGS): %: %.c
	$(CC) $(CCFLAGS) -o $@ $<

clean:
	rm -rf $(PROGS)

.PHONY: clean
