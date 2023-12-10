#include "entity.hpp"

Entity::Entity(SDL_Renderer *global_renderer, std::string image_path, int p_x, int p_y, int p_w, int p_h)
    : renderer_(global_renderer), x_(p_x), y_(p_y), w_(p_w), h_(p_h)
{
    texture_ = IMG_LoadTexture(renderer_, image_path.c_str());
    on_window_ = {x_, y_, w_, h_};

    std::cout << "texture loaded\n";
}

void Entity::display()
{
    SDL_RenderCopy(renderer_, texture_, NULL, &on_window_);
}

Entity::~Entity()
{
    SDL_DestroyTexture(texture_);
}