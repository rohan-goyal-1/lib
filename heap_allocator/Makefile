CC = gcc
CFLAGS = -Wextra -std=c11

test:
	$(CC) $(CFLAGS) test.c allocator.c

.PHONY: run clean

run:
	@ ./a.out

clean:
	@ rm -rf a.out
