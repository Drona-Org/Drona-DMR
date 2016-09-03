CFLAGS = -Wall -c
LFLAGS = -Wall

CC = g++

all : MotionPrimitives.o InputParser.o GenerateConstraints.o GenerateTrajectory.o Z3OutputParser.o Complan.o

MotionPrimitives.o : MotionPrimitives.h MotionPrimitives.cpp
	$(CC) $(CFLAGS) MotionPrimitives.cpp

InputParser.o : MotionPrimitives.h InputParser.h InputParser.cpp
	$(CC) $(CFLAGS) InputParser.cpp

GenerateConstraints.o : MotionPrimitives.h InputParser.h GenerateConstraints.h GenerateConstraints.h GenerateConstraints.cpp
	$(CC) $(CFLAGS) GenerateConstraints.cpp

GenerateTrajectory.o : MotionPrimitives.h InputParser.h GenerateConstraints.h GenerateTrajectory.h GenerateTrajectory.cpp
	$(CC) $(CFLAGS) GenerateTrajectory.cpp

Z3OutputParser.o : Z3OutputParser.h Z3OutputParser.cpp
	$(CC) $(CFLAGS) Z3OutputParser.cpp

Complan.o : MotionPrimitives.h InputParser.h GenerateConstraints.h GenerateTrajectory.h Z3OutputParser.h Complan.h Complan.cpp
	$(CC) $(CFLAGS) Complan.cpp


.PHONY: clean
clean :
	rm -f *.o
