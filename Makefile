build/pocgb: src/main.c
	mkdir -p build
	gcc src/main.c -o build/pocgb

run: build/pocgb
	./build/pocgb