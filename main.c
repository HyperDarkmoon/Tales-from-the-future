
#include "header.h"

int main() {
    SDL_Surface *screen = NULL;
    Background b,b1,b2;
    SDL_Event event;
    float lives = 3;
    SDL_Surface* heart = NULL;
    const char* paths[] = {"images/bg1.png", "images/bg2.png", "images/bg3.png", "images/bg4.png"};
    const int dx = 10; // position of the player
    int gameover=0;
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
    initBack(&b,screen,paths,4);
    initMusic("background_music.mp3");
    Mix_Music *bgMusic = Mix_LoadMUS("background_music.mp3");
    if (bgMusic == NULL) {
        printf("Unable to load music file: %s\n", Mix_GetError());
        Mix_CloseAudio();
        exit(1);
    }
    Mix_PlayMusic(bgMusic, -1);
    int done = 0;
    int playerX,playerY=10; // players position
    while (!done) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) { 
                 case SDL_QUIT:
                    done = 1;
                    break;
               
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            done = 1;
                            break;
                        case SDLK_s:
                            playSinglePlayer(screen,&b,paths);
                        case SDLK_q:
                            playMultiplayer(screen, &b1, &b2,paths);

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


