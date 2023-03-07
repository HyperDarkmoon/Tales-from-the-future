#ifndef ES_H
#define ES_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#define SCREEN_H 770
#define SCREEN_W 1366

typedef struct {
    SDL_Rect rect;
    int velocity;
    int maximumvelocity;
    int health;
    int max_health;
    SDL_Surface* sprite[8];  
    SDL_Surface* idle_sprite[8];
    int current_frame;
    int current_idle_frame;
    int last_frame_time;
}Entity;


void update_entity_animation(Entity *player, Uint32 current_time, int player_moving);
void init_entity(Entity* player, int x, int y, int velocity, int maximumvelocity, int health, int max_health, const char* sprite_paths[]);
void print_entity(Entity *player, SDL_Surface *screen_surface, int player_moving);
void init_idle_entity_animation(Entity *player, const char *idle_sprite_paths[]);

#endif