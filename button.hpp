
#ifndef BUTTON_HPP
#define BUTTON_HPP
#include "entity.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <stdio.h>
#include <string>

enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
};

const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

class Button : public Entity
{

  private:
    SDL_Event *e;
    SDL_Texture *texture2_; // 精靈圖
    SDL_Texture *texture3_;

    LButtonSprite state = BUTTON_SPRITE_MOUSE_OUT; // 滑鼠狀態

    bool isInside; // 滑鼠是否在按鈕上

  public:
    Button(
        SDL_Renderer *global_renderer, std::string image_path, std::string image_path_inside,
        std::string image_path_click, int p_x, int p_y, int p_w, int p_h, SDL_Event *global_event,
        void (*mouse_event)()) // 除了entity原有的還要丟event和按下滑鼠之後要幹嘛(mouse_event) 以及按下和移上去的精靈圖
        : Entity(global_renderer, image_path, p_x, p_y, p_w, p_h),
          texture2_(IMG_LoadTexture(global_renderer, image_path_inside.c_str())),
          texture3_(IMG_LoadTexture(global_renderer, image_path_click.c_str())), e(global_event), do_(mouse_event){};

    ~Button();

    void display();
    void handle_event(SDL_Event *e); // 這個函式要丟到while (SDL_PollEvent(&e) != 0)下面
    void (*do_)();                   // 按了要做什麼
};

#endif // BUTTON_HPP
