#include "button.hpp"
#include "entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include <string>

void show()
{
    std::cout << "motherfucker\n";
}

int main()
{
    SDL_Window *global_window = NULL;
    SDL_Renderer *global_renderer = NULL;

    global_window =
        SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
    if (global_window == NULL)
    {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
    }
    global_renderer = SDL_CreateRenderer(global_window, -1, SDL_RENDERER_ACCELERATED);

    if (global_renderer == NULL)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    }
    else
    {
        // Initialize renderer color
        SDL_SetRenderDrawColor(global_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

        // Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags))
        {
            printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        }
    }

    SDL_Event e;

    Entity image(global_renderer, "../images/1.png", 30, 30, 300, 300);
    Button button0(global_renderer, "../images/button.png", 500, 500, 300, 300, &e, (&show));
    button0.set_source(300, 200);

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
            button0.handle_event(&e);
        }

        // Clear screen
        SDL_SetRenderDrawColor(global_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(global_renderer);

        image.display();
        button0.display();

        SDL_RenderPresent(global_renderer);

        // Render texture to screen
        // image.display();
    }
}
