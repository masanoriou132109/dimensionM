#include "solid.hpp"

void Solid::display()
{
    collider = {int(x_), int(y_), int(w_), int(h_)};

    pos.x = x_;
    pos.y = y_;

    SDL_RenderCopy(renderer_, texture_, NULL, &collider);
}

bool Solid::collision(SDL_Rect target_collider)
{
    if (collider.x < (target_collider.x + target_collider.w) && (collider.x + collider.w) > target_collider.x &&
        collider.y < (target_collider.y + target_collider.h) && (collider.y + collider.h) > target_collider.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}