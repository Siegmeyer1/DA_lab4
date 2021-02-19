all: solution

solution: solution.o preproc.o AD_search.o letter.o
	g++ -std=c++11 -O3 solution.o preproc.o AD_search.o letter.o -o solution

solution.o: solution.cpp
	g++ -std=c++11 -O3 -c solution.cpp

preproc.o: preproc.cpp
	g++ -std=c++11 -O3 -c preproc.cpp

AD_search.o: AD_search.cpp
	g++ -std=c++11 -O3 -c AD_search.cpp

letter.o: letter.cpp
	g++ -std=c++11 -O3 -c letter.cpp

clean:
	rm -rf *.o solution
