#include "button.hpp"

void Button::set_source(int p_w, int p_h)
{

    rect_clip = new SDL_Rect[4];
    for (int i = 0; i < 4; i++)
    {
        rect_clip[i].h = p_h;
        rect_clip[i].w = p_w;
        rect_clip[i].x = 0;
        rect_clip[i].y = i * p_h;
    }
}

void Button::display()
{
    SDL_RenderCopyEx(renderer_, texture_, &rect_clip[mCurrentSprite], &on_window_, 0, NULL, SDL_FLIP_NONE);
}

void Button::handle_event(SDL_Event *e)
{
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {

        // Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        // Check if mouse is in button
        bool inside = false;

        // Mouse is left of the button
        if (x > x_ && x < x_ + w_ && y > y_ && y < y_ + h_)
        {
            inside = true;
        }
        // Mouse is right of the button

        // Mouse is outside button
        if (!inside)
        {
            mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        }
        // Mouse is inside button
        else
        {
            // Set mouse over sprite
            switch (e->type)
            {
            case SDL_MOUSEMOTION:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;

            case SDL_MOUSEBUTTONDOWN:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                do_();
                break;

            case SDL_MOUSEBUTTONUP:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;

                break;
            }
        }
    }
}

Button::~Button()
{
    SDL_DestroyTexture(texture_);
    delete[] rect_clip;
}