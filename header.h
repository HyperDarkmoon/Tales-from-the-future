

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3
#define SCREEN_WIDTH 1980
#define BACKGROUND_HEIGHT 480
#define SCREEN_HEIGHT 600
#define MAX_SCORES 100

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

void initBack(Background *b, SDL_Surface *screen,const char* path);
void initMusic(char *music);
void moveCamera(Background *b, int x, int y);
void afficherBack(Background b, SDL_Surface *screen);
void scrolling(Background *b, int direction,int dx);
void saveScore(ScoreInfo s, char *fileName);
void bestScore(char *filename, ScoreInfo t[]);
void animerBack(Background *b, SDL_Surface **screen);
void playMultiplayer(SDL_Surface *screen,Background *b1, Background *b2);
void draw_hearts(SDL_Surface *surface, int num_hearts);