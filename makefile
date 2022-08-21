
ashell: main.o noncanmode.o IO.o
	g++ main.o noncanmode.o IO.o -o ashell

main.o: main.cpp
	g++ -c main.cpp

IO.o: IO.cpp main.h
	g++ -c IO.cpp

noncanmode.o: noncanmode.cpp main.h
	g++ -c noncanmode.cpp

clean: 
	rm *.o ashell
