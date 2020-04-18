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

$(O)/Game.o: $(O)/Window.o $(O)/StateManager.o
	$(CC) $(S)/Game.cpp -c -o $(O)/Game.o $(STD) $(FLAGS)

$(O)/StateManager.o: $(O)/State_Intro.o $(O)/State_MainMenu.o $(O)/State_Settings.o $(O)/State_Credits.o $(O)/State_LevelMenu.o $(O)/State_Platform.o $(O)/State_Pause.o
	$(CC) $(S)/StateManager.cpp -c -o $(O)/StateManager.o $(STD) $(FLAGS)

$(O)/State_Pause.o: $(O)/EventManager.o
	$(CC) $(S)/State_Pause.cpp -c -o $(O)/State_Pause.o $(STD) $(FLAGS)

$(O)/State_Platform.o: $(O)/EventManager.o $(O)/Board.o $(O)/Player.o
	$(CC) $(S)/State_Platform.cpp -c -o $(O)/State_Platform.o $(STD) $(FLAGS)

$(O)/Player.o: $(O)/Collider.o
	$(CC) $(S)/Player.cpp -c -o $(O)/Player.o $(STD) $(FLAGS)

$(O)/Board.o: $(O)/Collider.o
	$(CC) $(S)/Board.cpp -c -o $(O)/Board.o $(STD) $(FLAGS)

$(O)/Collider.o:
	$(CC) $(S)/Collider.cpp -c -o $(O)/Collider.o $(STD) $(FLAGS)

$(O)/State_LevelMenu.o: $(O)/EventManager.o $(O)/Graph.o
	$(CC) $(S)/State_LevelMenu.cpp -c -o $(O)/State_LevelMenu.o $(STD) $(FLAGS)

$(O)/Graph.o:
	$(CC) $(S)/Graph.cpp -c -o $(O)/Graph.o $(STD) $(FLAGS)

$(O)/State_Credits.o: $(O)/EventManager.o
	$(CC) $(S)/State_Credits.cpp -c -o $(O)/State_Credits.o $(STD) $(FLAGS)

$(O)/State_Settings.o: $(O)/EventManager.o
	$(CC) $(S)/State_Settings.cpp -c -o $(O)/State_Settings.o $(STD) $(FLAGS)

$(O)/State_MainMenu.o: $(O)/EventManager.o
	$(CC) $(S)/State_MainMenu.cpp -c -o $(O)/State_MainMenu.o $(STD) $(FLAGS)

$(O)/State_Intro.o: $(O)/EventManager.o
	$(CC) $(S)/State_Intro.cpp -c -o $(O)/State_Intro.o $(STD) $(FLAGS)

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
