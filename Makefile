CC = gcc
TARGET = build/pocgb
SRCS = src/main.c src/bus.c src/cpu.c
HEADERS = $(wildcard include/*.h)
CFLAGS = -std=c17 -Wall -Wextra -Iinclude
$(TARGET): $(SRCS) $(HEADERS) Makefile
	mkdir -p build
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

.PHONY: run
run: $(TARGET)
	./$(TARGET)
