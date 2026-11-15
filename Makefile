CC = gcc
TARGET = build/pocgb
SRCS = src/main.c
CFLAGS = -std=c17 -Wall -Wextra -Iinclude
build/pocgb: src/main.c
	mkdir -p build
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

run: build/pocgb
	./$(TARGET)