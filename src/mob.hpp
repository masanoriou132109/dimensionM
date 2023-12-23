#ifndef MOB_H
#define MOB_H

#include "solid.hpp"

enum Move_dir // 移動方向
{
    MOVE_UP = 0,
    MOVE_DOWN = 1,
    MOVE_RIGHT = 2,
    MOVE_LEFT = 3,
};

enum FACE // 面向
{
    RIGHT = 0,
    LEFT = 1
};

class Mob : public Solid
{
  protected:
    // for renderer using

    bool isJumping = false; // 判斷跳躍（因應三維）
    bool moving = false;    // 判斷移動
    bool hasSprite = false; // 若要有多個精靈圖就會被設成true
    int sprite = 0;         // 精靈圖數

    float vel_x = 0; // 速度
    float vel_y = 0;

    Move_dir move_dir; // 移動方向
    FACE face;         // 面向

    SDL_Texture *texture2_; // 精靈圖
    SDL_Texture *texture3_;
    SDL_Texture *texture4_;

    // interacting
    const float speed_; // 設定速率（與vel不同但相關），這算是用來保存值的

  public:
    Mob(SDL_Renderer *global_renderer, std::string image_path, int p_x, int p_y, int p_w, int p_h,
        SDL_Event *global_event, int p_speed) // 需多傳入移動速率
        : Solid(global_renderer, image_path, p_x, p_y, p_w, p_h, global_event), speed_(p_speed){};

    void set_source(std::string image_path2, std::string image_path3,
                    std::string image_path4); // 設定精靈圖，不要就別丟

    int dimension_ = 2; // 開始有維度
};

#endif // MOB_H