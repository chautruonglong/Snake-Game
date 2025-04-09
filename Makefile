build:
	clang++ -std=c++17 src/main.cpp \
		-I /Users/mclogan/Downloads/SFML-3.0.0/include \
		-L /Users/mclogan/Downloads/SFML-3.0.0/lib \
		-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio \
		-o snake

run:
	DYLD_LIBRARY_PATH=/Users/mclogan/Downloads/SFML-3.0.0/lib ./snake
