#include <SDL2/SDL.h>

void moveRect (SDL_Rect* r, int x, int y) {
    r->x += x;
    r->y += y;
}

int main (int argc, char* args[])
{
    /* INITIALIZATION */
    unsigned int ticks;
    unsigned int interval = 16; // 60 FPS
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    ticks = SDL_GetTicks();

    /* EXECUTION */
    SDL_SetRenderDrawColor(renderer, 0xFF,0xFF,0xFF,0x00);
    SDL_RenderFillRect(renderer, NULL);
    SDL_Rect r = { 200, 200, 50, 50 };
    SDL_Event e;
    while (1) {
        // while (SDL_PollEvent(&e) == 0);
        // if (e.type == SDL_QUIT) {
        //     break;
        // } else if (e.type == SDL_KEYDOWN) {
        //     switch (e.key.keysym.sym) {
        //         case SDLK_UP:
        //             r.y -= 10;
        //         case SDLK_DOWN:
        //             r.y += 10;
        //         case SDLK_LEFT:
        //             r.x -= 10;
        //         case SDLK_RIGHT:
        //             r.x += 10;
        //     }
        // }
        if(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                break;
            }
        }
        if(SDL_GetTicks() >= ticks+interval) {
            ticks = SDL_GetTicks();
            moveRect(&r,10,0);
        }
        SDL_SetRenderDrawColor(renderer, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(renderer, &r);    }

    /* FINALIZATION */
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}