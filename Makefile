CC=g++
CFLAGS=--std=c++11 -lpthread -lncurses
default:
	@$(CC) -o main.exe main.cpp utils/UserInput.cpp printChar1.cpp printName1.cpp printChar2.cpp printName2.cpp printChar3.cpp printName3.cpp shootPlane.cpp $(CFLAGS)
run:
	@./main.exe
thread:
	@g++ -o thread.exe thread.cpp line/line.cpp utils/util.cpp utils/UserInput.cpp -lncurses --std=c++11 -lpthread

# CC=g++
# CFLAGS=-c -Wall -g -std=c++11
# LDFLAGS=-g -lm -lpthread -lncurses

# SOURCES=$(wildcard ./*.cpp) $(wildcard ./clipping/*.cpp) $(wildcard ./line/*.cpp) $(wildcard ./objects/*.cpp) $(wildcard ./point/*.cpp) $(wildcard ./polygon/*.cpp) $(wildcard ./utils/*.cpp)
# OBJECTS=$(SOURCES:.cpp=.o)
# MAIN=./main.cpp
# EXECUTABLE=./main.exe

# .PHONY: all bin clean

# all: bin

# bin: $(EXECUTABLE)

# $(EXECUTABLE): $(OBJECTS)
# 	mkdir -p bin
# 	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

# %.o: %.cpp
# 	$(CC) $(CFLAGS) $< -o $@

# clean:
# 	-rm $(OBJECTS)
# 	-rm $(EXECUTABLE)
