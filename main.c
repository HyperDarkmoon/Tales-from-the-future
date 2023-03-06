#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    SDL_Surface *screen;
    int boucle = 1;
    SDL_Event event;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) == -1)
    {
        printf("Could not initialize SDL: %s.\n", SDL_GetError());
        return -1;
    }
    screen = SDL_SetVideoMode(800,600,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
    while (boucle)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                boucle = 0;
                break;
            }
        }
    }
}

