#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "fonction.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// main function
int main(int argc, char const *argv[])
{
    SDL_Surface *screen;
    image IMAGE_BTN1, IMAGE_BTN2, IMAGE_BTN1_alt, IMAGE_BTN2_alt;
    image IMAGE_BTN3, IMAGE_BTN4, IMAGE_BTN3_alt, IMAGE_BTN4_alt;
    image IMAGE1, IMAGE2, IMAGE3, IMAGE4, IMAGE5, IMAGE6, IMAGE7, IMAGE8,IMGCREDITS; 
    image IMAGElevelOne;
    Mix_Music *music;
    Mix_Chunk *mus;
    texte txte;
    SDL_Event event;
    TTF_Font *font;
    TTF_Init();
    font = TTF_OpenFont("OpenSans-Bold.ttf", 100);
    int menu = 0;
    int mouseX = 0;
    int mouseY = 0;
    int boucle = 1;
    int sfxPlayed;
    int buttonOneHovered = 0; // 0 = normal, 1 = hovered (for button one)
                              // Initialization, if it fails program exits
    int buttonTwoHovered = 0; // same as button One but for button two
    int buttonThreeHovered = 0;
    int buttonFourHovered = 0;
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) == -1)
    {
        printf("Could not initialize SDL: %s.\n", SDL_GetError());
        return -1;
    }
    int fullscreen = 1;
    screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    // initialization function calls
    char buttonOne[25],buttonOneAlt[25],buttonTwo[25],buttonTwoAlt[25],buttonThree[25],buttonThreeAlt[25],buttonFour[25],buttonFourAlt[25];

    //Calling for the following function should include the image variable, x,y,h,w, and the image name
    initialiser_imageBOUTON(&IMAGE_BTN1,0,252,1112,200,"newgame.png");
    initialiser_imageBOUTON(&IMAGE_BTN2,0,204,112,200,"Settings.png");
    initialiser_imageBOUTON(&IMAGE_BTN3,0,160,112,200,"Credits.png");
    initialiser_imageBOUTON(&IMAGE_BTN4,0,112,112,200,"quit.png");
    initialiser_imageBOUTON(&IMAGE_BTN1_alt,0,252,200,112,"newgame_alt.png");
    initialiser_imageBOUTON(&IMAGE_BTN2_alt,0,204,112,200,"Settingsalt.png");
    initialiser_imageBOUTON(&IMAGE_BTN3_alt,0,160,112,200,"Creditsalt.png");
    initialiser_imageBOUTON(&IMAGE_BTN4_alt,0,112,112,200,"exitalt.png");
    initialiser_imageBACK(&IMAGE1,"bg1.png");
    initialiser_imageBACK(&IMAGE2,"bg2.png");
    initialiser_imageBACK(&IMAGE3,"bg3.png");
    initialiser_imageBACK(&IMAGE4,"bg4.png");
    initialiser_imageBACK(&IMAGE5,"bg5.png");
    initialiser_imageBACK(&IMAGE6,"bg6.png");
    initialiser_imageBACK(&IMAGE7,"bg7.png");
    initialiser_imageBACK(&IMAGE8,"bg8.png");
    initialiser_imageBACK(&IMGCREDITS,"credits.png");
    initialiser_levelOne(&IMAGElevelOne);
    //initialiser_audio(music);
    initialiser_texte(&txte);
    int frame = 0;
    // main loop
    while (boucle)
    {
        switch (menu) //Switch controls screen printings
        {
        case 0:
            //PrintMousePosition(screen, font, mouseX, mouseY); //These two lines show mouse positioning, commment if not needed
            //SDL_UpdateRect(screen, 0, 0, 0, 0); //Line two
            if (Mix_PlayingMusic() == 0) {
                initialiser_audio(music);
            }
            if (frame==9) {
                frame=0;
            }
            switch(frame) {
                case 1:
                    afficher_imageBMP(screen, IMAGE2);
                    SDL_Delay(100);
                    break;
                case 2:
                    afficher_imageBMP(screen, IMAGE3);
                    SDL_Delay(100);
                    break;
                case 3:
                    afficher_imageBMP(screen, IMAGE1);
                    SDL_Delay(100);
                    break;
                case 4:
                    afficher_imageBMP(screen, IMAGE4);
                    SDL_Delay(100);
                    break;
                case 5:
                    afficher_imageBMP(screen, IMAGE5);
                    SDL_Delay(100);
                    break;
                case 6:
                    afficher_imageBMP(screen, IMAGE6);
                    SDL_Delay(100);
                    break;
                case 7:
                    afficher_imageBMP(screen, IMAGE7);
                    SDL_Delay(100);
                    break;
                case 8:
                    afficher_imageBMP(screen, IMAGE8);
                    SDL_Delay(100);
                    break;
            }
            frame++;
            afficher_texte(screen, txte);
            if (buttonOneHovered == 0)
            {
                afficher_imageBTN(screen, IMAGE_BTN1);
            }
            else
            {
                afficher_imageBTN(screen, IMAGE_BTN1_alt);
            }
            if (buttonTwoHovered == 0)
            {
                afficher_imageBTN(screen, IMAGE_BTN2);
            }
            else
            {
                afficher_imageBTN(screen, IMAGE_BTN2_alt);
            }
            if (buttonThreeHovered == 0)
            {
                afficher_imageBTN(screen, IMAGE_BTN3);
            }
            else
            {
                afficher_imageBTN(screen, IMAGE_BTN3_alt);
            }
            if (buttonFourHovered == 0)
            {
                afficher_imageBTN(screen, IMAGE_BTN4);
            }
            else
            {
                afficher_imageBTN(screen, IMAGE_BTN4_alt);
            }

            // second loop, reads events
            while (SDL_PollEvent(&event))
            {
                // different options for menu
                switch (event.type)
                {
                case SDL_QUIT: // quits the game
                    boucle = 0;
                    break;
                case SDL_MOUSEBUTTONDOWN: // mouse click
                    if (event.button.button == SDL_BUTTON_LEFT &&
                        event.motion.y <= SCREEN_H - 48 && event.motion.y >= SCREEN_H - 73 &&
                        event.motion.x <= 98 && event.motion.x >= 25)
                    {
                        boucle = 0;
                    }
                    if (event.motion.y <= SCREEN_H - 189 &&
                        event.motion.y >= SCREEN_H - 195 &&
                        event.motion.x <= 175 && event.motion.x >= 20) {
                            menu = 1;
                    }
                    if (event.motion.y <= SCREEN_H - 132 &&
                        event.motion.y >= SCREEN_H - 152 &&
                        event.motion.x <= 175 && event.motion.x >= 20) {
                            menu = 2;
                    }
                    if (event.motion.y <= SCREEN_H - 98 &&
                        event.motion.y >= SCREEN_H - 112 &&
                        event.motion.x <= 175 && event.motion.x >= 20){
                            menu = 3;
                        }
                    // Mouse button clicks on specific regions, proceeds elsewhere
                    break;
                case SDL_MOUSEMOTION: // mouse moving
                    mouseX = event.motion.x;
                    mouseY = event.motion.y;
                    if (event.motion.y <= SCREEN_H - 189 &&
                        event.motion.y >= SCREEN_H - 195 &&
                        event.motion.x <= 175 && event.motion.x >= 20)
                    {
                        buttonOneHovered = 1;
                        if (sfxPlayed==0) { 
                            initialiser_audiobref(mus,"Hover.wav");
                            sfxPlayed=1;
                        }
                    }
                    else
                    {
                        sfxPlayed =0;
                        buttonOneHovered = 0;
                    }
                    if (event.motion.y <= SCREEN_H - 132 &&
                        event.motion.y >= SCREEN_H - 152 &&
                        event.motion.x <= 175 && event.motion.x >= 20)
                    {
                        buttonTwoHovered = 1;
                        if (sfxPlayed==0) { 
                            initialiser_audiobref(mus,"Hover.wav");
                            sfxPlayed=1;
                        }
                    }
                    else
                    {
                        sfxPlayed =0;
                        buttonTwoHovered = 0;
                    }
                    if (event.motion.y <= SCREEN_H - 98 &&
                        event.motion.y >= SCREEN_H - 112 &&
                        event.motion.x <= 175 && event.motion.x >= 20)
                    {
                        buttonThreeHovered = 1;
                        if (sfxPlayed==0) { 
                            initialiser_audiobref(mus,"Hover.wav");
                            sfxPlayed=1;
                        }
                    }
                    else
                    {
                        sfxPlayed =0;
                        buttonThreeHovered = 0;
                    }
                    if (event.motion.y <= SCREEN_H - 48 &&
                        event.motion.y >= SCREEN_H - 73 &&
                        event.motion.x <= 98 && event.motion.x >= 25)
                    {
                        buttonFourHovered = 1;
                        if (sfxPlayed==0) { 
                            initialiser_audiobref(mus,"Hover.wav");
                            sfxPlayed=1;
                        }
                    }
                    else
                    {
                        sfxPlayed =0;
                        buttonFourHovered = 0;
                    }
                    // mouse hovers over specific regions, plays sound
                    break;
                }
            }
            SDL_Flip(screen); // Updates the screen
            break;
            case 1:
                Mix_CloseAudio();
                afficher_imageBTN(screen,IMAGElevelOne);
                while(SDL_PollEvent(&event)) {
                    switch(event.type) {
                        case SDL_QUIT:
                            boucle = 0;
                            break;
                        case SDL_KEYDOWN:
                            switch(event.key.keysym.sym) {
                                case(SDLK_ESCAPE): 
                                    menu = 0;
                                    break;
                            }
                    }
                }
                SDL_Flip(screen);
            break;
            case 2:
                afficher_imageBMP(screen, IMAGE1);
                while(SDL_PollEvent(&event)) {
                    switch(event.type) {
                        case SDL_QUIT:
                            boucle = 0;
                            break;
                        case SDL_KEYDOWN:
                            switch(event.key.keysym.sym) {
                                case(SDLK_ESCAPE): 
                                    menu = 0;
                                    break;
                                case(SDLK_f):
                                    if (fullscreen == 0) {
                                        screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_FULLSCREEN | SDL_DOUBLEBUF);
                                        fullscreen = 1;
                                        SDL_Flip(screen);
                                    }
                                    if (fullscreen == 1) {
                                        screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                                        fullscreen = 0;
                                        SDL_Flip(screen);
                                    }
                                break;
                            }
                            break;
                    }
                case 3:
                Mix_CloseAudio();
                afficher_imageBMP(screen,IMGCREDITS);
                while(SDL_PollEvent(&event)) {
                    switch(event.type) {
                        case SDL_QUIT:
                            boucle = 0;
                            break;
                        case SDL_KEYDOWN:
                            switch(event.key.keysym.sym) {
                                case(SDLK_ESCAPE): 
                                    menu = 0;
                                    break;
                            }
                    }
                }
                SDL_Flip(screen);
                break;
                }
            SDL_Flip(screen);
            break;
        }
    }

    // free functions
    liberer_image(IMAGE1);
    liberer_image(IMAGE2);
    liberer_image(IMAGE3);
    liberer_image(IMAGE4);
    liberer_image(IMAGE5);
    liberer_image(IMAGE6);
    liberer_image(IMAGE7);
    liberer_image(IMAGE8);
    liberer_image(IMAGE_BTN1);
    liberer_image(IMAGE_BTN2);
    liberer_image(IMAGE_BTN3);
    liberer_image(IMAGE_BTN4);
    liberer_image(IMAGE_BTN1_alt);
    liberer_image(IMAGE_BTN2_alt);
    liberer_image(IMAGE_BTN3_alt);
    liberer_image(IMAGE_BTN4_alt);
    liberer_image(IMGCREDITS);
    //liberer_musique(music);
    //liberer_musiquebref(mus);

    liberer_texte(txte);

    SDL_Quit();

    return 0;
}
