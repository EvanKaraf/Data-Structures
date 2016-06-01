hash: HashTableImplementation.o menu.o main.o
	gcc -o hash HashTableImplementation.o menu.o main.o

HashTableImplementation.o: HashTableImplementation.c HashTableTypes.h
	gcc -c HashTableImplementation.c

main.o: main.c HashTableTypes.h
	gcc -c main.c

menu.o: menu.c HashTableInterface.h
	gcc -c menu.c

clean:
	rm HashTableImplementation.o menu.o main.o
