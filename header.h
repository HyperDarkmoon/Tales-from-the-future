

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    SDL_Rect rect;
    SDL_Surface *images[4];
    int currentImageIndex;
    SDL_Rect camera_pos;
    int direction;
}Background;
typedef struct {
    int score;
    int time;
    char playerName[20];
} ScoreInfo;

void initBack(Background *b, SDL_Surface *screen);
void initMusic(char *music);
void afficherBack(Background b, SDL_Surface *screen);
void scrolling(Background *b, int direction,int dx);
void saveScore(ScoreInfo s, char *fileName);
void bestScore(char *filename, ScoreInfo t[]);
void animerBack(Background *b, SDL_Surface **screen);
void playMultiplayer(SDL_Surface *screen,Background *b1, Background *b2);