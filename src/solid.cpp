#include "solid.hpp"

void Solid::display()
{
    collider = {x_, y_, w_, h_};

    SDL_RenderCopy(renderer_, texture_, NULL, &on_window_);
}

void Solid::collision(Solid &target)
{
    if (collider.x < (target.collider.x + target.collider.w) && (collider.x + collider.w) > target.collider.x &&
        collider.y < (target.collider.y + target.collider.h) && (collider.y + collider.h) > target.collider.y)
    {
        std::cout << "collided\n";
    }
}