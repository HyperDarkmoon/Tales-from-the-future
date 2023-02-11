#ifndef FONCTION_H
#define FONCTION_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#define SCREEN_H 770
#define SCREEN_W 1366

//Structure image
typedef struct {
    char *url;
    SDL_Rect pos_img_affiche;
    SDL_Rect pos_img_ecran;
    SDL_Surface *img;
}image;

//structure texte
typedef struct {
    SDL_Surface *txt;
    SDL_Rect pos_txt;
    SDL_Color color_txt;
    TTF_Font *police;
}texte;


//fonctions image*
void initialiser_imageBACK(image *imge,char* name);
void initialiser_imageBOUTON(image *imge, int x, int y, int h, int w, char *name);
void initialiser_levelOne(image *imge);
void liberer_image(image imge);

//fonctions audio
void initialiser_audio(Mix_Music *music);
void liberer_musique(Mix_Music *music);
int initialiser_audiobref(Mix_Chunk *music,char* filename);
void liberer_musiquebref(Mix_Chunk *music);
void increaseVolume(int *volume);
void decreaseVolume(int *volume);

//fonctions texte
void initialiser_texte(texte *txte);
void afficher_texte(SDL_Surface *screen,texte txte);
void liberer_texte(texte txte);

//fonctions d'affichage
void afficher_imageBMP(SDL_Surface *screen,image imge);
void afficher_imageBTN(SDL_Surface *screen,image imge);




//Test
void PrintMousePosition(SDL_Surface *screen, TTF_Font *font, int x, int y);
#endif