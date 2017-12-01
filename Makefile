CC=g++ -std=c++0x

LIBS_FLAGS=-lgmpxx -lgmp -O3

main: src/main.cpp src/Paillier.o
	$(CC) src/main.cpp src/Paillier.o $(LIBS_FLAGS) -o main
	rm src/Paillier.o

src/Paillier.o: src/Paillier.h src/Paillier.cpp
	$(CC) -c src/Paillier.cpp -o src/Paillier.o
