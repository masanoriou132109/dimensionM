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

    if (p_keystate[SDL_SCANCODE_G] && !isShooting)
    {
        for (auto i : weapon_)
        {
            if (i == DIFFERENTIATE)
            {
                shooting = DIFFERENTIATE;
                isShooting = true;
                bullet = {on_window_.x, on_window_.y, 100, 50};
                if (face == LEFT)
                {
                    bullet_dir = {-4, 0};
                }
                else
                {
                    bullet_dir = {4, 0};
                }
                break;
            }
        }
    }

    if (p_keystate[SDL_SCANCODE_H] && !isShooting)
    {
        for (auto i : weapon_)
        {
            if (i == INTEGRATION)
            {
                shooting = INTEGRATION;
                isShooting = true;
                bullet = {on_window_.x, on_window_.y, 100, 50};
                if (face == LEFT)
                {
                    bullet_dir = {-4, 0};
                }
                else
                {
                    bullet_dir = {4, 0};
                }
                break;
            }
        }
    }

    if (p_keystate[SDL_SCANCODE_J] && !isShooting)
    {
        for (auto i : weapon_)
        {
            if (i == DE_FOURIER)
            {
                shooting = DE_FOURIER;
                isShooting = true;
                bullet = {on_window_.x, on_window_.y, 100, 50};
                if (face == LEFT)
                {
                    bullet_dir = {-4, 0};
                }
                else
                {
                    bullet_dir = {4, 0};
                }
                break;
            }
        }
    }

    if (p_keystate[SDL_SCANCODE_K] && !isShooting)
    {
        for (auto i : weapon_)
        {
            if (i == TAYLOR_SERIES)
            {
                shooting = TAYLOR_SERIES;
                isShooting = true;
                bullet = {on_window_.x, on_window_.y, 100, 50};
                if (face == LEFT)
                {
                    bullet_dir = {-4, 0};
                }
                else
                {
                    bullet_dir = {4, 0};
                }
                break;
            }
        }
    }

    if (p_keystate[SDL_SCANCODE_L] && !isShooting)
    {
        for (auto i : weapon_)
        {
            if (i == LAPLACE_TRANS)
            {
                shooting = LAPLACE_TRANS;
                isShooting = true;
                bullet = {on_window_.x, on_window_.y, 100, 50};
                if (face == LEFT)
                {
                    bullet_dir = {-4, 0};
                }
                else
                {
                    bullet_dir = {4, 0};
                }
                break;
            }
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
        else // not jumping
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
        else // face == LEFT
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
    else // dimension == 2
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
        else // face == LEFT
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

    if (isShooting)
    {
        bullet.x += bullet_dir.x * 3;
        bullet.y += bullet_dir.y * 3;
        switch (shooting)
        {
        case DIFFERENTIATE:
            SDL_RenderCopy(renderer_, atk1, NULL, &bullet);
            break;
        case INTEGRATION:
            SDL_RenderCopy(renderer_, atk2, NULL, &bullet);
            break;
        case DE_FOURIER:
            SDL_RenderCopy(renderer_, atk3, NULL, &bullet);
            break;
        case TAYLOR_SERIES:
            SDL_RenderCopy(renderer_, atk4, NULL, &bullet);
            break;
        case LAPLACE_TRANS:
            SDL_RenderCopy(renderer_, atk5, NULL, &bullet);
            break;
        default:

            break;
        }

        if (bullet.x < 0 || bullet.x > 1280 || bullet.y > 720 || bullet.y < 0)
        {
            isShooting = false;
            shooting = NONE;
            bullet = {int(x_), int(y_), 0, 0};
        }
    }

    collider = {int(x_), int(y_), int(h_), int(w_)};
    SDL_Delay(10);
}

void Player::detect(std::vector<Weapon *> wps, std::vector<Fodder *> fods, std::vector<Solid *> obst)
{
    for (auto i : wps)
    {
        if (collider.x < (i->collider.x + i->collider.w) && (collider.x + collider.w) > i->collider.x &&
            collider.y < (i->collider.y + i->collider.h) && (collider.y + collider.h) > i->collider.y)
        {
            weapon_.push_back(i->attack_);
            i->picked = true;
        }
    }

    for (auto i : fods)
    {
        if (collide(cir_, i->shape))
        {
            x_ += 2 * i->vel_x;
            y_ += 2 * i->vel_y;
        }
        hp_ -= i->atk_;
    }

    for (auto i : obst)
    {
        if (collide(cir_, i->shape))
        {
            x_ -= vel_x;
            y_ -= vel_y;
        }
    }
}