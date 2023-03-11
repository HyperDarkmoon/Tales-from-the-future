#include "entities.h"

void init_entity(Entity* player, int x, int y, int velocity, int maximumvelocity, int health, int max_health)
{
    player->rect.h = 80;
    player->rect.w = 100;
    player->rect.x = x;
    player->rect.y= y;
    player->velocity=velocity;
    player->maximumvelocity = maximumvelocity;
    player->health = health;
    player->max_health = max_health;
    player->last_frame_time=100;
}
void init_idle_entity_animation(Entity *player)
{
    player->idle_sprite[0]=IMG_Load("test_entity/ready_1.png");
    player->idle_sprite[1]=IMG_Load("test_entity/ready_2.png");
    player->idle_sprite[2]=IMG_Load("test_entity/ready_3.png");
    player->idle_sprite[3]=IMG_Load("test_entity/ready_4.png");
    player->idle_sprite[4]=IMG_Load("test_entity/ready_5.png");
    player->idle_sprite[5]=IMG_Load("test_entity/ready_6.png");
    player->current_idle_frame=0;
}
void update_entity_animation(Entity *player, int player_moving)
{
    if(!player_moving)
    {
        if (player->current_idle_frame==5) player->current_idle_frame =0;
        else player->current_idle_frame++;
    }
    else
    {
        if (player->current_frame==5) player->current_frame = 0;
        else player->current_frame++;
    }
}
void print_entity(Entity *player, SDL_Surface *screen_surface, int player_moving)
{
    if (player_moving == 1)
    {
    player->rect.x += 10;
     SDL_BlitSurface(player->sprite[player->current_frame],NULL,screen_surface,&(player->rect));
    }
    else SDL_BlitSurface(player->idle_sprite[player->current_idle_frame],NULL,screen_surface,&(player->rect));
    SDL_Delay(player->last_frame_time);
}
void init_entity_animation(Entity *player)
{
    player->sprite[0]=IMG_Load("test_entity/run_1.png");
    player->sprite[1]=IMG_Load("test_entity/run_2.png");
    player->sprite[2]=IMG_Load("test_entity/run_3.png");
    player->sprite[3]=IMG_Load("test_entity/run_4.png");
    player->sprite[4]=IMG_Load("test_entity/run_5.png");
    player->sprite[5]=IMG_Load("test_entity/run_6.png");
    player->current_idle_frame=0;
}
