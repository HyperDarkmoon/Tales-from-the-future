#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "fonction.h"

// Initializes background image
void initialiser_imageBACK(image *imge)
{
    char subfolder_path[256];
    FILE *fp = fopen("config.txt", "r");
    if (fp == NULL)
    {
        printf("unable to open config file\n");
        return;
    }
    fscanf(fp, "MY_SUBFOLDER=%s\n", subfolder_path);
    fclose(fp);
    strcat(subfolder_path, "/final.bmp");
    imge->url = subfolder_path;
    imge->img = SDL_LoadBMP(imge->url);
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

//Initializes the image for the first button
void initialiser_imageBOUTON1(image *imge)
{
    char subfolder_path[256];
    FILE *fp = fopen("config.txt", "r");
    if (fp == NULL)
    {
        printf("unable to open config file\n");
        return;
    }
    fscanf(fp, "MY_SUBFOLDER=%s\n", subfolder_path);
    fclose(fp);
    strcat(subfolder_path, "/newgame.png");
    imge->url = subfolder_path; //newgame.png
    imge->img = IMG_Load(imge->url);
    if (imge->img == NULL)
    {
        printf("unable to load background image %s \n", SDL_GetError());
        return;
    }
    imge->pos_img_ecran.x = 0;
    imge->pos_img_ecran.y = SCREEN_H - 700;
    imge->pos_img_affiche.w = 0;
    imge->pos_img_affiche.h = 0;
    imge->pos_img_affiche.x = 0;
    imge->pos_img_affiche.y = 0;
}

//Initializes the image for the second button
void initialiser_imageBOUTON2(image *imge)
{
    char subfolder_path[256];
    FILE *fp = fopen("config.txt", "r");
    if (fp == NULL)
    {
        printf("unable to open config file\n");
        return;
    }
    fscanf(fp, "MY_SUBFOLDER=%s\n", subfolder_path);
    fclose(fp);
    strcat(subfolder_path, "/quit.png");
    imge->url = subfolder_path; //quit.png
    imge->img = IMG_Load(imge->url);
    if (imge->img == NULL)
    {
        printf("unable to load background image %s \n", SDL_GetError());
        return;
    }
    imge->pos_img_ecran.x = 0;
    imge->pos_img_ecran.y = SCREEN_H - 400;
    imge->pos_img_affiche.w = 0;
    imge->pos_img_affiche.h = 0;
    imge->pos_img_affiche.x = 0;
    imge->pos_img_affiche.y = 0;
}

//Prints BMP image
void afficher_imageBMP(SDL_Surface *screen, image imge)
{
    SDL_BlitSurface(imge.img, &imge.pos_img_affiche, screen, &imge.pos_img_ecran);
}

//Prints first button
void afficher_imageBTN1(SDL_Surface *screen, image imge)
{
    SDL_BlitSurface(imge.img, NULL, screen, &imge.pos_img_ecran);
}

//Prints second button
void afficher_imageBTN2(SDL_Surface *screen, image imge)
{
    SDL_BlitSurface(imge.img, NULL, screen, &imge.pos_img_ecran);
}

//frees images from memory
void liberer_image(image imge)
{
    SDL_FreeSurface(imge.img);
}


//Initializes the audio files
void initialiser_audio(Mix_Music *music)
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
        printf("%s", SDL_GetError());
    }
    music = Mix_LoadMUS("track.mp3");
    Mix_PlayMusic(music, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 3.5);
}

//frees music files from memory
void liberer_musique(Mix_Music *music)
{
    Mix_FreeMusic(music);
}

//Initializes sound effects
void initialiser_audiobref(Mix_Chunk *music)
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    music = Mix_LoadWAV("simple.wav");
    Mix_PlayChannel(-1, music, 0);
    if (music == NULL)
        printf("%s", SDL_GetError());
}

//frees memory from sound effects
void liberer_musiquebref(Mix_Chunk *music)
{
    Mix_FreeChunk(music);
}

//initializes text
void initialiser_texte(texte *txte)
{
    /*char subfolder_path[256];
    FILE *fp = fopen("config.txt", "r");
    if (fp == NULL)
    {
        printf("unable to open config file\n");
        return;
    }
    fscanf(fp, "MY_SUBFOLDER_FONTS=%s\n", subfolder_path);
    fclose(fp);
    printf("%s",subfolder_path);
    strcat(subfolder_path, "/OpenSans-Bold.ttf");*/
    TTF_Init();
    txte->police = TTF_OpenFont("OpenSans-Bold.ttf", 100);
    txte->color_txt.r = 255;
    txte->color_txt.g = 209;
    txte->color_txt.b = 220;

    txte->pos_txt.x = 50;
    txte->pos_txt.y = 0;
}

//prints text (the title in this case)
void afficher_texte(SDL_Surface *screen, texte txte)
{
    txte.txt = TTF_RenderText_Blended(txte.police, "TALES FROM THE FUTURE", txte.color_txt);
    SDL_BlitSurface(txte.txt, NULL, screen, &txte.pos_txt);
}

//frees text from memory
void liberer_texte(texte txte)
{
    TTF_CloseFont(txte.police);
    TTF_Quit;
}