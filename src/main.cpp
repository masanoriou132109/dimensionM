#include "button.hpp"
// #include "player.hpp"
// include "colli.hpp"
#include "fodder.hpp"
#include "text.hpp"
#include "weapon.hpp"
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
    Player ply1(g_renderer, "../images/1.png", 500, 500, 100, 100, &e, 5, 500);
    ply1.set_source("../images/3.png", "../images/4.png", "../images/2.png");
    std::vector<Fodder *> fods;
    // fods.push_back(new Fodder(g_renderer, EXPO, 200, 200, 60, 60));
    fods.push_back(new Fodder(g_renderer, CONST, 20, 20, 100, 100));
    std::vector<Solid *> obst;
    obst.push_back(new Solid(g_renderer, "../images/brick.png", 600, 600, 80, 80, &e));

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

        ply1.handle_event(key_state, &e);
        ply1.display();
        for (auto i : obst)
        {
            i->display();
        }

        for (auto i : fods)
        {
            i->display(ply1, obst);
        }

        // 寫程式區

        SDL_RenderPresent(g_renderer);
    }
}
