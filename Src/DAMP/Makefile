CFLAGS = -Wall -c
LFLAGS = -Wall

CC = g++

all : MotionPrimitives.o InputParser.o Astar.o Semplan.o


MotionPrimitives.o : MotionPrimitives.h MotionPrimitives.cpp
	$(CC) $(CFLAGS) MotionPrimitives.cpp

InputParser.o : MotionPrimitives.h InputParser.h InputParser.cpp
	$(CC) $(CFLAGS) InputParser.cpp

Astar.o : MotionPrimitives.h InputParser.h Astar.h Astar.cpp
	$(CC) $(CFLAGS) Astar.cpp

Semplan.o : Astar.h Semplan.h Semplan.cpp
	$(CC) $(CFLAGS) Semplan.cpp


.PHONY: clean
clean :
	rm -f *.o
