CC=g++
CFLAGS=--std=c++11
default:
	@$(CC) -o main.exe main.cpp point/point.cpp line/line.cpp polygon/polygon.cpp clipping/clip.cpp utils/util.cpp -lpthread $(CFLAGS)
run:
	@./main.exe
thread:
	@g++ -o thread.exe thread.cpp line/line.cpp utils/util.cpp utils/UserInput.cpp -lncurses --std=c++11 -lpthread
