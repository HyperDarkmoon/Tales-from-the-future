#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "fonction.h"

void initialiser_imageSettings1(image *imge)
{
    imge->url = ("imgs/volume.png"); // newgame.png
    imge->img = IMG_Load(imge->url);
    if (imge->img == NULL)
    {
        printf("unable to load background image %s \n", SDL_GetError());
        return;
    }
    imge->pos_img_ecran.x = SCREEN_W-1800;
    imge->pos_img_ecran.y = SCREEN_H-900;
    imge->pos_img_affiche.w = 500;
    imge->pos_img_affiche.h = 281;
    imge->pos_img_affiche.x = SCREEN_W-1000;
    imge->pos_img_affiche.y = SCREEN_H - 252;
}
