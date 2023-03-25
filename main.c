
#include "header.h"

int main() {
    SDL_Surface *screen = NULL;
    Background b,b1,b2;
    SDL_Event event;
    const char path[30]="111.png";
    

    // Initialize SDL video
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1) {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    // Set up the screen
    screen = SDL_SetVideoMode(SCREEN_WIDTH , SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (screen == NULL) {
        printf("Unable to set video mode %s\n", SDL_GetError());
        exit(1);
    }

    // Initialize the background
    initBack(&b,screen,"111.png");
    initMusic("background_music.mp3");
    Mix_Music *bgMusic = Mix_LoadMUS("background_music.mp3");
    if (bgMusic == NULL) {
        printf("Unable to load music file: %s\n", Mix_GetError());
        Mix_CloseAudio();
        exit(1);
    }
    Mix_PlayMusic(bgMusic, -1);
    int done = 0;
    while (!done) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) { 
               
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                         case SDLK_ESCAPE:
                            done = 1;
                            break;
                        case SDLK_s:
                            animerBack(&b,&screen);
                            SDL_Flip(screen);
                            SDL_Delay(10);
                            break;
                        case SDLK_q:
                            
                            playMultiplayer(screen, &b1, &b2);
                            break;
                        default:
                            break;
                    }
                    default :
                        break;
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        SDL_FreeSurface(b.images[i]);
    }
    Mix_FreeMusic(bgMusic);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}


