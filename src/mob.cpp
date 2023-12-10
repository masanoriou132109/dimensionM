#include "mob.hpp"

void Mob::set_source(int p_w, int p_h, int num_of_sprite, int p_how)
{
    rect_clip = new SDL_Rect[num_of_sprite];
    num_of_sprite_ = num_of_sprite;

    if (p_how == 1)
    {
        for (int i = 0; i < num_of_sprite; i++)
        {
            rect_clip[i].h = p_h;
            rect_clip[i].w = p_w;
            rect_clip[i].x = 0;
            rect_clip[i].y = i * p_h;
        }
    }
    else
    {
        for (int i = 0; i < num_of_sprite; i++)
        {
            rect_clip[i].h = p_h;
            rect_clip[i].w = p_w;
            rect_clip[i].x = i * p_w;
            rect_clip[i].y = 0;
        }
    }
}

void Mob::handle_event(const Uint8 *p_keystate, SDL_Event *e)
{
    if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_f)
    {
        if (dimension_ == 3)
        {
            dimension_ = 2;
        }
        else
        {
            dimension_ = 3;
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
        sprite++;
        if (sprite == num_of_sprite_)
        {
            sprite = 0;
        }
    }
}

void Mob::display()
{

    if (dimension_ == 3)
    {
        if (isJumping == true)
        {
            std::cerr << "is jumping\n";
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
            SDL_RenderCopyEx(renderer_, texture_, &rect_clip[sprite], &on_window_, 0, NULL, SDL_FLIP_HORIZONTAL);
        }
        else
        {
            SDL_RenderCopyEx(renderer_, texture_, &rect_clip[sprite], &on_window_, 0, NULL, SDL_FLIP_NONE);
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
            SDL_RenderCopyEx(renderer_, texture_, &rect_clip[sprite], &on_window_, 0, NULL, SDL_FLIP_HORIZONTAL);
        }
        else
        {
            SDL_RenderCopyEx(renderer_, texture_, &rect_clip[sprite], &on_window_, 0, NULL, SDL_FLIP_NONE);
        }
        vel_x = 0;
        vel_y = 0;
    }
    collider = {x_, y_, w_, h_};
    SDL_Delay(5);
}
