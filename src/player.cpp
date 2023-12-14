#include "player.hpp"

void Player::handle_event(const Uint8 *p_keystate, SDL_Event *e)
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

    if (p_keystate[SDL_SCANCODE_SPACE])
    {
        if (taking_weapon)
        {
            if (!shooting)
            {
                shooting = true;
            }
        }
    }

    if (dimension_ == 2)
    {
        if (p_keystate[SDL_SCANCODE_W])
        {
            vel_y = -sqrt(3) / 2 * speed_;
            vel_x = speed_ / 2;

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
                vel_y = -5 * sqrt(speed_);
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
        if (sprite == 20)
        {
            sprite = 5;
        }
    }
}

void Player::display()
{

    if (dimension_ == 3)
    {
        if (isJumping == true)
        {
            y_ += vel_y;
            x_ += vel_x;

            if (x_ + w_ > SCREEN_WIDTH)
            {
                x_ = SCREEN_WIDTH - w_;
            }
            if (x_ < 0)
            {
                x_ = 0;
            }
            if (y_ + h_ > SCREEN_HEIGHT)
            {
                y_ = SCREEN_HEIGHT - w_;
            }
            if (y_ < 0)
            {
                y_ = 0;
            }
            w_ = abs(0.8 * y_);
            h_ = abs(0.8 * y_);

            // 模擬重力

            vel_y += 0.3; // 增加一個向下的重力

            // 簡單的碰地判斷
            if ((y_ + h_) > SCREEN_HEIGHT)
            {
                y_ = SCREEN_HEIGHT - h_;
                isJumping = false;
                vel_y = 0;
            }
        }
        else
        {
            x_ += vel_x;
            y_ += vel_y;

            if (x_ + w_ > SCREEN_WIDTH)
            {
                x_ = SCREEN_WIDTH - w_;
            }
            if (x_ < 0)
            {
                x_ = 0;
            }
            if (y_ + h_ > SCREEN_HEIGHT)
            {
                y_ = SCREEN_HEIGHT - w_;
            }
            if (y_ < 0)
            {
                y_ = 0;
            }

            w_ = abs(0.8 * y_);
            h_ = abs(0.8 * y_);
        }

        foot_ = y_ + h_;

        on_window_ = {int(x_), int(y_), int(h_), int(w_)};

        if (face == RIGHT)
        {
            switch (sprite / 5)
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
            switch (sprite / 5)
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

        if (x_ + w_ > SCREEN_WIDTH)
        {
            x_ = SCREEN_WIDTH - w_;
        }
        if (x_ < 0)
        {
            x_ = 0;
        }
        if (y_ + h_ > SCREEN_HEIGHT)
        {
            y_ = SCREEN_HEIGHT - w_;
        }
        if (y_ < 0)
        {
            y_ = 0;
        }

        w_ = abs(0.8 * y_);
        h_ = abs(0.8 * y_);

        on_window_ = {int(x_), int(y_), int(h_), int(w_)};

        if (face == RIGHT)
        {
            switch (sprite / 5)
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
            switch (sprite / 5)
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
    collider = {int(x_), int(y_), int(h_), int(w_)};
    SDL_Delay(10);
}

void Player::pick(std::vector<Weapon> wps)
{
    for (auto i : wps)
    {
        if (collider.x < (i.collider.x + i.collider.w) && (collider.x + collider.w) > i.collider.x &&
            collider.y < (i.collider.y + i.collider.h) && (collider.y + collider.h) > i.collider.y)
        {
            weapon_.push_back(i.attack_);
            i.picked = true;
        }
    }

    for (auto i : wps)
    {
        if (i.picked)
        {
            if (!shooting)
            {
                i.collider.x = x_ + w_;
                i.collider.y = y_;
            }
            else
            {
                i.collider.x += 6;

                SDL_RenderCopy(i.renderer_, i.texture_, NULL, &i.collider);

                if (i.collider.x > SCREEN_WIDTH)
                {
                    shooting = false;
                }
            }
        }
    }

    /*
        if (collider.x < (target.collider.x + target.collider.w) && (collider.x + collider.w) > target.collider.x &&
            collider.y < (target.collider.y + target.collider.h) && (collider.y + collider.h) > target.collider.y)
        {
            // weapon_.push_back(target.attack_);
            target.picked = true;
            taking_weapon = true;
        }

        if (!shooting)
        {
            target.collider.x = x_ + w_;
            target.collider.y = y_;
        }
        else
        {
            if (target.picked)
            {
                target.collider.x += 6;

                SDL_RenderCopy(target.renderer_, target.texture_, NULL, &target.collider);

                if (target.collider.x > SCREEN_WIDTH)
                {
                    shooting = false;
                }
            }
        }*/
}

void Player::attacked(Fodder &fod)
{
    if (collision(fod) == true)
    {
        hp_ -= fod.getatk();
    }

    if (hp_ <= 0)
    {
        SDL_DestroyTexture(texture_);
        SDL_DestroyTexture(texture2_);
        SDL_DestroyTexture(texture3_);
        SDL_DestroyTexture(texture4_);
    }
}
