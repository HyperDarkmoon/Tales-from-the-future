#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "fonction.h"
#include <stdio.h>
#include <stdlib.h>

// main function
int main(int argc, char const *argv[]) {
    SDL_Surface *screen;
    image IMAGE, IMAGE_BTN1, IMAGE_BTN2, IMAGE_BTN1_alt;
    Mix_Music *music;
    Mix_Chunk *mus;
    texte txte;
    SDL_Event event;
    int boucle = 1;
    int buttonHovered = 0; // 0 = normal, 1 = hovered
                           // Initialization, if it fails program exits
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) == -1) {
        printf("Could not initialize SDL: %s.\n", SDL_GetError());
        return -1;
    }
    screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);

    // initialization function calls
    initialiser_imageBACK(&IMAGE);
    initialiser_imageBOUTON1(&IMAGE_BTN1);
    initialiser_imageBOUTON2(&IMAGE_BTN2);
    initialiser_imageBOUTON1_alt(&IMAGE_BTN1_alt);
    initialiser_audio(music);
    initialiser_texte(&txte);

    // main loop
    while (boucle) {
        afficher_imageBMP(screen, IMAGE);
        afficher_texte(screen, txte);
        if (buttonHovered == 0) {
            afficher_imageBTN1(screen, IMAGE_BTN1);
        }
        else {
            afficher_imageBTN1(screen, IMAGE_BTN1_alt);
        }
        afficher_imageBTN2(screen, IMAGE_BTN2);

        // second loop, reads events
        while (SDL_PollEvent(&event)) {
            // different options for menu
            switch (event.type) {
            case SDL_QUIT: // quits the game
                boucle = 0;
                break;
            case SDL_MOUSEBUTTONDOWN: // mouse click
                if (event.button.button == SDL_BUTTON_LEFT &&
                    event.motion.y <= 300 && event.motion.y >= 250 &&
                    event.motion.x <= 423 && event.motion.x >= 213) {
                    boucle = 0;
                }
                // Mouse button clicks on specific regions, proceeds elsewhere
                break;
            case SDL_MOUSEMOTION: // mouse moving
                if (event.motion.y <= SCREEN_H - 112 &&
                    event.motion.y >= SCREEN_H - 160 &&
                    event.motion.x <= 200 && event.motion.x >= 0) {
                    buttonHovered = 1;
                }
                else {
                    buttonHovered = 0;
                }
                // mouse hovers over specific regions, plays sound
                break;
            }
        }
        SDL_Flip(screen); // Updates the screen
    }

    // free functions
    liberer_image(IMAGE);
    liberer_image(IMAGE_BTN1);
    liberer_image(IMAGE_BTN2);

    liberer_musique(music);
    liberer_musiquebref(mus);

    liberer_texte(txte);

    SDL_Quit();

    return 0;
}
