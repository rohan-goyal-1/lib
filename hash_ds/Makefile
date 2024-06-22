CC = gcc
CFLAGS = -Wextra -std=c11
EXE_PATH = bin
EXE_NAME = $(EXE_PATH)/hash_tester

hash:
	@ mkdir -p $(EXE_PATH)
	$(CC) $(CFLAGS) src/test.c src/lib/*.c -o $(EXE_NAME)

.PHONY: run clean

run:
	@ ./$(EXE_NAME)

clean:
	@ rm -rf $(EXE_PATH)
