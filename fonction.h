#ifndef FONCTION_H
#define FONCTION_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#define SCREEN_H 768
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


//fonctions image
void initialiser_imageBACK(image *imge);
void initialiser_imageBOUTON1(image *imge);
void initialiser_imageBOUTON2(image *imge);
void initialiser_imageBOUTON1_alt(image *imge);
void initialiser_imageBOUTON2_alt(image *imge);
void liberer_image(image imge);

//fonctions audio
void initialiser_audio(Mix_Music *music);
void liberer_musique(Mix_Music *music);
void initialiser_audiobref(Mix_Chunk *music);
void liberer_musiquebref(Mix_Chunk *music);

//fonctions texte
void initialiser_texte(texte *txte);
void afficher_texte(SDL_Surface *screen,texte txte);
void liberer_texte(texte txte);

//fonctions d'affichage
void afficher_imageBMP(SDL_Surface *screen,image imge);
void afficher_imageBTN1(SDL_Surface *screen,image imge);
void afficher_imageBTN1_alt(SDL_Surface *screen,image imge);
void afficher_imageBTN2(SDL_Surface *screen,image imge);



//Test
void PrintMousePosition(SDL_Surface *screen, TTF_Font *font, int x, int y);
#endif