
#ifndef ENTITY_H
#define ENTITY_H
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

class Entity
{
  protected:
    float x_, y_, w_, h_;
    SDL_Texture *texture_;
    SDL_Renderer *renderer_;
    SDL_Rect on_window_;

  public:
    Entity(){};
    Entity(SDL_Renderer *global_renderer, std::string image_path, int p_x, int p_y, int p_w,
           int p_h); // 傳入renderer, 圖片檔, 實體x、y座標, 長寬
    ~Entity();
    virtual void display();
    // 宣告這個才會顯示（因為每個東西display的timimg跟方式不太一樣我就寫成virtual function）
    // 但這沒包含SDL_RenderPresent(renderer)，我不知道為什麼這個要宣告在主程式才能用，不然開兩個東西就會閃
};
#endif // ENTITY_H