#ifndef WEAPON_H
#define WEAPON_H

#include "solid.hpp"

enum Math
{
    DIFFERENTIATE = 0,
    INTEGRATION = 1,
    DE_FOURIER = 2,
    TAYLOR_SERIES = 3,
    LAPLACE_TRANS = 4
};

class Weapon : public Solid
{
  private:
    float w_ = 300;
    float h_ = 150;
    Math attack_;

  public:
    Weapon(SDL_Renderer *global_renderer, float p_x, float p_y, Math p_attack);
    // friend class Player;
    void display();
    friend class Player;
    bool picked;
};

#endif // WEAPON_H