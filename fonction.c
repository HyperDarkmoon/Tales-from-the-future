#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "fonction.h"

// Initializes background image
void initialiser_imageBACK(image *imge,char* name)
{
    char link[50];
    strcpy(link,"imgs/");
    strcat(link,name);
    imge->url = (link);
    imge->img = IMG_Load(imge->url);
    if (imge->img == NULL)
    {
        printf("unable to load background image %s \n", SDL_GetError());
        return;
    }
    imge->pos_img_ecran.x = 0;
    imge->pos_img_ecran.y = 0;
    imge->pos_img_affiche.x = 0;
    imge->pos_img_affiche.y = 0;
    imge->pos_img_affiche.h = SCREEN_H;
    imge->pos_img_affiche.w = SCREEN_W;
}

void initialiser_levelOne(image *imge)
{
    imge->url = ("bgimgs/level1.jpg");
    imge->img = IMG_Load(imge->url);
    if (imge->img == NULL)
    {
        printf("unable to load background image %s \n", SDL_GetError());
        return;
    }
    imge->pos_img_ecran.x = 0;
    imge->pos_img_ecran.y = 0;
    imge->pos_img_affiche.x = 0;
    imge->pos_img_affiche.y = 0;
    imge->pos_img_affiche.h = SCREEN_H;
    imge->pos_img_affiche.w = SCREEN_W;
}

// Initializes All the buttons per parameter
void initialiser_imageBOUTON(image *imge, int x, int y, int h, int w, char *name)
{
    char link[50];
    strcpy(link,"imgs/");
    strcat(link,name);
    imge->url = (link); 
    imge->img = IMG_Load(imge->url);
    if (imge->img == NULL)
    {
        printf("unable to load background image %s \n", SDL_GetError());
        return;
    }
    imge->pos_img_ecran.x = x;
    imge->pos_img_ecran.y = SCREEN_H - y;
    imge->pos_img_affiche.w = h;
    imge->pos_img_affiche.h = w;
    imge->pos_img_affiche.x = x;
    imge->pos_img_affiche.y = SCREEN_H - y;
}

// Prints BMP image
void afficher_imageBMP(SDL_Surface *screen, image imge)
{
    SDL_BlitSurface(imge.img, &imge.pos_img_affiche, screen, &imge.pos_img_ecran);
}

// Prints first button
void afficher_imageBTN(SDL_Surface *screen, image imge)
{
    SDL_BlitSurface(imge.img, NULL, screen, &imge.pos_img_ecran);
}

// frees images from memory
void liberer_image(image imge)
{
    SDL_FreeSurface(imge.img);
}

// Initializes the audio files
void initialiser_audio(Mix_Music *music)
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
        printf("%s", SDL_GetError());
    }
    music = Mix_LoadMUS("game_sound/Main_Menu_Msc.wav");
    Mix_PlayMusic(music, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 3.5);
}

// frees music files from memory
void liberer_musique(Mix_Music *music)
{
    Mix_FreeMusic(music);
}

// Initializes sound effects
void initialiser_audiobref(Mix_Chunk *music,char* filename)
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    char link[50];
    strcpy(link,"game_sound/");
    strcat(link,filename);
    music = Mix_LoadWAV(link);
    Mix_PlayChannel(-1, music, 0);
    if (music == NULL)
        printf("%s", SDL_GetError());
}

// frees memory from sound effects
void liberer_musiquebref(Mix_Chunk *music)
{
    Mix_FreeChunk(music);
}

// initializes text
void initialiser_texte(texte *txte)
{
    TTF_Init();
    txte->police = TTF_OpenFont("OpenSans-Bold.ttf", 100); //keep in main folder for now
    txte->color_txt.r = 255;
    txte->color_txt.g = 209;
    txte->color_txt.b = 220;
    txte->pos_txt.x = 50;
    txte->pos_txt.y = 0;
}

// prints text (the title in this case)
void afficher_texte(SDL_Surface *screen, texte txte)
{
    txte.txt = TTF_RenderText_Blended(txte.police, "TALES FROM THE FUTURE", txte.color_txt);
    SDL_BlitSurface(txte.txt, NULL, screen, &txte.pos_txt);
    SDL_FreeSurface(txte.txt);
}

// frees text from memory
void liberer_texte(texte txte)
{
    TTF_CloseFont(txte.police);
    TTF_Quit;
}



//THIS FUNCTION WILL HELP DETERMINE PIXEL POSITIONS

void PrintMousePosition(SDL_Surface *screen, TTF_Font *font, int x, int y) {
  char text[32];
  sprintf(text, "Mouse at %d, %d", x, y);
  text[31]='\0';
  SDL_Color textColor = { 255, 255, 255 };
  SDL_Surface *message = TTF_RenderText_Solid(font, text, textColor);
  SDL_Rect messageRect;
  messageRect.x = 10;
  messageRect.y = 10;
  SDL_BlitSurface(message, NULL, screen, &messageRect);
  SDL_FreeSurface(message);
}
