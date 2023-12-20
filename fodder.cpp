#include "fodder.hpp"


Fodder::Fodder(SDL_Renderer *global_renderer, math_kind p_math, int p_x, int p_y, int p_w, int p_h, Polygon p_poly)
    : Mob(global_renderer, " ", float(p_x), float(p_y), float(p_w), float(p_h), NULL, 0), con_(p_math), _poly(p_poly)
{

    hp_ = (float(p_math) + 1) * 100;
    atk_ = (p_math + 1) * 10;

    std::cerr << "hp = " << hp_ << '\n';


    switch (p_math)
    {
    case CONST:
        texture_ = IMG_LoadTexture(renderer_, "C.png");
        break;
    case POLY:
        texture_ = IMG_LoadTexture(renderer_, "A.png");
        break;
    case TRIG:
        texture_ = IMG_LoadTexture(renderer_, "T.png");
        break;
    case EXPO:
        texture_ = IMG_LoadTexture(renderer_, "E.png");
        break;
    case LOGA:
        texture_ = IMG_LoadTexture(renderer_, "L.png");
        break;
    default:
        break;
    }
}

void Fodder::display(Player &ply, std::vector<Solid *> obst)
{ 

    if (collision(ply.bullet))
    { 

        switch (con_) 
        {
        case CONST:
            switch (ply.shooting) 
            {
            case DIFFERENTIATE:
                hp_ = 0;
                break;
            case INTEGRATION:
                hp_ *= 0.36;
                break;
            case LOGARITHM:
                hp_ *= 0.94;
                break;
            case DE_FOURIER:
                hp_ *= 0.15;
                break;
            case TAYLOR_SERIES:
                hp_ *= 0.2;
                break;
            case LAPLACE_TRANS:
                hp_ *= 0.98;
                break;
            default:
                break;
            }
            break;

        case TRIG:
            switch (ply.shooting)
            {
            case DIFFERENTIATE:
                hp_ *= 0.94; 
                break;
            case INTEGRATION:
                hp_ *= 0.52;
                break;
            case LOGARITHM:
                hp_ *= 0.92;
                break;
            case TAYLOR_SERIES:
                hp_ *= 1.54;
                con_ = POLY; 
                break;
            case DE_FOURIER:
                hp_ *= 0;
                break;
            case LAPLACE_TRANS:
                hp_ *= 0.4;
                break;
            default:
                break;
            }
            break;

        case LOGA:
            switch (ply.shooting)
            {
            case DIFFERENTIATE:
                hp_ *= 0.68;
                break;
            case INTEGRATION:
                hp_ *= 0.44;
                break;
            case LOGARITHM:
                hp_ *= 1.12;
                break;
            case TAYLOR_SERIES:
                hp_ *= 0.46;
                con_ = POLY; 
                break;
            case DE_FOURIER:
                hp_ *= 0.48;
                con_ = TRIG; 
                break;
            case LAPLACE_TRANS:
                hp_ *= 0.7;
                break;
            default:
                break;
            }
            break;

        case POLY:
            switch (ply.shooting)
            {
            case DIFFERENTIATE:
                hp_ *= 0.5;
                break;
            case INTEGRATION:
                hp_ *= 0.64;
                atk_ += 10; // 傷害提升
                break;
            case LOGARITHM:
                hp_ *= 0.82;
                break;
            case TAYLOR_SERIES:
                hp_ *= 0;
                break;
            case DE_FOURIER:
                hp_ *= 0.02;
                break;
            case LAPLACE_TRANS:
                hp_ *= 0.31;
                break;
            default:
                break;
            }
            break;

        case EXPO:
            switch (ply.shooting)
            {
            case DIFFERENTIATE:
                hp_ *= 0.94;
                atk_ *= 1.6; // 傷害提升
                w_ *= 1.5;
                h_ *= 1.5; // 變大
                break;
            case INTEGRATION:
                hp_ += 10;
                atk_ -= 10; // 傷害提升
                break;
            case LOGARITHM:
                hp_ *= 0.2;
                break;
            case TAYLOR_SERIES:
                hp_ *= 0.46;
                // con_ = POLY; // 變成多項式
                break;
            case DE_FOURIER:
                hp_ *= 0.16;
                // con_ = TRIG; // 變成三角
                break;
            case LAPLACE_TRANS:
                hp_ *= 0.8;
                break;
            default:
                break;
            }
            break;

        default:
            break;
        }
        isHit = true;
        ply.shooting = NONE;             // 一打到就重設玩家（讓子彈消失）
        ply.isShooting = false;          // 一打到就重設
        ply.bullet = {2000, 2000, 0, 0}; // 一打到就重設
        std::cerr << "now hp=" << hp_ << '\n';
    }

    if (hp_ > 0)
    {
        Vector direction(ply.collider.x - x_, ply.collider.y - y_); // 小怪到玩家的向量

        if (con_ == CONST || con_ == LOGA || con_ == POLY) // 咬人怪
        {
            for (auto i : obst)
            {
                Vector to_obst(i->collider.x - x_, i->collider.y - y_); // 到障礙物的向量

                if (to_obst.length() < 50 && direction.unit_x * to_obst.unit_x + direction.unit_y * to_obst.unit_y > 0)
                { // 如果朝向障礙物就慢一點
                    x_ += direction.unit_x * 0.3 * speed_;
                    y_ += direction.unit_y * 0.3 * speed_;
                }
                else
                {
                    x_ += direction.unit_x * speed_;
                    y_ += direction.unit_y * speed_;
                }
            }
        }
        else // 火槍兵 // 攻擊方式我還沒想好怎麼寫
        {
            for (auto i : obst)
            {
                Vector to_obst(i->collider.x - x_, i->collider.y - y_); // 到障礙物的向量

                if (to_obst.length() < 50 && direction.unit_x * to_obst.unit_x + direction.unit_y * to_obst.unit_y > 0)
                {                                // 如果朝向障礙物就慢一點
                    if (direction.length() > 50) // 離玩家50 pixels以上才走向玩家
                    {
                        x_ += direction.unit_x * 0.3 * speed_;
                        y_ += direction.unit_y * 0.3 * speed_;
                    }
                }
                else
                {
                    if (direction.length() > 50)
                    {
                        x_ += direction.unit_x * speed_;
                        y_ += direction.unit_y * speed_;
                    }
                }
            }
        }

        collider = {int(x_), int(y_), int(w_),
                    int(h_)}; // 更新螢幕上位置與碰撞箱（其實這兩個有點重複，要修改的話在solid裡面找）
        on_window_ = {int(x_), int(y_), int(w_), int(h_)};

        SDL_RenderCopy(renderer_, texture_, NULL, &on_window_);
    }
    else
    {
        std::cerr << "fod has dead\n"; // 加入死亡效果
    }
}

// 玩家部分

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
    if (hp_ > 0)
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
        else
        {
            bullet = {2000, 2000, 0, 0};
        }

        collider = {int(x_), int(y_), int(h_), int(w_)};
        SDL_Delay(10);
    }
    else
    {
        // SDL_Quit();
    }
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
        if (collider.x < (i->collider.x + i->collider.w) && (collider.x + collider.w) > i->collider.x &&
            collider.y < (i->collider.y + i->collider.h) && (collider.y + collider.h) > i->collider.y)
        {
            hp_ -= i->atk_;
        }

        if (!i->collision(bullet))
        {
            i->isHit = false;
        }
    }

    for (auto i : obst)
    {
        if (collider.x < (i->collider.x + i->collider.w) && (collider.x + collider.w) > i->collider.x &&
            collider.y < (i->collider.y + i->collider.h) && (collider.y + collider.h) > i->collider.y)
        {
            x_ -= vel_x;
            y_ -= vel_y;
        }
    }
}





//�ڼg�n�˥��F�A�i�H����� 
//���ئn�I��
//�u�n��Ϥ���m
// 
