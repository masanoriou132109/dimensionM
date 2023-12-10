#ifndef SOLID_H
#define SOLID_H
#include "entity.hpp"

class Solid : public Entity
{
  protected:
    int sprite = 0;
    int num_of_sprite_;
    SDL_Event *e;
    SDL_Rect *rect_clip;

  public:
    Solid(SDL_Renderer *global_renderer, std::string image_path, int p_x, int p_y, int p_w, int p_h,
          SDL_Event *global_event)
        : Entity(global_renderer, image_path, p_x, p_y, p_w, p_h), e(global_event){};
    SDL_Rect collider = {x_, y_, w_, h_};
    void collision(Solid &target);
    void display();
};

#endif // SOLID_H