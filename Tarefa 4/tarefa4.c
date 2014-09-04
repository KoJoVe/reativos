/* Tarefa 4 - Sistemas Reativos

Esta tarefa consiste em um jogo, onde o jogador controla um quadrado azul através das setas
e atira para os quatro lados utilizando as teclas ASDW. A cada intervalo de tempo, surge um
quadrado que é um inimigo vermelho. O jogador deve desviar dos quadrados vermelhos e atigi-los
com seus tiros para poder sobreviver */

#include <SDL2/SDL.h>
#include <stdlib.h>

#define MAX 20

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
        *x = 625;
        *y = 0;
    } else if(i==2) {
        *x = 0;
        *y = 465;
    } else if(i==3) {
        *x = 625;
        *y = 465;
    }
}

void shootBullet(int i,int x, int y, Bullet** bullets) {
    SDL_Rect* g;
    Bullet* b;
    b = (Bullet *) malloc(sizeof(Bullet));
    g = (SDL_Rect *) malloc(sizeof(SDL_Rect));
    g->x=x;
    g->y=y;
    g->w=5;
    g->h=5;
    for(i=0;i<MAX;i++) {
        if(!bullets[i]) {
            bullets[i] = b;
            bullets[i]->g = g;
            bullets[i]->dir = i;
        }
    }
}

void checkColision(Bullet* bullet, SDL_Rect * enemy, SDL_Renderer* renderer) {
    if(bullet->g->x >= enemy->x - bullet->g->w && bullet->g->x <= enemy->x + enemy-> w) 
        if(bullet->g->y >= enemy->y - bullet->g->h && bullet->g->y <= enemy->y + enemy-> h) {
            SDL_SetRenderDrawColor(renderer, 0xFF,0xFF,0xFF,0x00);
            SDL_RenderFillRect(renderer, bullet->g);  
            SDL_RenderFillRect(renderer, enemy);  
            free(bullet);
            free(enemy);
        }
}

void followPlayer(SDL_Rect* player, SDL_Rect** enemy) {
    int i;
    for(i=0;i<MAX;i++) {
        if(enemy[i]->x < player->x)
            enemy[i] += 1;
        if(enemy[i]->x > player->x)
            enemy[i] -= 1;
        if(enemy[i]->y < player->y)
            enemy[i] += 1;
        if(enemy[i]->y > player->y)
            enemy[i] -= 1;
    }
}

SDL_Rect* spawnEnemy(int x, int y) {
    SDL_Rect* r;
    g = (SDL_Rect *) malloc(sizeof(SDL_Rect));
    g->x=x;
    g->y=y;
    g->w=15;
    g->h=15;
    return r;
}

int main (int argc, char* args[])
{
    /* INITIALIZATION */
    unsigned int ticks;
    unsigned int spawnInterval = 10000; // 60 FPS
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    ticks = SDL_GetTicks();
    int i,x,y,j;

    /* EXECUTION */
    SDL_SetRenderDrawColor(renderer, 0xFF,0xFF,0xFF,0x00);
    SDL_RenderFillRect(renderer, NULL);
    SDL_Rect r = { 200, 200, 20, 20 };
    SDL_Rect* enemies[MAX];
    Bullet* bullets[MAX];
    SDL_Event e;
    
    while (1) {

        if(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                break;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        r.y -= 1;
                    case SDLK_DOWN:
                        r.y += 1;
                    case SDLK_LEFT:
                        r.x -= 1;
                    case SDLK_RIGHT:
                        r.x += 1;
                    case SDLK_w:
                        if(!cooldown) {
                            shootBullet(0,x,y,bullets);
                            cooldown = true;
                        }
                    case SDLK_d:
                        if(!cooldown) {
                            shootBullet(1,x,y,bullets);
                            cooldown = true;
                        }
                    case SDLK_s:
                        if(!cooldown) {
                            shootBullet(2,x,y,bullets);
                            cooldown = true;
                        }
                    case SDLK_a:
                        if(!cooldown) {
                            shootBullet(3,x,y,bullets);
                            cooldown = true;
                        }
                }
            }
        }

        if(SDL_GetTicks() >= ticks+spawnInterval) {
            for(i=0;i<MAX;i++) {
                if(!enemies[i]) {
                    getRandomCoords(&x,&y);
                    enemies[i] = spawnEnemy(x,y);
                }
            }
        }

        for(i=0;i<MAX;i++) {
            if(bullets[i]) {
                for (j=0;j<MAX;i++) {
                    if(enemies[j]) {
                        checkColision(bullets[i],enemies[j],renderer);
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(renderer, &r);  

        SDL_SetRenderDrawColor(renderer, 0x00,0xFF,0x00,0x00);
        for(i=0;i<MAX;i++) {
            if(bullet[i])
                SDL_RenderFillRect(renderer, bullets[i]->g);
        }

        SDL_SetRenderDrawColor(renderer, 0xFF,0x00,0x00,0x00);
        for(i=0;i<MAX;i++) {
            if(enemies[i])
                SDL_RenderFillRect(renderer, enemies[i]);
        }

        followPlayer(&r,enemies);

        for(i=0;i<MAX;i++) {
            if(enemies[i]) {
                if(enemies[i]->x >= r.x - enemies[i]->w && enemies[i]->x <= r.x + r.w) 
                    if(enemies[i]->y >= r.y - enemies[i]->h && enemies[i]->y <= r.y + r.h) {
                        break;
                        break; //EndGame
                    }
            }
        }

        for(i=0;i<MAX;i++) {
            if(bullets[i]) {
                switch(bullets[i]->dir) {
                    case 0:
                        bullets[i]->g->y += 1;
                        break;
                    case 1:
                        bullets[i]->g->x += 1;
                        break;
                    case 2:
                        bullets[i]->g->y -= 1;
                        break;
                    case 3:
                        bullets[i]->g->x -= 1;
                        break;
                }
            }
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
