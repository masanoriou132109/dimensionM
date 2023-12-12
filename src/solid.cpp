#include "solid.hpp"

void Solid::display()
{
    collider = {int(x_), int(y_), int(w_), int(h_)};

    SDL_RenderCopy(renderer_, texture_, NULL, &on_window_);
}

bool Solid::collision(Solid &target)
{
    if (collider.x < (target.collider.x + target.collider.w) && (collider.x + collider.w) > target.collider.x &&
        collider.y < (target.collider.y + target.collider.h) && (collider.y + collider.h) > target.collider.y)
    {
        return true;
    }
    else
    {
        return false;
    }
}