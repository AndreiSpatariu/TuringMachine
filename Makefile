all:

build: Main.c InputFunctions.c InputFunctions.h 
	gcc -g -w Main.c InputFunctions.c InputFunctions.h -o TemaAA

run: TemaAA
	./TemaAA

clean:
	rm TemaAA