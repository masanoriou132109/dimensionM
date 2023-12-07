/*This source code copyrighted by Lazy Foo' Productions 2004-2023
and may not be redistributed without written permission.*/

// Using SDL, SDL_image, standard IO, and strings
#ifndef BUTTON_HPP
#define BUTTON_HPP
#include "entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include <stdio.h>
#include <string>

enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
};

const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

class Button : public Entity
{
  public:
    Button(SDL_Renderer *global_renderer, std::string image_path, int p_x, int p_y, SDL_Event *global_event)
        : Entity(global_renderer, image_path, p_x, p_y), e(global_event){};
    void set_source(int p_w, int p_h);
    void display();
    void handle_event(SDL_Event *e);

  private:
    LButtonSprite mCurrentSprite;
    SDL_Event *e;
    int button_w, button_h;
    SDL_Rect *rect_clip;
    SDL_Rect on_window;
};

#endif // BUTTON_HPP
