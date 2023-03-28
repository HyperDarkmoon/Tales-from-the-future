
#include "header.h"

void initBack(Background* b, SDL_Surface* screen, const char** paths, int numImages) {
    // Load background images
    for (int i = 0; i < numImages; i++) {
        SDL_Surface* temp = IMG_Load(paths[i]);
        if (temp == NULL) {
            printf("Error: could not load background image: %s\n", IMG_GetError());
            exit(1);
        }
        b->images[i] = temp;
    }
    // Create a surface with the same format as the screen surface
    SDL_Surface* background = SDL_CreateRGBSurface(SDL_SWSURFACE, SCREEN_WIDTH, SCREEN_HEIGHT, screen->format->BitsPerPixel, 0, 0, 0, 0);
    if (background == NULL) {
        printf("Error: could not create background surface: %s\n", SDL_GetError());
        exit(1);
    }

    // Scale background images to fill the entire screen without black borders
    SDL_Rect src_rect = { 0, 0, b->images[0]->w, b->images[0]->h };
    SDL_Rect dest_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    if (b->images[0]->w * SCREEN_HEIGHT > SCREEN_WIDTH * b->images[0]->h) {
        dest_rect.h = SCREEN_WIDTH * b->images[0]->h / b->images[0]->w;
        dest_rect.y = (SCREEN_HEIGHT - dest_rect.h) / 2;
    }
    else {
        dest_rect.w = SCREEN_HEIGHT * b->images[0]->w / b->images[0]->h;
        dest_rect.x = (SCREEN_WIDTH - dest_rect.w) / 2;
    }
    for (int i = 0; i < numImages; i++) {
        SDL_Surface* temp = b->images[i];
        SDL_SoftStretch(temp, &src_rect, background, &dest_rect);
    }

    // Set background rect x and y to 0
    b->rect.x = 0;
    b->rect.y = 0;

    // Set background rect width and height to the width and height of the background surface
    b->rect.w = background->w;
    b->rect.h = background->h;

    // Set camera position x and y to 0
    b->camera_pos.x = 0;
    b->camera_pos.y = 0;

    // Set camera view width and height to the screen width and height
    b->camera_pos.w = SCREEN_WIDTH;
    b->camera_pos.h = SCREEN_HEIGHT;

    // Set direction to 0
    b->direction = 0;

    // Free temporary surface
    SDL_FreeSurface(background);
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
    // Initialize background
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
    // Game loop
    while (!gameover) {
        // Handle events
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
                    }
                    break;
            }
        }

        // Update score and level
        score += level;
        if (score >= 10 * level) {
            level++;
        }

        // Draw background and hearts
        animerBack(b,&screen);
        draw_hearts(screen, lives, b);
        

        // Update screen
        SDL_Flip(screen);

        // Wait for 20 milliseconds
        SDL_Delay(20);
    }
    Uint32 elapsed_time = get_elapsed_time(start_time);
    printf("Elapsed time: %u milliseconds\n", elapsed_time);
    // Save score
    ScoreInfo si = { score,elapsed_time, "Player 1" };
    saveScore(si, "scores.txt");
    bestScore("scores.txt", topScores);
}

void playMultiplayer(SDL_Surface *screen, Background *b1, Background *b2, const char **paths) {
    SDL_FillRect(screen, NULL, 0);   // Clear the screen
    initBack(b1, screen, paths, 4);
    initBack(b2, screen, paths, 4);
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
    // Set camera positions for each background
    b1->camera_pos = (SDL_Rect) {0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT};
    b2->camera_pos = (SDL_Rect) {SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT};
    // Game loop
    while (!gameover) {
        // Handle events
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
                        case SDLK_d:
                            b2->direction = RIGHT;
                            scrolling(b2, RIGHT, 5);
                        case SDLK_z:
                            b2->direction = UP;
                            scrolling(b2, UP, 5);
                        case SDLK_s:
                            b2->direction = DOWN;
                            scrolling(b2, DOWN, 5);
                    }
                    break;
            }

        }
        score += level;
        if (score >= 10 * level) {
            level++;
        }

        // Draw background and hearts
        animerBack(b1,&screen);
        draw_hearts(screen, lives, b1);
        animerBack(b2,&screen);
        draw_hearts(screen, lives, b2);
        

        // Update screen
        SDL_Flip(screen);

        // Wait for 20 milliseconds
        SDL_Delay(20);
        for(int i=0;i<2;i++){
            Uint32 elapsed_time = get_elapsed_time(start_time);
            printf("Elapsed time: %u milliseconds\n", elapsed_time);
            // Save score
            ScoreInfo si = { score,elapsed_time, "Player 1" };
            saveScore(si, "scores.txt");
            bestScore("scores.txt", topScores);
        }
    
    }

}

