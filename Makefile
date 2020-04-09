CC = g++
EXEC = PlatformGame
FLAGS = -Wall -Werror -pedantic
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
STD = -std=c++17
S = src
O = obj
B = bin

all: $(O) $(B) $(O)/main.o
	$(CC) $(O)/*.o -o $(B)/$(EXEC) $(LIBS)

$(O)/main.o: $(O)/Game.o
	$(CC) $(S)/main.cpp -c -o $(O)/main.o $(STD) $(FLAGS)

$(O)/Game.o: $(O)/Window.o
	$(CC) $(S)/Game.cpp -c -o $(O)/Game.o $(STD) $(FLAGS)

$(O)/Window.o: $(O)/EventManager.o
	$(CC) $(S)/Window.cpp -c -o $(O)/Window.o $(STD) $(FLAGS)

$(O)/EventManager.o:
	$(CC) $(S)/EventManager.cpp -c -o $(O)/EventManager.o $(STD) $(FLAGS)

clean: $(O) $(B)
	rm -r $(O)
	rm -r $(B)

$(O):
	mkdir $(O)

$(B):
	mkdir $(B)
