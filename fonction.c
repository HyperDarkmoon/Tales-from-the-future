
#include "header.h"

void initBack(Background* b, SDL_Surface* screen, const char** paths, int numImages) {


    for (int i = 0; i < numImages; i++) {
        SDL_Surface* temp = IMG_Load(paths[i]);
        if (temp == NULL) {
            printf("Error: could not load background image: %s\n", IMG_GetError());
            exit(1);
        }
        b->images[i] = temp;
    }
    
    b->rect.x = 0;
    b->rect.y = 0;

    b->rect.w = screen->w;
    b->rect.h = screen->h;

    b->camera_pos.x = 0;
    b->camera_pos.y = 0;

    b->camera_pos.w = SCREEN_WIDTH;
    b->camera_pos.h = SCREEN_HEIGHT;

    b->direction = 0;

}

void initMusic(char *music) {
    
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        printf("Unable to initialize SDL_mixer: %s\n", Mix_GetError());
        exit(1);
    }

}


void afficherBack(Background b, SDL_Surface *screen) {
    
    SDL_BlitSurface(b.images[b.currentImageIndex], &b.camera_pos, screen,&b.rect);
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
    while (fgets(line, sizeof(line), fp) != NULL ) {
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
void draw_scores(char *filename, ScoreInfo t[]) {
    // Initialize SDL and TTF
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    // Create surface and load font
    SDL_Surface *surface = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
    TTF_Font *font = TTF_OpenFont("font.ttf", 28);

    // Load scores from file
    FILE *fp;
    char line[100];
    int i = 0;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: could not open file.\n");
        return;
    }
    while (fgets(line, sizeof(line), fp) != NULL ) {
        sscanf(line, "%d %d %s", &t[i].score, &t[i].time, t[i].playerName);
        i++;
    }
    fclose(fp);
    int n = i;

    // Sort scores
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

    // Create surface for scores
    SDL_Surface *textSurface;
    SDL_Rect rect;
    char scoreString[50];
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
    for (i = 0; i < 3 && i < n; i++) {
        sprintf(scoreString, "%d. %s %d %d", i + 1, t[i].playerName, t[i].score, t[i].time);
        textSurface = TTF_RenderText_Blended(font, scoreString, (SDL_Color) { 255, 255, 255 });
        rect.x = 50;
        rect.y = i * 50 + 50;
        SDL_BlitSurface(textSurface, NULL, surface, &rect);
        SDL_FreeSurface(textSurface);
    }

    // Update surface
    SDL_UpdateRect(surface, 0, 0, 0, 0);

    // Wait for user to quit
    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN) {
            break;
        }
    }

    // Clean up
    TTF_CloseFont(font);
    SDL_Quit();
    TTF_Quit();
}
void animerBack(Background *b,SDL_Surface **screen) {
    

    b->currentImageIndex++;

    if (b->currentImageIndex >= 4) {
        b->currentImageIndex = 0;
    }
    afficherBack(*b,*screen);
}


void draw_hearts(SDL_Surface *surface, float lives,Background*b) {
    SDL_Surface *full_heart = IMG_Load("heart1.png");
    SDL_Surface *half_heart = IMG_Load("heart2.png");
    SDL_Surface *empty_heart = IMG_Load("heart3.png");

    int heart_width = full_heart->w;
    int heart_height = full_heart->h;

    int x = b->rect.x;
    int y = b->rect.y;

    for (int i = 0; i < 3; i++) {
        SDL_Rect dest_rect = { x, y, heart_width, heart_height };

        if (lives >= 1.0f) {
            SDL_BlitSurface(full_heart, NULL, surface, &dest_rect);
        } else if (lives > 0.5f) {
            SDL_BlitSurface(half_heart, NULL, surface, &dest_rect);
        } else {
            SDL_BlitSurface(empty_heart, NULL, surface, &dest_rect);
        }

        x += heart_width + 10;
        lives -= 1.0f;
    }

    SDL_FreeSurface(full_heart);
    SDL_FreeSurface(half_heart);
    SDL_FreeSurface(empty_heart);
}

Uint32 get_elapsed_time(Uint32 start_time) {
    Uint32 current_time = SDL_GetTicks();
    Uint32 elapsed_time = current_time - start_time;
    return elapsed_time;
}

void playSinglePlayer(SDL_Surface *screen, Background *b, const char **paths) {
    
    initBack(b, screen, paths, 4);
    int gameover = 0;
    int score = 0;
    int level = 1;
    int lives = 3;
    SDL_Event event;
    Uint32 start_time = SDL_GetTicks();
    ScoreInfo topScores[3] = {
    {0, 0, ""},
    {0, 0, ""},
    {0, 0, ""}
    };
    
    while (!gameover) {
        
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    gameover = 1;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            gameover = 1;
                            break;
                        case SDLK_LEFT:
                            b->direction = LEFT;
                            scrolling(b, LEFT, 5);
                            break;
                        case SDLK_RIGHT:
                            b->direction = RIGHT;
                            scrolling(b, RIGHT, 5);
                            break;
                        case SDLK_UP:
                            b->direction = UP;
                            scrolling(b, UP, 5);
                            break;
                        case SDLK_DOWN:
                            b->direction = DOWN;
                            scrolling(b, DOWN, 5);
                            break;
                        case SDLK_m:
                            draw_scores("scores.txt", topScores);
                    }
                    break;
            }
        }
        score += level;
        if (score >= 10 * level) {
            level++;
        }
        animerBack(b,&screen);
        draw_hearts(screen, lives, b);

        SDL_Flip(screen);
        SDL_Delay(20);
    }
    Uint32 elapsed_time = get_elapsed_time(start_time);
    printf("Elapsed time: %u milliseconds\n", elapsed_time);
    ScoreInfo si = { score,elapsed_time, "Player 1" };
    saveScore(si, "scores.txt");
}


void playMultiplayer(Background* b1, Background* b2,SDL_Surface* screen , const char** paths) {

    SDL_Init(SDL_INIT_VIDEO);
    

 
    //SDL_Surface* p1_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, p1_rect.w, p1_rect.h, 32, 0, 0, 0, 0);
    initBack(b1,screen, paths, 4);

    //SDL_Surface* p2_surface = SDL_CreateRGBSurface(SDL_SWSURFACE, p2_rect.w, p2_rect.h, 32, 0, 0, 0, 0);
    initBack(b2,screen, paths, 4);
    b1->posBack1 = (SDL_Rect){0, (BACKGROUND_HEIGHT- SCREEN_HEIGHT) / 2, SCREEN_WIDTH  / 2, SCREEN_HEIGHT};
    b1->posScreen1 = (SDL_Rect){0, 0, SCREEN_WIDTH  / 2, SCREEN_HEIGHT};
    b1->posBack2 = (SDL_Rect){SCREEN_WIDTH  / 2, (BACKGROUND_HEIGHT  - SCREEN_HEIGHT) / 2, SCREEN_WIDTH  / 2, SCREEN_HEIGHT};


    b2->posBack1 = (SDL_Rect){SCREEN_WIDTH  / 2, (BACKGROUND_HEIGHT  - SCREEN_HEIGHT) / 2, SCREEN_WIDTH  / 2, SCREEN_HEIGHT};
    b2->posScreen1 = (SDL_Rect){SCREEN_WIDTH  / 2, 0, SCREEN_WIDTH  / 2, SCREEN_HEIGHT};
    b2->posBack2 = (SDL_Rect){0, (BACKGROUND_HEIGHT  - SCREEN_HEIGHT) / 2, SCREEN_WIDTH  / 2, SCREEN_HEIGHT};
 
    int gameover1 = 0,gameover2=0;
    int score1=0,score2 = 0;
    int level = 1;
    int lives1= 3,lives2=3;
    SDL_Event event;
    Uint32 start_time = SDL_GetTicks();
    ScoreInfo topScores[3] = {
    {0, 0, ""},
    {0, 0, ""},
    {0, 0, ""}
    };

    while (!gameover1 && !gameover2) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    gameover1 = 1;
                    gameover2 = 1;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            gameover1 = 1;
                            gameover2 = 1;
                            break;
                        case SDLK_LEFT:
                            b1->direction = LEFT;
                            scrolling(b1, LEFT, 5);
                            break;
                        case SDLK_RIGHT:
                            b1->direction = RIGHT;
                            scrolling(b1, RIGHT, 5);
                            break;
                        case SDLK_UP:
                            b1->direction = UP;
                            scrolling(b1, UP, 5);
                            break;
                        case SDLK_DOWN:
                            b1->direction = DOWN;
                            scrolling(b1, DOWN, 5);
                            break;
                        case SDLK_q:
                            b2->direction = LEFT;
                            scrolling(b2, LEFT, 5);
                            break;
                        case SDLK_d:
                            b2->direction = RIGHT;
                            scrolling(b2, RIGHT, 5);
                            break;
                        case SDLK_z:
                            b2->direction = UP;
                            scrolling(b2, UP, 5);
                            break;
                        case SDLK_s:
                            b2->direction = DOWN;
                            scrolling(b2, DOWN, 5);
                            break;
                    }
                    break;
            }
        }
        score1 += level;
        score2 += level;

        if (score1 >= 10 * level || score2 >= 10 * level) {
            level++;
        }
        SDL_FillRect(screen, NULL, 0);
        
        animerBack(b1, &screen);
        draw_hearts(screen, lives1, b1);

        
        animerBack(b2, &screen);
        draw_hearts(screen, lives2, b2);
        SDL_Flip(screen);
        SDL_Delay(20);
        
        
    
    }
    Uint32 elapsed_time = get_elapsed_time(start_time);
    printf("Elapsed time: %u milliseconds\n", elapsed_time);
    
    ScoreInfo si1 = { score1,elapsed_time, "Player 1" };
    saveScore(si1, "scores.txt");
    ScoreInfo si2 = { score2,elapsed_time, "Player 2" };
    saveScore(si2, "scores.txt");
    bestScore("scores.txt", topScores);
}
