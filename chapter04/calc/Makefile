CC = gcc
CCFLAGS = -ansi -g

rpc: main.c getop.c stack.c getch.c
	$(CC) $(CCFLAGS) -o $@ $^

clean:
	rm -rf rpc

.PHONY: clean
