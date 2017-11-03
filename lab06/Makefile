# mainFileName = lab6
# files = vector matrix Data
# allFiles = $(mainFileName) $(files)
# filesObj = $(addsuffix .o, $(allFiles))
# filesH = $(addsuffix .h, $(files))
#
#
# all: cleanExe $(mainFileName)
#
# # Execution
# $(mainFileName): $(filesObj)
# 	g++ $(CFLAGS) $^ -o $@
#
# # Compilation
# %.o: %.cpp $(filesH)
# 	g++ -c $< $(CFLAGS)
#
# # Utils
# clean:
# 	rm -f *.o $(mainFileName)
#
# cleanExe:
# 	rm -f $(mainFileName)


all: cleanExe lab6


lab6: lab6.o Data.o
	mpicc -g -Wall -o lab6 lab6.cpp
	# g++ $(CFLAGS) -fopenmp -o lab6 lab6.o Data.o

lab6.o: lab6.cpp vector.h matrix.h
	g++ $(CFLAGS) -c lab6.cpp

Data.o: Data.cpp vector.h matrix.h
	g++ $(CFLAGS) -c Data.cpp

cleanExe:
	rm -f lab6

clean:
	rm -f *.o lab6
