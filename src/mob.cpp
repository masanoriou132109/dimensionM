#include "mob.hpp"

void Mob::set_source(std::string image_path2, std::string image_path3, std::string image_path4)
{
    texture2_ = IMG_LoadTexture(renderer_, image_path2.c_str());
    texture3_ = IMG_LoadTexture(renderer_, image_path3.c_str());
    texture4_ = IMG_LoadTexture(renderer_, image_path4.c_str());
    hasSprite = true;
}

void Mob::handle_event(const Uint8 *p_keystate, SDL_Event *e)
{
    if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_f)
    {
        if (hasSprite)
        {
            sprite--;
        }

        if (dimension_ == 3)
        {
            dimension_ = 2;
        }
        else
        {
            dimension_ = 3;
            isJumping = true;
        }
    }

    if (e->type == SDL_KEYDOWN)
    {
        if (dimension_ == 2)
        {
            if (p_keystate[SDL_SCANCODE_W])
            {
                vel_y = -sqrt(3) / 2 * speed_;
                vel_x = speed_ / 2;

                w_ += speed_ * sin(60);
                h_ += speed_ * sin(60);

                if (p_keystate[SDL_SCANCODE_A])
                {
                    vel_x = -speed_;
                }
                if (p_keystate[SDL_SCANCODE_D])
                {
                    vel_x = speed_;
                }
            }
            if (p_keystate[SDL_SCANCODE_S])
            {
                vel_y = sqrt(3) / 2 * speed_;
                vel_x = -speed_ / 2;

                w_ -= speed_ * sin(60);
                h_ -= speed_ * sin(60);

                if (p_keystate[SDL_SCANCODE_A])
                {
                    vel_x = -speed_;
                }
                if (p_keystate[SDL_SCANCODE_D])
                {
                    vel_x = speed_;
                }
            }
            if (p_keystate[SDL_SCANCODE_A])
            {
                face = LEFT;
                vel_x = -speed_;
                if (p_keystate[SDL_SCANCODE_W])
                {
                    vel_y = -speed_;
                }
                if (p_keystate[SDL_SCANCODE_S])
                {
                    vel_y = speed_;
                }
            }
            if (p_keystate[SDL_SCANCODE_D])
            {
                face = RIGHT;
                vel_x = speed_;
                if (p_keystate[SDL_SCANCODE_W])
                {
                    vel_y = -speed_;
                }
                if (p_keystate[SDL_SCANCODE_S])
                {
                    vel_y = speed_;
                }
            }
        }
        if (dimension_ == 3)
        {
            if (p_keystate[SDL_SCANCODE_W])
            {
                if (isJumping == false)
                {
                    vel_y = -1.5 * speed_;
                    isJumping = true;

                    if (p_keystate[SDL_SCANCODE_A])
                    {
                        vel_x = -speed_;
                    }
                    if (p_keystate[SDL_SCANCODE_D])
                    {
                        vel_x = speed_;
                    }
                }
            }

            if (p_keystate[SDL_SCANCODE_A])
            {
                face = LEFT;
                vel_x = -speed_;
            }
            if (p_keystate[SDL_SCANCODE_D])
            {
                face = RIGHT;
                vel_x = speed_;
            }
        }

        if (hasSprite)
        {
            sprite++;
            if (sprite == 4)
            {
                sprite = 0;
            }
        }
    }
}

void Mob::display()
{

    if (dimension_ == 3)
    {
        if (isJumping == true)
        {
            y_ += vel_y;
            x_ += vel_x;

            // 模擬重力

            vel_y += 0.3; // 增加一個向下的重力

            // 簡單的碰地判斷
            if ((y_ + h_) > 720)
            {
                y_ = 720 - h_;
                std::cerr << "\ntouch\n";
                isJumping = false;
                vel_y = 0;
            }
        }
        else
        {
            x_ += vel_x;
            y_ += vel_y;
        }

        on_window_ = {x_, y_, h_, w_};

        if (face == RIGHT)
        {
            switch (sprite)
            {
            case 0:
                SDL_RenderCopyEx(renderer_, texture_, NULL, &on_window_, 0, NULL, SDL_FLIP_NONE);
                break;
            case 1:
                SDL_RenderCopyEx(renderer_, texture2_, NULL, &on_window_, 0, NULL, SDL_FLIP_NONE);
                break;
            case 2:
                SDL_RenderCopyEx(renderer_, texture3_, NULL, &on_window_, 0, NULL, SDL_FLIP_NONE);
                break;
            case 3:
                SDL_RenderCopyEx(renderer_, texture4_, NULL, &on_window_, 0, NULL, SDL_FLIP_NONE);
            default:
                break;
            }
        }
        else
        {
            switch (sprite)
            {
            case 0:
                SDL_RenderCopyEx(renderer_, texture_, NULL, &on_window_, 0, NULL, SDL_FLIP_HORIZONTAL);
                break;
            case 1:
                SDL_RenderCopyEx(renderer_, texture2_, NULL, &on_window_, 0, NULL, SDL_FLIP_HORIZONTAL);
                break;
            case 2:
                SDL_RenderCopyEx(renderer_, texture3_, NULL, &on_window_, 0, NULL, SDL_FLIP_HORIZONTAL);
                break;
            case 3:
                SDL_RenderCopyEx(renderer_, texture4_, NULL, &on_window_, 0, NULL, SDL_FLIP_HORIZONTAL);
            default:
                break;
            }
        }
        vel_x = 0;
    }
    else
    {
        x_ += vel_x;
        y_ += vel_y;

        on_window_ = {x_, y_, h_, w_};

        if (face == RIGHT)
        {
            switch (sprite)
            {
            case 0:
                SDL_RenderCopyEx(renderer_, texture_, NULL, &on_window_, 0, NULL, SDL_FLIP_NONE);
                break;
            case 1:
                SDL_RenderCopyEx(renderer_, texture2_, NULL, &on_window_, 0, NULL, SDL_FLIP_NONE);
                break;
            case 2:
                SDL_RenderCopyEx(renderer_, texture3_, NULL, &on_window_, 0, NULL, SDL_FLIP_NONE);
                break;
            case 3:
                SDL_RenderCopyEx(renderer_, texture4_, NULL, &on_window_, 0, NULL, SDL_FLIP_NONE);
            default:
                break;
            }
        }
        else
        {
            switch (sprite)
            {
            case 0:
                SDL_RenderCopyEx(renderer_, texture_, NULL, &on_window_, 0, NULL, SDL_FLIP_HORIZONTAL);
                break;
            case 1:
                SDL_RenderCopyEx(renderer_, texture2_, NULL, &on_window_, 0, NULL, SDL_FLIP_HORIZONTAL);
                break;
            case 2:
                SDL_RenderCopyEx(renderer_, texture3_, NULL, &on_window_, 0, NULL, SDL_FLIP_HORIZONTAL);
                break;
            case 3:
                SDL_RenderCopyEx(renderer_, texture4_, NULL, &on_window_, 0, NULL, SDL_FLIP_HORIZONTAL);
            default:
                break;
            }
        }
        vel_x = 0;
        vel_y = 0;
    }
    collider = {x_, y_, w_, h_};
    SDL_Delay(10);
}
