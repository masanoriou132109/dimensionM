
#ifndef ENTITY_H
#define ENTITY_H
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include <iostream>
#include <string>
class Entity
{
  public:
    Entity(SDL_Renderer *global_renderer, std::string image_path, int p_x, int p_y);
    ~Entity();
    virtual void display();

  protected:
    int x_, y_;
    SDL_Texture *texture_;
    SDL_Renderer *renderer_;
};
#endif // ENTITY_H