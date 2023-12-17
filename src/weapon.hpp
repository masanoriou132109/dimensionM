#ifndef WEAPON_H
#define WEAPON_H

#include "solid.hpp"

enum Math
{
    DIFFERENTIATE = 0,
    INTEGRATION = 1,
    DE_FOURIER = 2,
    LOGARITHM = 3,
    TAYLOR_SERIES = 4,
    LAPLACE_TRANS = 5,
    NONE = 6
};

class Weapon : public Solid // 這個標頭檔只處理武器被撿起來，發射出去的武器屬於player的一部分，不然會造成循環include
{
  private:
    float w_ = 300;
    float h_ = 150;

  public: // 跟小怪一樣，反正這種免洗的東西就全部公開
    Weapon(SDL_Renderer *global_renderer, float p_x, float p_y, Math p_attack);
    friend class Player; // 讓玩家得知撿到武器的性質
    void display();
    bool picked = false; // 被撿起來就不顯示了，小怪不會碰到
    Math attack_;
};

#endif // WEAPON_H