build:
	gcc -Wall -std=c99 ./src/*.c -lSDL2 -o game

run:
	./game

clean:
	rm game

# build-and-run:
# 	clean && make && make run

build-and-run: clean build run
