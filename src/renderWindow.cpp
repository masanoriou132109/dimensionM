#include "renderWindow.hpp"

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>

#include <iostream>

RenderWindow::RenderWindow(std::string title, int p_w, int p_h) : window(NULL), renderer(NULL)
{
    window =
        SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cout << "WINDOW_INIT died" << SDL_GetError() << '\n';
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void RenderWindow::cleanUP()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

SDL_Texture *RenderWindow::loadTexture(std::string path)
{
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture(renderer, path.c_str());

    if (texture == NULL)
    {
        std::cout << "loadTexture died" << SDL_GetError() << '\n';
    }

    return texture;
}

void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}