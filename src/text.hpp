#include "entity.hpp"

class Text : public Entity
{
  private:
    std::string text_;
    float x_, y_, w_, h_;
    SDL_Texture *texture_;
    SDL_Renderer *renderer_;
    SDL_Rect on_window_;
    TTF_Font *font_;
    SDL_Color colour = {0, 0, 0, 255};

  public:
    Text(SDL_Renderer *global_renderer, std::string p_text, std::string p_font, float p_x, float p_y, float p_w,
         float p_h, int p_size);
    ~Text();
    void display(bool p_event, int p_time);
    void release();
};

Text::Text(SDL_Renderer *global_renderer, std::string p_text, std::string p_font, float p_x, float p_y, float p_w,
           float p_h, int p_size)
    : renderer_(global_renderer), x_(p_x), y_(p_y), w_(p_w), h_(p_h), text_(p_text)
{
    font_ = TTF_OpenFont(p_font.c_str(), p_size);
    SDL_Surface *textSurface = TTF_RenderText_Blended(font_, p_text.c_str(), colour);

    if (!textSurface)
    {
        // Handle rendering failure
        throw std::runtime_error("Failed to render text");
    }

    texture_ = SDL_CreateTextureFromSurface(renderer_, textSurface);
    if (!texture_)
    {
        // Handle texture creation failure
        SDL_FreeSurface(textSurface);
        throw std::runtime_error("Failed to create texture");
    }

    SDL_FreeSurface(textSurface);

    on_window_ = {int(x_), int(y_), int(w_), int(h_)};
}

void Text::display(bool p_event, int p_time)
{
    if (p_event)
    {
        SDL_RenderCopy(renderer_, texture_, NULL, &on_window_);
        SDL_Delay(p_time);
        release();
    }
}

Text::~Text()
{
    TTF_CloseFont(font_);
    SDL_DestroyTexture(texture_);
}

void Text::release()
{
    TTF_CloseFont(font_);
    SDL_DestroyTexture(texture_);
}