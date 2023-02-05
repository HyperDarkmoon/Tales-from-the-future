prog: main.c fonction.c
	gcc main.c fonction.c settings.c -o prog -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf