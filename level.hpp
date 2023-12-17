#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include <iostream>
#include "entity.hpp"
#include "solid.hpp"
#include "mob.hpp"
#include "button.hpp"
#include "background.hpp"
#include "weapon.hpp"

enum GameState
{
	Menu = 0;
	Playing = 1;
	Pausing = 2;
}


class Menu
{
	private:
		Button press_to_start_game;
		Button press_to_quit_game;
		Background menu_background;
		bool started;
	public:
		bool isStarted()
		{
			return started;
		}
		Menu():started(false){};
		void start()
		{
			started = true;
			if( Mix_PlayingMusic() == 1 )
			{
				Mix_HaltMusic();
			} 
			if( Mix_PlayingMusic() == 0 )
		    {
		        //Play the music
		        Mix_PlayMusic( menu_background.music, -1 );
		    }
		}
		void end()
		{
			started = false;
			if( Mix_PlayingMusic() == 1 )
			{
				Mix_HaltMusic();
			}
		}
		void handle_event(SDL_event* e, GameState &currentstate, bool &quit)
		{
			if( /*press_to_start_game*/)
			{
				currentstate = playing;
				end();
			}
			if( /*press_to_quit_game*/)
			{
				quit = true;
			}
		}
		void render()
		{
			menu_background.render();
			/* Button.render */; 
		}
}

class Level
{
	protected:
		int stage_num; //有幾小關 
		//::vector<Background*> backgrounds; //每一關的背景 
		Background backgrounds; //先一關一個就好 
		Button* buttons; //左上角按暫停的按鈕 
		bool pause; //是否暫停
		bool started;
		std::vector<vector<Fodder*>> fodders;
		//小怪 、角色 blablabla 
	public:
		Level()
		{
		}
		~Level()
		{
		}
		bool isStarted()
		{
			return started;
		}
		void start(); //開始這個關卡 
		void end(); //結束這個關卡 
		void excuting(); // 用來跑這關裡面全部的物件 
		void checkcollision(); // 全部的玩家 BOSS小怪 都對solid或彼此執行其檢查碰撞的function 
		void render();
}


class Pause
{
	private:
		Button resume_game;
		Button back_to_menu;
	public:
		void start();
		void end();
		void handle_event(SDL_event* , GameState &currentstate, bool &quit , Level* thelevel)
		{
			if( Mix_PlayingMusic() == 1)
			{
				Mix_PauseMusic();
			}
			if( /*resume_game is pressed*/)
			{
				if( Mix_PausedMusic() == 1)
				{
					Mix_ResumeMusic();
				}
			}
			if( /*back_to_menu is pressed*/)
			{
				thelevelend();
			}
		} 
		void render();
}
