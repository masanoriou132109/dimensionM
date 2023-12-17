#include "mob.hpp"

void Mob::set_source(std::string image_path2, std::string image_path3, std::string image_path4)
{
    texture2_ = IMG_LoadTexture(renderer_, image_path2.c_str());
    texture3_ = IMG_LoadTexture(renderer_, image_path3.c_str());
    texture4_ = IMG_LoadTexture(renderer_, image_path4.c_str());
    hasSprite = true;
}
