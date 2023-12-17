#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "level.hpp"
#include "button.hpp"
#include <string>
string monster_image[5] = {"","","","",""};
int monster_x[5] = { , , , , };
int monster_y[5] = { , , , , };
int monster_w[5] = { , , , , };
int monster_h[5] = { , , , , };


enum GameState
{
	s_menu = 0;
	s_playing = 1;
	s_pausing = 2;
	s_next_Level = 3;
}

enum Monster
{
	_constant = 0;
	_trigonalmetric = 1;
	_exponential = 2;
	_logarithm = 3;
	_polynomial = 4;
	monster_num = 5;
}
class Gamemanager
{
	private:
		SDL_Window* g_window;
	    SDL_Renderer* g_renderer;
	    Uint64 startTime;
	    SDL_Event e;
	    const Uint8 *key_state = SDL_GetKeyboardState(NULL);
	    
	    std::vector<Level*> levels;
	    Level CurrentLevel;
	    Menu themenu;
	    Pause thepause;
	    
	    GameState currentstate;
	    quit = false;
	    
	    Player* penguin; // Player裡面多一個 bool 變數 invisible 在Player.render()的時候由Player class本身決定要不要render出來
	    std::vector<Fodder> monsters; //存不同的 Fodder們 
	    
		 
	public:
		Gamemanager
		void initSDL();
		void closeSDL();
		void handleEvents();
		void render();
		void run();
		void loadLevel();
}
#endif
