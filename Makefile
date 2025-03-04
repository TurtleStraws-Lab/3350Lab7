all: lab7

lab7: lab7.cpp
	g++ -Wall -o lab7 lab7.cpp

clean:
	rm -f lab7

