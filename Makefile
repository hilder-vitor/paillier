CC=g++

LIBS_FLAGS=-lgmpxx -lgmp

main: src/main.cpp src/Paillier.o
	g++ src/main.cpp src/Paillier.o $(LIBS_FLAGS) -o main
	rm src/Paillier.o

src/Paillier.o: src/Paillier.h src/Paillier.cpp
	g++ -c src/Paillier.cpp -o src/Paillier.o
