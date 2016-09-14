CC=g++

CXXFLAGS=-std=c++11
LIBS_FLAGS=-lgmpxx -lgmp

main: src/main.cpp src/Paillier.o
	g++ src/main.cpp src/Paillier.o $(CXXFLAGS) $(LIBS_FLAGS) -o main
	rm src/Paillier.o

src/Paillier.o: src/Paillier.h src/Paillier.cpp
	g++ -c src/Paillier.cpp -o src/Paillier.o $(CXXFLAGS)
