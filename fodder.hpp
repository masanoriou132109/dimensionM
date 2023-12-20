#ifndef FODDER_H
#define FODDER_H
//#include"Untitled1.hpp"
#include "mob.hpp"
#include "vector.hpp"
#include "weapon.hpp"
#include <iostream>


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
    Fodder(SDL_Renderer *global_renderer, math_kind p_math, int p_x, int p_y, int p_w, int p_h);
    int atk_;
    int hp_;
    math_kind con_;

    float vel_x;
    float vel_y;
    float speed_ = 1;   
    bool isHit = false; 
    void display(Player &ply, std::vector<Solid *> obst); 
};

// 玩家部分

class Player : public Mob
{
	friend class Fodder;
  private:
    std::vector<Math> weapon_;
	
	int animation_count;
    float hp_;
    Vector direction;

    SDL_Texture *atk1 = IMG_LoadTexture(renderer_, "diff.png");
    SDL_Texture *atk2 = IMG_LoadTexture(renderer_, "inte.png");
    SDL_Texture *atk3 = IMG_LoadTexture(renderer_, "four.png");
    SDL_Texture *atk4 = IMG_LoadTexture(renderer_, "tayl.png");
    SDL_Texture *atk5 = IMG_LoadTexture(renderer_, "tridra.png");
    SDL_Texture *atk6 = IMG_LoadTexture(renderer_, "loga.png");

  public:
    Player(SDL_Renderer *global_renderer, std::string image_path, int p_x, int p_y, int p_w, int p_h,
           SDL_Event *global_event, float p_speed, float p_hp)
        : Mob(global_renderer, image_path, p_x, p_y, p_w, p_h, global_event, p_speed), hp_(p_hp), animation_count(0){};

    void handle_event(const Uint8 *p_keystate, SDL_Event *e);
    void display();
    void detect(std::vector<Weapon *> wps, std::vector<Fodder *> fods, std::vector<Solid *> obst);
    SDL_Rect bullet = {2000, 2000, 0, 0};
    Vector bullet_dir;
    Math shooting;
    bool isShooting = false;
};

#endif // FODDER_H
