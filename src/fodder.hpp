#ifndef FODDER_H
#define FODDER_H

#include "mob.hpp"
#include "vector.hpp"
#include "weapon.hpp"

// 相當抱歉但是因為技術問題我必須把
// Player 和 Fodder 寫在同一個檔案裡面

enum math_kind
{
    CONST = 0,
    TRIG = 1,
    EXPO = 2,
    LOGA = 3,
    POLY = 4
};

// 小怪部分

class Player;

class Fodder : public Mob
{
  public: // 反正小怪不重要嘛全部設成public
    Fodder(SDL_Renderer *global_renderer, math_kind p_math, int p_x, int p_y, int p_w, int p_h, Polygon p_shape);
    int atk_;
    int hp_;
    math_kind con_;
    Polygon shape;

    float vel_x;
    float vel_y;
    float speed_ = 1;   // 你們想想看要設成多少，1就已經很快了
    bool isHit = false; // 被打到（為了不重複傷害）

    void display(Player &ply, std::vector<Solid *> obst); // 小怪的display 要記得傳玩家
};

// 玩家部分

class Player : public Mob
{
  private:
    std::vector<Math> weapon_;

    float hp_;
    Vector direction;

    SDL_Texture *atk1 = IMG_LoadTexture(renderer_, "../images/diff.png");
    SDL_Texture *atk2 = IMG_LoadTexture(renderer_, "../images/inte.png");
    SDL_Texture *atk3 = IMG_LoadTexture(renderer_, "../images/four.png");
    SDL_Texture *atk4 = IMG_LoadTexture(renderer_, "../images/tayl.png");
    SDL_Texture *atk5 = IMG_LoadTexture(renderer_, "../images/lapt.png");

  public:
    Player(SDL_Renderer *global_renderer, std::string image_path, int p_x, int p_y, int p_w, int p_h,
           SDL_Event *global_event, float p_speed, float p_hp)
        : Mob(global_renderer, image_path, p_x, p_y, p_w, p_h, global_event, p_speed, {}), hp_(p_hp),
          cir_(p_w / 2, {x_ + w_ / 2, y_ + h_ / 2}){};

    void handle_event(const Uint8 *p_keystate, SDL_Event *e);
    void display();
    void detect(std::vector<Weapon *> wps, std::vector<Fodder *> fods, std::vector<Solid *> obst);
    SDL_Rect bullet = {2000, 2000, 0, 0};
    Vector bullet_dir;
    Math shooting;
    bool isShooting = false;
    Circle cir_;
};

#endif // FODDER_H