

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL_ttf.h>
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3
#define SCREEN_WIDTH 1980
#define BACKGROUND_HEIGHT 480
#define SCREEN_HEIGHT 600
#define MAX_SCORES 100
#define SCORES_WIDTH 500
#define SCORES_HEIGHT 300
#define SCORE_DIGIT_WIDTH 30
#define SCORE_DIGIT_HEIGHT 50
typedef struct {
    SDL_Rect rect;
    SDL_Surface *images[4];
    int currentImageIndex;
    SDL_Rect camera_pos;
    SDL_Rect posBack1;
    int direction;
    SDL_Rect posScreen1;
    SDL_Rect posBack2;
}Background;
typedef struct {
    int score;
    int time;
    char playerName[20];
} ScoreInfo;
void initBack(Background* b, SDL_Surface* screen, const char** paths, int numImages);
void initMusic(char *music);
void afficherBack(Background b, SDL_Surface *screen);
void scrolling(Background *b, int direction,int dx);
void saveScore(ScoreInfo s, char *fileName);
void bestScore(char *filename, ScoreInfo t[]);
void animerBack(Background *b, SDL_Surface **screen);
void draw_hearts(SDL_Surface *surface, float lives,Background *b);
void playMultiplayer(Background* b1, Background* b2,SDL_Surface* screen , const char** paths);
void playSinglePlayer(SDL_Surface *screen, Background *b, const char **paths) ;