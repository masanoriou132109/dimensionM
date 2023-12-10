#ifndef CHARA_H
#define CHARA_H
#include "entity.hpp"

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

class Chara : public Entity
{
  protected:
    int sprite = 0;
    int num_of_sprite_;
    Move_dir move_dir;
    FACE face;
    int weapon_;
    int speed_;
    SDL_Event *e;
    SDL_Rect *rect_clip;
    int dimension_ = 2;
    bool isJumping = false;
    bool moving = false;
    int vel_x = 0;
    int vel_y = 0;

  public:
    Chara(SDL_Renderer *global_renderer, std::string image_path, int p_x, int p_y, int p_w, int p_h,
          SDL_Event *global_event, int p_weapon, int p_speed)
        : Entity(global_renderer, image_path, p_x, p_y, p_w, p_h), e(global_event), weapon_(p_weapon),
          speed_(p_speed){};
    ~Chara();
    void handle_event(const Uint8 *p_keystate, SDL_Event *e);
    void display();
    void set_source(int p_w, int p_h, int num_of_sprite, int p_how);
};

#endif // CHARA_H