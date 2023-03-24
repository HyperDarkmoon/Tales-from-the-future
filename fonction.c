
#include "header.h"
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3
#define MAX_SCORES 100
#define SCREEN_WIDTH 1980
#define BACKGROUND_HEIGHT 2400
#define SCREEN_HEIGHT 600

void initBack(Background *b, SDL_Surface *screen) {
    // Load background images
    b->images[0] = IMG_Load("111.png");
    b->images[1] = IMG_Load("111.png");
    b->images[2] = IMG_Load("111.png");
    b->images[3] = IMG_Load("111.png");

    b->currentImageIndex = 0;

    // Set background rect x and y to 0
    b->rect.x = 0;
    b->rect.y = 0;

    // Set background rect width and height to the width and height of the first image
    b->rect.w = b->images[0]->w;
    b->rect.h = b->images[0]->h;

    // Set camera position x and y to 0
    b->camera_pos.x = 0;
    b->camera_pos.y = 0;

    // Calculate camera view width and height based on screen size and aspect ratio of background image
    b->camera_pos.w = SCREEN_WIDTH * BACKGROUND_HEIGHT / SCREEN_HEIGHT;
    b->camera_pos.h = SCREEN_HEIGHT * BACKGROUND_HEIGHT / SCREEN_WIDTH;

    // Set direction to 0
    b->direction = 0;
}


void initMusic(char *music) {
    // Initialize SDL_mixer
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        printf("Unable to initialize SDL_mixer: %s\n", Mix_GetError());
        exit(1);
    }

}

void afficherBack(Background b, SDL_Surface *screen) {
    // Blit the current image frame of the background to the screen
    SDL_BlitSurface(b.images[b.currentImageIndex], &b.camera_pos, screen,NULL);
    // Update the screen
    SDL_Flip(screen);
}

void scrolling(Background *b, int direction, int dx) {
    switch (direction) {
        case LEFT:
            b->camera_pos.x -= dx;
            break;
        case RIGHT:
            b->camera_pos.x += dx;
            break;
        case UP:
            b->camera_pos.y -= dx;
            break;
        case DOWN:
            b->camera_pos.y += dx;
            break;
        default:
            break;
            
        
    }
    //Checks if the background rectangle has gone off-screen and wraps it around to the opposite side if necessary
    if (b->camera_pos.x < 0) {
        b->camera_pos.x += b->rect.w;
    } else if (b->camera_pos.x >= b->rect.w) {
        b->camera_pos.x -= b->rect.w;
    }
    if (b->camera_pos.y < 0) {
        b->camera_pos.y += b->rect.h;
    } else if (b->camera_pos.y >= b->rect.h) {
        b->camera_pos.y -= b->rect.h;
    }
}


void saveScore(ScoreInfo s, char *fileName) {
    FILE *fp;
    fp = fopen(fileName, "a");
    if (fp == NULL) {
        printf("Error: could not open file.\n");
        return;
    }
    fprintf(fp, "%d %d %s\n", s.score, s.time, s.playerName);
    fclose(fp);
}

void bestScore(char *filename, ScoreInfo t[]) {
    FILE *fp;
    char line[100];
    int i = 0;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: could not open file.\n");
        return;
    }
    while (fgets(line, sizeof(line), fp) != NULL && i < MAX_SCORES) {
        sscanf(line, "%d %d %s", &t[i].score, &t[i].time, t[i].playerName);
        i++;
    }
    fclose(fp);
    int n = i;
    ScoreInfo temp;
    for (i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (t[j].score > t[i].score || (t[j].score == t[i].score && t[j].time < t[i].time)) {
                temp = t[i];
                t[i] = t[j];
                t[j] = temp;
            }
        }
    }
    printf("High Scores:\n");
    for (i = 0; i < 3 && i < n; i++) {
        char scoreString[50];
        sprintf(scoreString, "%s %d %d", t[i].playerName, t[i].score, t[i].time);
        printf("%d. %s\n", i + 1, scoreString);
    }
}
void animerBack(Background *b,SDL_Surface **screen) {
    const int dx = 10; 

    b->currentImageIndex++;

    if (b->currentImageIndex >= 4) {
        b->currentImageIndex = 0;
    }

    SDL_Event event;
    char *scoreFile = "scores.txt";
    ScoreInfo currentScore = { 1000, 120, "John" };
    ScoreInfo topScores[3] = {
    {0, 0, ""},
    {0, 0, ""},
    {0, 0, ""}
    };
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        scrolling(b, LEFT,dx);
                        break;
                    case SDLK_RIGHT:
                        scrolling(b, RIGHT,dx);
                        break;
                    case SDLK_UP:
                        scrolling(b, UP,dx);
                        break;
                    case SDLK_DOWN:
                        scrolling(b, DOWN,dx);
                        break;
                    case SDLK_m:
                        saveScore(currentScore, scoreFile);
                        bestScore(scoreFile, topScores);
            
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }

    // Blit the current background image to the screen
    afficherBack(*b,*screen);
}


void playMultiplayer(SDL_Surface *screen,Background *b1, Background *b2){
    SDL_FillRect(screen, NULL, 0);   // Clear the screen
    initBack(b1, screen);
    initBack(b2, screen);
    b1->camera_pos = (SDL_Rect) {0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT};
    b2->camera_pos = (SDL_Rect) {SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT};
    animerBack(b1,&screen);
    animerBack(b2,&screen);
    }







