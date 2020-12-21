all:cat


cat:cat.o
	g++ -o cat cat.o -std=c++1z


cat.o:cat.cpp
	g++ -c cat.cpp -std=c++1z

clean:
	rm *.o cat 
