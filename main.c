#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <stdlib.h>
#include "entities.h"

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
    screen = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    Entity e;
    int isMoving = 0;
    init_entity(&e, 200, 200, 1, 1, 3, 3);
    init_idle_entity_animation(&e);
    init_entity_animation(&e);
    while (boucle)
    {
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
        print_entity(&e, screen, isMoving);
        update_entity_animation(&e, isMoving);
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                boucle = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_f:
                    if (isMoving == 1)
                        isMoving = 0;
                    else
                        isMoving = 1;
                    break;
                }

                break;
            }
        }
        SDL_Flip(screen);
    }
}
