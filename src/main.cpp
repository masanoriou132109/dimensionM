#include "button.hpp"
#include "player.hpp"
#include "text.hpp"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include <string>
#include <vector>

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

int main()
{
    Uint64 startTime = SDL_GetPerformanceCounter();

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window *g_window = NULL;
    SDL_Renderer *g_renderer = NULL;

    g_window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (g_window == NULL)
    {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
    }
    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

    if (g_renderer == NULL)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    }
    else
    {
        // Initialize renderer color
        SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

        // Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags))
        {
            printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        }
    }

    SDL_Event e;
    const Uint8 *key_state = SDL_GetKeyboardState(NULL);
    bool quit = 0;

    // 宣告區

    Player ply1(g_renderer, "../images/1.png", 30, 500, 100, 100, &e, 10, 300);
    ply1.set_source("../images/2.png", "../images/4.png", "../images/3.png");
    Fodder fod1(g_renderer, "../images/brown1.png", 300, 30, 200, 100, &e, 0, exponential);

    // 宣告區

    while (!quit)
    {
        // Handle events on queue
        SDL_PollEvent(&e);
        // User requests quit
        if (e.type == SDL_QUIT)
        {
            quit = true;
        }

        key_state = SDL_GetKeyboardState(NULL);
        SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(g_renderer);
        Uint64 end = SDL_GetPerformanceCounter();

        // 寫程式區

        ply1.handle_event(key_state, &e);
        ply1.display();
        fod1.display();
        ply1.attacked(fod1);

        // 寫程式區

        SDL_RenderPresent(g_renderer);
        double elapse = (double)(end - startTime) / SDL_GetPerformanceFrequency();

        // Render texture to screen
    }
}
