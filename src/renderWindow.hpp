
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "entity.hpp"
#include <iostream>
#include <string>

class RenderWindow
{
  public:
    RenderWindow(std::string title, int p_w, int p_h);
    SDL_Texture *loadTexture(std::string path);
    void cleanUP();
    void clear();
    void render(Entity &p_entity);
    void display();
    SDL_Window *window;
    SDL_Renderer *renderer;

  private:
};

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

void RenderWindow::render(Entity &p_entity)
{
    SDL_Rect src;
    src.x = p_entity.getcurrentFrame().x;
    src.y = p_entity.getcurrentFrame().y;
    src.h = p_entity.getcurrentFrame().h;
    src.w = p_entity.getcurrentFrame().w;

    SDL_Rect dst;
    dst.x = p_entity.getX();
    dst.y = p_entity.getY();
    dst.h = p_entity.getcurrentFrame().h;
    dst.w = p_entity.getcurrentFrame().w;

    SDL_RenderCopy(renderer, p_entity.getTexture(), &src, &dst);
}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}
