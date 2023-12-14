#ifndef FODDER_H
#define FODDER_H

#include "mob.hpp"

enum math_kind
{
    zero_degree_polynomial = 0,
    higher_degree_polynomial = 1,
    exponential = 2,
    anti_gene_function = 3
};

class Fodder : public Mob
{
  public:
    Fodder(SDL_Renderer *global_renderer, std::string image_path, int p_x, int p_y, int p_w, int p_h,
           SDL_Event *global_event, int p_speed, math_kind p_math)
        : Mob(global_renderer, image_path, p_x, p_y, p_w, p_h, global_event, p_speed), con_(p_math)
    {
        atk_ = (p_math + 1) * 10;
    }
    int getatk()
    {
        return atk_;
    }

  private:
    int atk_;
    math_kind con_;
};

#endif // FODDER_H