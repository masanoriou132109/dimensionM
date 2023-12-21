#ifndef PLAYER_H
#define PLAYER_H
#include "fodder.hpp"
#include "weapon.hpp"
#include <vector>

class Player : public Mob
{
  protected:
    std::vector<Math> weapon_;
    Circle cir_;

    int hp_;
    Vector direction;

    SDL_Texture *atk1 = IMG_LoadTexture(renderer_, "../images/diff.png");
    SDL_Texture *atk2 = IMG_LoadTexture(renderer_, "../images/inte.png");
    SDL_Texture *atk3 = IMG_LoadTexture(renderer_, "../images/four.png");
    SDL_Texture *atk4 = IMG_LoadTexture(renderer_, "../images/tayl.png");
    SDL_Texture *atk5 = IMG_LoadTexture(renderer_, "../images/lapt.png");

  public:
    Player(SDL_Renderer *global_renderer, std::string image_path, int p_x, int p_y, int p_w, int p_h,
           SDL_Event *global_event, float p_speed, int p_hp)
        : Mob(global_renderer, image_path, p_x, p_y, p_w, p_h, global_event, p_speed), hp_(p_hp),
          cir_(p_w / 2, {x_ + w_ / 2, y_ + h_ / 2}){};

    void handle_event(const Uint8 *p_keystate, SDL_Event *e);
    void display();
    void detect(std::vector<Weapon *> wps, std::vector<Fodder *> fods, std::vector<Solid *> obst);
    SDL_Rect bullet = {int(x_), int(y_), 0, 0};
    Vector bullet_dir;
    Math shooting;
    bool isShooting = false;
};

#endif // PLAYER_H