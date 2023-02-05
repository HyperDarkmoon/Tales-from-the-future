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
    image IMAGE, IMAGE_BTN1, IMAGE_BTN2, IMAGE_BTN1_alt, IMAGE_BTN2_alt;
    Mix_Music *music;
    Mix_Chunk *mus;
    texte txte;
    SDL_Event event;
    TTF_Font *font;
    TTF_Init();
    font = TTF_OpenFont("OpenSans-Bold.ttf", 100);
    int mouseX = 0;
    int mouseY = 0;
    int boucle = 1;
    int buttonOneHovered = 0; // 0 = normal, 1 = hovered (for button one)
                           // Initialization, if it fails program exits
    int buttonTwoHovered = 0; //same as button One but for button two
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
    initialiser_imageBOUTON2_alt(&IMAGE_BTN2_alt);
    initialiser_audio(music);
    initialiser_texte(&txte);

    // main loop
    while (boucle) {
        //PrintMousePosition(screen, font, mouseX, mouseY); //These two lines show mouse positioning, commment if not needed
        //SDL_UpdateRect(screen, 0, 0, 0, 0); //Line two
        afficher_imageBMP(screen, IMAGE);
        afficher_texte(screen, txte);
        if (buttonOneHovered == 0) {
            afficher_imageBTN1(screen, IMAGE_BTN1);
        }
        else {
            afficher_imageBTN1(screen, IMAGE_BTN1_alt);
        }
        if (buttonTwoHovered == 0) {
            afficher_imageBTN2(screen, IMAGE_BTN2);
        }
        else {
            afficher_imageBTN2(screen, IMAGE_BTN2_alt);
        }
        
        // second loop, reads events
        while (SDL_PollEvent(&event)) {
            // different options for menu
            switch (event.type) {
            case SDL_QUIT: // quits the game
                boucle = 0;
                break;
            case SDL_MOUSEBUTTONDOWN: // mouse click
                if (event.button.button == SDL_BUTTON_LEFT &&
                    event.motion.y <= SCREEN_H - 48 && event.motion.y >= SCREEN_H - 73 &&
                    event.motion.x <= 98 && event.motion.x >= 25) {
                    boucle = 0;
                }
                // Mouse button clicks on specific regions, proceeds elsewhere
                break;
            case SDL_MOUSEMOTION: // mouse moving
                mouseX = event.motion.x;
                mouseY = event.motion.y;
                if (event.motion.y <= SCREEN_H - 98 &&
                    event.motion.y >= SCREEN_H - 112 &&
                    event.motion.x <= 175 && event.motion.x >= 20) {
                    buttonOneHovered = 1;
                }
                else {
                    buttonOneHovered = 0;
                }
                 if (event.motion.y <= SCREEN_H - 48 &&
                    event.motion.y >= SCREEN_H - 73 &&
                    event.motion.x <= 98 && event.motion.x >= 25) {
                    buttonTwoHovered = 1;
                }
                else {
                    buttonTwoHovered = 0;
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
