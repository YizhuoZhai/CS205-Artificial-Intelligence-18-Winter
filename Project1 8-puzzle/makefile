main: main.o solver.o puzzle.o
	g++ main.o solver.o puzzle.o -o main

main.o: main.cpp solver.h ioinfo.h
	g++ -c main.cpp

solver.o: solver.h
	g++ -c solver.cpp

puzzle.o: puzzle.h
	g++ -c puzzle.cpp
clean:
	rm *.o
