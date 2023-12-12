#ifndef MOB_H
#define MOB_H

#include "solid.hpp"

enum Move_dir
{
    MOVE_UP = 0,
    MOVE_DOWN = 1,
    MOVE_RIGHT = 2,
    MOVE_LEFT = 3,
};

enum FACE
{
    RIGHT = 0,
    LEFT = 1
};

class Mob : public Solid
{
  protected:
    // for renderer using
    int dimension_ = 2;
    bool isJumping = false;
    bool moving = false;
    bool hasSprite = false;
    int sprite = 0;

    float vel_x = 0;
    float vel_y = 0;

    Move_dir move_dir;
    FACE face;

    SDL_Texture *texture2_;
    SDL_Texture *texture3_;
    SDL_Texture *texture4_;

    // interacting
    float speed_; // 設定速率

  public:
    Mob(SDL_Renderer *global_renderer, std::string image_path, int p_x, int p_y, int p_w, int p_h,
        SDL_Event *global_event, int p_speed)
        : Solid(global_renderer, image_path, p_x, p_y, p_w, p_h, global_event), speed_(p_speed){};

    // virtual void handle_event(const Uint8 *p_keystate, SDL_Event *e);
    // void display();
    void set_source(std::string image_path2, std::string image_path3,
                    std::string image_path4); // 設定精靈圖，不要就別丟

    bool collision(Solid &target);
};

#endif // MOB_H