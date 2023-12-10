#ifndef CHARA_H
#define CHARA_H
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

    float vel_x = 0;
    float vel_y = 0;

    Move_dir move_dir;
    FACE face;

    // interacting
    int weapon_;  // 目前還不知道weapon會是怎樣
    float speed_; // 設定速率

  public:
    Mob(SDL_Renderer *global_renderer, std::string image_path, int p_x, int p_y, int p_w, int p_h,
        SDL_Event *global_event, int p_weapon, int p_speed)
        : Solid(global_renderer, image_path, p_x, p_y, p_w, p_h, global_event), weapon_(p_weapon), speed_(p_speed){};
    void handle_event(const Uint8 *p_keystate, SDL_Event *e);
    void display();
    void set_source(int p_w, int p_h, int num_of_sprite, int p_how);
};

#endif // CHARA_H