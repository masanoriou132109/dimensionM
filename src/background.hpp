
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include <string>

class Background
{
  public:
    Background(std::string title, int p_w, int p_h);
    ~Background();
    void loadTexture(std::string path);
    void cleanUP();
    void clear();
    void display();
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture_;

  private:
};
