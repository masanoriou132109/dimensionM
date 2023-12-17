#include "level.hpp"

Level::void start()
{
	//開始撥放音樂、等待幾秒
	//把玩家放到要的位置
	//顯示文字 
	 //If there is no music playing
	started = true;
    if( Mix_PlayingMusic() == 0 )
    {
        //Play the music
        Mix_PlayMusic( backgrounds.music, -1 );
    }
    
}

Level::void end()
{
	//把東西都刪掉 deallocate == NULL 之類的 
	Mix_HaltMusic();
	started = false;
}

Level::void excute()
{
	blablabla
	checkcollision();
	blablabla
}


