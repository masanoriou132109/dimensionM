#include "weapon.hpp"

Weapon::Weapon(SDL_Renderer *global_renderer, float p_x, float p_y, Math p_attack)
{
    renderer_ = global_renderer;
    x_ = p_x;
    y_ = p_y;
    attack_ = p_attack;
    switch (p_attack)
    {
    case DIFFERENTIATE:
        texture_ = IMG_LoadTexture(renderer_, "diff.png");
        break;
    case INTEGRATION:
        texture_ = IMG_LoadTexture(renderer_, "inte.png");
        break;
    case LOGARITHM:
    	texture_ = IMG_LoadTexture(renderer_, "loga.png");
    	break;
    case DE_FOURIER:
        texture_ = IMG_LoadTexture(renderer_, "four.png");
        break;
    case TAYLOR_SERIES:
        texture_ = IMG_LoadTexture(renderer_, "tridra.png");
        break;
    case LAPLACE_TRANS:
        texture_ = IMG_LoadTexture(renderer_, "lapt.png");
        break;
    default:
        break;
    }
}

void Weapon::display()
{
    if (!picked)
    {
        collider = {int(x_), int(y_), int(w_), int(h_)};

        SDL_RenderCopy(renderer_, texture_, NULL, &collider);
    }
}
