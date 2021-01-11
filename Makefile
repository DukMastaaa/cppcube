main: makeobj/main.o makeobj/colours.o makeobj/cubes.o makeobj/cubeView.o makeobj/scrambler.o
	g++ makeobj/main.o makeobj/colours.o makeobj/cubes.o makeobj/cubeView.o makeobj/scrambler.o -lncurses -o main

makeobj/main.o: main.cpp
	g++ -c main.cpp
	mkdir -p makeobj; mv main.o makeobj

makeobj/colours.o: colours.cpp colours.h
	g++ -c colours.cpp
	mkdir -p makeobj; mv colours.o makeobj

makeobj/cubes.o: cubes.cpp cubes.h
	g++ -c cubes.cpp
	mkdir -p makeobj; mv cubes.o makeobj

makeobj/cubeView.o: cubeView.cpp cubeView.h
	g++ -c cubeView.cpp
	mkdir -p makeobj; mv cubeView.o makeobj

makeobj/scrambler.o: scrambler.cpp scrambler.h
	g++ -c scrambler.cpp
	mkdir -p makeobj; mv scrambler.o makeobj

clean:
	rm makeobj/*.o