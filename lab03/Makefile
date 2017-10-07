# Execution
lab3: lab3.o Data.o
	g++ $(CFLAGS) -o lab3 lab3.o Data.o -lpthread

lab3.o: lab3.cpp vector.h matrix.h
	g++ $(CFLAGS) -c lab3.cpp

Data.o: Data.cpp vector.h matrix.h
	g++ $(CFLAGS) -c Data.cpp

clean:
	rm -f *.o lab3
