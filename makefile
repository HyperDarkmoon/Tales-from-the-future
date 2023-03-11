prog: main.c es.c
	gcc main.c es.c -o prog -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf