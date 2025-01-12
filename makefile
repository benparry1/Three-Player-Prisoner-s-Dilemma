play.x:	main.o PD.o
	g++ -std=c++11 main.o PD.o -o play.x
main.o: main.cpp
	g++ -std=c++11 -c main.cpp
PD.o: PD.cpp
	g++ -std=c++11 -c PD.cpp
clean:
	rm *.o play.x
