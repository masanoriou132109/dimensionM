#ifndef SOLID_H
#define SOLID_H
#include "entity.hpp"

class Solid : public Entity
{
  protected:
    SDL_Event *e;
    SDL_Rect *rect_clip;
    float foot_ = y_ + h_;

  public:
    Solid(){};
    Solid(SDL_Renderer *global_renderer, std::string image_path, int p_x, int p_y, int p_w, int p_h,
          SDL_Event *global_event)
        : Entity(global_renderer, image_path, p_x, p_y, p_w, p_h), e(global_event){};

    SDL_Rect collider = {int(x_), int(y_), int(w_), int(h_)};

    float delta_r = 0.1 * y_;

    bool collision(Solid &target);
    void display();
};

#endif // SOLID_H