
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
    Button(SDL_Renderer *global_renderer, std::string image_path, int p_x, int p_y, int p_w, int p_h,
           SDL_Event *global_event,
           void (*mouse_event)()) // 除了entity原有的還要丟event和按下滑鼠之後要幹嘛(mouse_event)
        : Entity(global_renderer, image_path, p_x, p_y, p_w, p_h), e(global_event), do_(mouse_event){};
    ~Button();
    void set_source(int p_w, int p_h); // 這可以設定在來源圖片裡你一個按鈕要框的大小(像lazy foo 那個就是300*200)
    void display();
    void handle_event(SDL_Event *e); // 這個函式要丟到while (SDL_PollEvent(&e) != 0)下面

  private:
    LButtonSprite mCurrentSprite;
    SDL_Event *e;
    SDL_Rect *rect_clip;
    void (*do_)();
};

#endif // BUTTON_HPP
