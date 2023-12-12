#include "mob.hpp"

void Mob::set_source(std::string image_path2, std::string image_path3, std::string image_path4)
{
    texture2_ = IMG_LoadTexture(renderer_, image_path2.c_str());
    texture3_ = IMG_LoadTexture(renderer_, image_path3.c_str());
    texture4_ = IMG_LoadTexture(renderer_, image_path4.c_str());
    hasSprite = true;
}

bool Mob::collision(Solid &target)
{
    if (dimension_ == 3)
    {
        if (y_ > target.collider.y - target.delta_r && y_ < target.collider.y + target.delta_r)
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
        else
        {
            return false;
        }
    }
    else
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
}
