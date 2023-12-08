
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "entity.hpp"
#include <iostream>
#include <string>

class RenderWindow
{
  public:
    RenderWindow(std::string title, int p_w, int p_h);
    SDL_Texture *loadTexture(std::string path);
    void cleanUP();
    void clear();
    void display();
    SDL_Window *window;
    SDL_Renderer *renderer;

  private:
};
