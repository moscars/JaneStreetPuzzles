dice.o: dice.h dice.cpp
	g++-12 -std=c++20 -c dice.cpp

main.o: main.cpp
	g++-12 -std=c++20 -c main.cpp

main: main.o dice.o
	g++-12 -std=c++20 main.o dice.o -o main

runmain: main
	./main

clean:
	rm *.o main