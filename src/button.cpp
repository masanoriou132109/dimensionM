#include "button.hpp"

void Button::display()
{
    std::cerr << state << '\n';
    switch (state)
    {
    case BUTTON_SPRITE_MOUSE_OUT:
        SDL_RenderCopyEx(renderer_, texture_, NULL, &on_window_, 0, NULL, SDL_FLIP_NONE);
        break;

    case BUTTON_SPRITE_MOUSE_OVER_MOTION:
        SDL_RenderCopyEx(renderer_, texture2_, NULL, &on_window_, 0, NULL, SDL_FLIP_NONE);
        break;

    case BUTTON_SPRITE_MOUSE_DOWN:
        SDL_RenderCopyEx(renderer_, texture3_, NULL, &on_window_, 0, NULL, SDL_FLIP_NONE);
        break;
    case BUTTON_SPRITE_MOUSE_UP:
        SDL_RenderCopyEx(renderer_, texture2_, NULL, &on_window_, 0, NULL, SDL_FLIP_NONE);
        break;
    }
}

void Button::handle_event(SDL_Event *e)
{
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {

        // Get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        // Check if mouse is in button
        inside = false;

        // Mouse is left of the button
        if (x > x_ && x < x_ + w_ && y > y_ && y < y_ + h_)
        {
            inside = true;
        }
        // Mouse is right of the button

        // Mouse is outside button
        if (!inside)
        {
            state = BUTTON_SPRITE_MOUSE_OUT;
        }
        // Mouse is inside button
        else
        {
            // Set mouse over sprite
            switch (e->type)
            {
            case SDL_MOUSEMOTION:
                state = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;

            case SDL_MOUSEBUTTONDOWN:
                state = BUTTON_SPRITE_MOUSE_DOWN;
                do_();
                break;
            case SDL_MOUSEBUTTONUP:
                state = BUTTON_SPRITE_MOUSE_UP;
                break;
            }
        }
    }
}

Button::~Button()
{
    SDL_DestroyTexture(texture_);
}