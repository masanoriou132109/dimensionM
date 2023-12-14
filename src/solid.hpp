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
    /*
        Solid &operator=(const Solid &other)
        {
            if (this != &other) // 檢查是否為自我賦值
            {
                // 釋放舊資源
                SDL_DestroyTexture(texture_);

                int wid, hei;
                if (other.texture_)
                {
                    SDL_QueryTexture(other.texture_, NULL, NULL, &wid, &hei);
                }

                // 創建新資源
                texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_TARGET, wid, hei);

                SDL_SetRenderTarget(renderer_, texture_);
                SDL_RenderCopy(renderer_, other.texture_, NULL, &other.on_window_);
                SDL_SetRenderTarget(renderer_, NULL);

                // 複製其他成員
                // 例如，如果有其他成員變數，應該進行相應的複製操作

                // 將 on_window_ 複製到 this->on_window_
                this->on_window_ = other.on_window_;
            }

            return *this;
        }*/

    SDL_Rect collider = {int(x_), int(y_), int(w_), int(h_)};

    float delta_r = 0.1 * y_;

    bool collision(Solid &target);
    void display();
};

#endif // SOLID_H