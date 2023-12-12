#ifndef PLAYER_H
#define PLAYER_H
#include "mob.hpp"
#include "weapon.hpp"
#include <vector>

class Player : public Mob
{
  protected:
    std::vector<Math> weapon_;
    bool shooting = false;
    bool taking_weapon = false;

  public:
    Player(SDL_Renderer *global_renderer, std::string image_path, int p_x, int p_y, int p_w, int p_h,
           SDL_Event *global_event, float p_speed)
        : Mob(global_renderer, image_path, p_x, p_y, p_w, p_h, global_event, p_speed){};

    void handle_event(const Uint8 *p_keystate, SDL_Event *e);
    void display();

    friend class Weapon;
    void pick(Weapon &target);
    // void set_source(std::string image_path2, std::string image_path3,
    //                std::string image_path4); // 不要就不要設定
};

#endif // PLAYER_H