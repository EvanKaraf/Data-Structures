graphs: DisjointSetsImplementation.o GraphImplementation.o main.o menu.o PQImplementation.o StackImplementation.o
	gcc -o graphs DisjointSetsImplementation.o GraphImplementation.o main.o menu.o PQImplementation.o StackImplementation.o

DisjointSetsImplementation.o: DisjointSetsImplementation.c DisjointSetsInterface.h
	gcc -c DisjointSetsImplementation.c

GraphImplementation.o: GraphImplementation.c PQInterface.h StackInterface.h DisjointSetsInterface.h
	gcc -c GraphImplementation.c

main.o: main.c
	gcc -c main.c

menu.o: menu.c GraphsInterface.h
	gcc -c menu.c

PQImplementation.o: PQImplementation.c PQInterface.h
	gcc -c PQImplementation.c

StackImplementation.o: StackImplementation.c StackInterface.h
	gcc -c StackImplementation.c

clean:
	rm DisjointSetsImplementation.o GraphImplementation.o main.o menu.o PQImplementation.o StackImplementation.o
