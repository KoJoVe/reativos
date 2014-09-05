/* Tarefa 4 - Sistemas Reativos

Esta tarefa consiste em um jogo, onde o jogador controla um quadrado azul através das setas
e atira para os quatro lados utilizando as teclas ASDW. A cada intervalo de tempo, surge um
quadrado que é um inimigo vermelho. O jogador deve desviar dos quadrados vermelhos e atigi-los
com seus tiros para poder sobreviver */
#include <SDL2/SDL.h>
#include <stdlib.h>
#define MAX 20
#define WIN_WID 640
#define WIN_HEI 480
#define ENEMY_SIZE 15
#define PLAYER_SIZE 20
#define PLAYER_STEP 20
struct bullet {
    SDL_Rect* g;
    int dir;
};
typedef struct bullet Bullet;
void getRandomCoords(int* x, int* y) {
    int i = rand() % 4;
    if(i==0) {
        *x = 0;
        *y = 0;
    } else if (i==1) {
        *x = WIN_WID - ENEMY_SIZE;
        *y = 0;
    } else if(i==2) {
        *x = 0;
        *y = WIN_HEI - ENEMY_SIZE;
    } else if(i==3) {
        *x = WIN_WID - ENEMY_SIZE;
        *y = WIN_HEI - ENEMY_SIZE;
    }
}
void shootBullet(int dir,int x, int y, Bullet** bullets) {
    int i;
    SDL_Rect* g;
    Bullet* b;
    b = (Bullet *) malloc(sizeof(Bullet));
    g = (SDL_Rect *) malloc(sizeof(SDL_Rect));
    g->x=x;
    g->y=y;
    g->w=5;
    g->h=5;
    for(i=0;i<MAX;i++) {
        if(bullets[i]==NULL) {
            bullets[i] = b;
            bullets[i]->g = g;
            bullets[i]->dir = dir;
            break;
        }
    }
}
void checkColision(Bullet** bullet, SDL_Rect** enemy, SDL_Renderer* renderer) {
    int i,j;
    for(i=0;i<MAX;i++) {
        if(bullet[i]!=NULL) {
            for (j=0;j<MAX;j++) {
                if(enemy[j]!=NULL) {
                    if(bullet[i]->g->x >= enemy[j]->x - bullet[i]->g->w && bullet[i]->g->x <= enemy[j]->x + enemy[j]-> w) {
                        if(bullet[i]->g->y >= enemy[j]->y - bullet[i]->g->h && bullet[i]->g->y <= enemy[j]->y + enemy[j]-> h) {
                            SDL_SetRenderDrawColor(renderer, 0xFF,0xFF,0xFF,0x00);
                            SDL_RenderFillRect(renderer, bullet[i]->g);  
                            SDL_RenderFillRect(renderer, enemy[j]);  
                            free(bullet[i]);
                            bullet[i] = NULL;
                            free(enemy[j]);
                            enemy[j] = NULL;
                            break;
                        }
                    }
                }
            }
        }
    }
}
void followPlayer(SDL_Rect* player, SDL_Rect** enemy) {
    int i;
    for(i=0;i<MAX;i++) {
        if(enemy[i]!=NULL) {
            if(enemy[i]->x < player->x)
                enemy[i]->x += 5;
            if(enemy[i]->x > player->x)
                enemy[i]->x -= 5;
            if(enemy[i]->y < player->y)
                enemy[i]->y += 5;
            if(enemy[i]->y > player->y)
                enemy[i]->y -= 5;
        }
    }
}
void bulletOutBounds(Bullet** bullets) {
    int i;
    for(i=0;i<MAX;i++) {
        if(bullets[i]!=NULL)
            if(bullets[i]->g->x<0 || bullets[i]->g->y<0 || bullets[i]->g->x>WIN_WID || bullets[i]->g->h>WIN_HEI) {
                free(bullets[i]);
                bullets[i] = NULL;
            }
    }
}
SDL_Rect* spawnEnemy(int x, int y) {
    SDL_Rect* g;
    g = (SDL_Rect *) malloc(sizeof(SDL_Rect));
    g->x=x;
    g->y=y;
    g->w=ENEMY_SIZE;
    g->h=ENEMY_SIZE;
    return g;
}
int main (int argc, char* args[]) {
    unsigned int cdTick;
    unsigned int ticks;
    unsigned int followTicks;
    unsigned int spawnInterval = 1000;
    unsigned int cooldownTime = 200; 
    unsigned int followInterval = 100; 
    bool cooldown = false;
    int i,x,y,j;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_WID, WIN_HEI, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0xFF,0xFF,0xFF,0x00);
    SDL_RenderFillRect(renderer, NULL);
    SDL_Rect r = { 200, 200, PLAYER_SIZE, PLAYER_SIZE };
    SDL_Rect* enemies[MAX] = {NULL};
    Bullet* bullets[MAX] = {NULL};
    SDL_Event e;
    ticks = SDL_GetTicks();
    followTicks = SDL_GetTicks();
    while (1) {
        if(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                break;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        r.y -= PLAYER_STEP;
                        break;
                    case SDLK_DOWN:
                        r.y += PLAYER_STEP;
                        break;
                    case SDLK_LEFT:
                        r.x -= PLAYER_STEP;
                        break;
                    case SDLK_RIGHT:
                        r.x += PLAYER_STEP;
                        break;
                }
                switch (e.key.keysym.sym) {
                    case SDLK_w:
                            if(!cooldown) {
                                shootBullet(0,r.x+8,r.y+8,bullets);
                                cooldown = true;
                                cdTick = SDL_GetTicks();
                            }
                            break;
                        case SDLK_d:
                            if(!cooldown) {
                                shootBullet(1,r.x+8,r.y+8,bullets);
                                cooldown = true;
                                cdTick = SDL_GetTicks();
                            }
                            break;
                        case SDLK_s:
                            if(!cooldown) {
                                shootBullet(2,r.x+8,r.y+8,bullets);
                                cooldown = true;
                                cdTick = SDL_GetTicks();
                            }
                            break;
                        case SDLK_a:
                            if(!cooldown) {
                                shootBullet(3,r.x+8,r.y+8,bullets);
                                cooldown = true;
                                cdTick = SDL_GetTicks();
                            }
                            break;
                }
            }
        }
        if(cooldown==true) {
            if(SDL_GetTicks() >= cdTick+cooldownTime) {
                cooldown = false;
            }
        }
        if(SDL_GetTicks() >= ticks+spawnInterval) {
            for(i=0;i<MAX;i++) {
                if(enemies[i]==NULL) {
                    getRandomCoords(&x,&y);
                    enemies[i] = spawnEnemy(x,y);
                    ticks = SDL_GetTicks();
                    break;
                }
            }
        }
        bulletOutBounds(bullets);
        checkColision(bullets,enemies,renderer);
        for(i=0;i<MAX;i++) {
            if(enemies[i]!=NULL) {
                if(enemies[i]->x >= r.x - enemies[i]->w && enemies[i]->x <= r.x + r.w) 
                    if(enemies[i]->y >= r.y - enemies[i]->h && enemies[i]->y <= r.y + r.h) {
                        SDL_DestroyRenderer(renderer);
                        SDL_DestroyWindow(window);
                        SDL_Quit();
                        return 0;
                    }
            }
        }
        if(SDL_GetTicks() >= followTicks+followInterval) {
            followPlayer(&r,enemies);
            followTicks = SDL_GetTicks();
        }
        for(i=0;i<MAX;i++) {
            if(bullets[i]!=NULL) {
                switch(bullets[i]->dir) {
                    case 0:
                        bullets[i]->g->y -= 1;
                        break;
                    case 1:
                        bullets[i]->g->x += 1;
                        break;
                    case 2:
                        bullets[i]->g->y += 1;
                        break;
                    case 3:
                        bullets[i]->g->x -= 1;
                        break;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderFillRect(renderer, NULL);
        SDL_SetRenderDrawColor(renderer, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(renderer, &r);
        SDL_SetRenderDrawColor(renderer, 0x00,0xFF,0x00,0x00);
        for(i=0;i<MAX;i++) {
            if(bullets[i]!=NULL)
                SDL_RenderFillRect(renderer, bullets[i]->g);
        }
        SDL_SetRenderDrawColor(renderer, 0xFF,0x00,0x00,0x00);
        for(i=0;i<MAX;i++) {
            if(enemies[i]!=NULL)
                SDL_RenderFillRect(renderer, enemies[i]);
        }
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
