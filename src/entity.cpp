
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "entity.hpp"
#include <string>

Entity::Entity(SDL_Renderer *global_renderer, std::string image_path, int p_x, int p_y)
    : renderer_(global_renderer), x_(p_x), y_(p_y)
{
    texture_ = IMG_LoadTexture(renderer_, image_path.c_str());
    std::cout << "texture loaded\n";
}

void Entity::display()
{
    SDL_RenderCopy(renderer_, texture_, NULL, NULL);

    SDL_RenderPresent(renderer_);
}

Entity::~Entity()
{
    SDL_DestroyTexture(texture_);
}