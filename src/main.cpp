#include "button.hpp"
#include "entity.hpp"
#include "mob.hpp"
#include "solid.hpp"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include <string>

const int SCREEN_FPS = 10;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
/*
void collision(SDL_Rect collider_subject, SDL_Rect collider_object)
{
    if (collider_subject.x < (collider_object.x + collider_object.w) &&
        (collider_subject.x + collider_subject.w) > collider_object.x &&
        collider_subject.y < (collider_object.y + collider_object.h) &&
        (collider_subject.y + collider_subject.h) > collider_object.y)
    {
        std::cout << "collided\n";
    }
}*/

void show()
{
    std::cout << "motherfucker\n";
}

int main()
{
    SDL_Window *g_window = NULL;
    SDL_Renderer *g_renderer = NULL;

    g_window =
        SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
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

    // Entity image(g_renderer, "../images/1.png", 30, 30, 300, 300);
    // Entity image2(g_renderer, "../images/3.jpg", 500, 80, 100, 100);
    // Button button0(g_renderer, "../images/littlepg.png", "../images/brown1.png", "../images/brown2.png", 300, 300,
    // 300,
    //               300, &e, (&show));
    Mob ch1(g_renderer, "../images/brown2.png", 70, 500, 200, 200, &e, 3, 10);
    // ch1.set_source("../images/brown2.png", "../images/brown2.png", "../images/brown2.png");
    //  Mob ch2(g_renderer, "../images/anime.png", 700, 500, 200, 200, &e, 3, 2);
    //  ch2.set_source(56, 185, 2, 0);

    bool quit = 0;

    while (!quit)
    {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            // User requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            key_state = SDL_GetKeyboardState(NULL);
            ch1.handle_event(key_state, &e);
            //  ch2.handle_event(key_state, &e);
            // button0.handle_event(&e);
        }

        // Clear screen
        SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(g_renderer);

        ch1.display();
        //  ch2.display();
        //   image.display();
        //   image2.display();
        // button0.display();
        // ch2.collision(ch1);
        SDL_RenderPresent(g_renderer);

        // Render texture to screen
        // image.display();
    }
}
