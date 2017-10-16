all: cleanExe lab5


lab5: lab5.o Data.o
	g++ $(CFLAGS) -fopenmp -o lab5 lab5.o Data.o

lab5.o: lab5.cpp vector.h matrix.h
	g++ $(CFLAGS) -fopenmp -c lab5.cpp

Data.o: Data.cpp vector.h matrix.h
	g++ $(CFLAGS) -fopenmp -c Data.cpp

cleanExe:
	rm -f lab5

clean:
	rm -f *.o lab5
