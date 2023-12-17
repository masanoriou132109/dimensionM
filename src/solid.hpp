#ifndef SOLID_H
#define SOLID_H
#include "entity.hpp"
#include "vector.hpp"

class Solid : public Entity
{
  protected:
    SDL_Event *e; // 開始能處理事件

    // SDL_Rect *rect_clip;

    float foot_ = y_ + h_; // 還不知道會不會用到，腳的位置
    Vector pos;            // 就是座標

  public:
    Solid(){};
    Solid(SDL_Renderer *global_renderer, std::string image_path, int p_x, int p_y, int p_w, int p_h,
          SDL_Event *global_event) // 需多傳入一個global事件的指標（or&)
        : Entity(global_renderer, image_path, p_x, p_y, p_w, p_h), e(global_event), pos(float(p_x), float(p_y)){};

    SDL_Rect collider = {int(x_), int(y_), int(w_), int(h_)}; // 碰撞箱

    float delta_r = 0.1 * y_; // 薛說要的誤差值，但可能不用了

    bool collision(SDL_Rect target_collider); // 判斷與其他solid碰撞

    void display(); // 顯示，包含移動位置
};

#endif // SOLID_H