all: main.o bignum.o
	g++ -o a.out main.o bignum.o
main.o: main.cpp bignum.o
	g++ -c main.cpp
bignum.o: bignum.h bignum.cpp
	g++ -c bignum.cpp
clean:
	rm -rf *.o
