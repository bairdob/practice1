all:cat


cat:cat.o
	g++ -o cat cat.o


cat.o:cat.cpp
	g++ -c cat.cpp -std=c++11

clean:
	rm *.o cat 
