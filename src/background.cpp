#include "background.hpp"

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>

#include <iostream>

Background::Background(std::string title, int p_w, int p_h) : window(NULL), renderer(NULL)
{
    window =
        SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cout << "WINDOW_INIT died" << SDL_GetError() << '\n';
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void Background::cleanUP()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Background::loadTexture(std::string path)
{
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture(renderer, path.c_str());

    if (texture == NULL)
    {
        std::cout << "loadTexture died" << SDL_GetError() << '\n';
    }
}

void Background::clear()
{
    SDL_RenderClear(renderer);
}

void Background::display()
{
    SDL_RenderPresent(renderer);
}

Background::~Background()
{
    SDL_DestroyTexture(texture_);
}