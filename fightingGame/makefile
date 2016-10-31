game: main.o character.o game.o
	g++ main.o character.o game.o -o game -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

main.o: main.cpp
	g++ -c main.cpp
	
character.o: character.cpp
	g++ -c character.cpp
	
game.o: game.cpp
	g++ -c game.cpp
	
clean:
	rm *.o
	rm game