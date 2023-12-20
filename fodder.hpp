#ifndef FODDER_H
#define FODDER_H
//#include"Untitled1.hpp"
#include "mob.hpp"
#include "vector.hpp"
#include "weapon.hpp"
#include"colli.hpp"
enum math_kind
{
    CONST = 0,
    TRIG = 1,
    EXPO = 2,
    LOGA = 3,
    POLY = 4
};



class Player;

class Fodder : public Mob
{
  public:
    Fodder(SDL_Renderer *global_renderer, math_kind p_math, int p_x, int p_y, int p_w, int p_h, Polygon p_poly);
    int atk_;
    int hp_;
    math_kind con_;
    Polygon _poly;

    float vel_x;
    float vel_y;
    float speed_ = 1;   
    bool isHit = false; 

    void display(Player &ply, std::vector<Solid *> obst); 
};

// 玩家部分

class Player : public Mob
{
  private:
    std::vector<Math> weapon_;

    float hp_;
    Vector direction;

    SDL_Texture *atk1 = IMG_LoadTexture(renderer_, "C.png");
    SDL_Texture *atk2 = IMG_LoadTexture(renderer_, "L.png");
    SDL_Texture *atk3 = IMG_LoadTexture(renderer_, "E.png");
    SDL_Texture *atk4 = IMG_LoadTexture(renderer_, "A.png");
    SDL_Texture *atk5 = IMG_LoadTexture(renderer_, "T.png");

  public:
    Player(SDL_Renderer *global_renderer, std::string image_path, int p_x, int p_y, int p_w, int p_h,
           SDL_Event *global_event, float p_speed, float p_hp)
        : Mob(global_renderer, image_path, p_x, p_y, p_w, p_h, global_event, p_speed), hp_(p_hp){};

    void handle_event(const Uint8 *p_keystate, SDL_Event *e);
    void display();
    void detect(std::vector<Weapon *> wps, std::vector<Fodder *> fods, std::vector<Solid *> obst);
    SDL_Rect bullet = {2000, 2000, 0, 0};
    Vector bullet_dir;
    Math shooting;
    bool isShooting = false;
};

#endif // FODDER_H
