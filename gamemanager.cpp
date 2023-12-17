#include "gamemanager.hpp"
void Gamemanager::initSDL()
{
	startTime = SDL_GetPerformanceCounter();
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    g_window = NULL;
    g_renderer = NULL;

    g_window = SDL_CreateWindow("DimensioM", 0, 0, SCREEN_WIDTH,
                                SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (g_window == NULL)
    {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
    }
    g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

    if (g_renderer == NULL)
    {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    }
    else
    {
        // Initialize renderer color
        SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

        // Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags))
        {
            printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        }
    }
    //初始化玩家 
	penguin = new Player(g_renderer, "../images/1.png", 30, 500, 100, 100, &e, 10, 300);
    penguin->set_source("../images/2.png", "../images/4.png", "../images/3.png");
    //初始化小怪 
    for( int i=0 ; i < monster_num ; i++)
    {
    	monster.push_back(new Fodder(g_renderer,monster_image[i],monster_x[i],monster_y[i],monster_w[i],monster_h[i],&e,0,/*mathkind*/));
	}
	//初始化關卡
	themenu = Menu();
	loadLevel();
	thepause = Pause();
	currentstate = s_menu;
	CurrentLevel = 0;
}

void Gamemanager::closeSDL()
{
	//關掉
	// 解放
	//  之類的 
}

void Gamemanager::handleEvents()
{
	SDL_PollEvent(&e);

    if (e.type == SDL_QUIT)
    {
        quit = true;
        return;
    }
    
	switch (currentstate) // 簡單來說 handleEvent是更改數據，render是顯示 
	{
		case (s_menu):
			if(!themenu.isStarted())
			{
				themenu.start();
			}
			themenu.handle_event(&e ,currentstate, quit);
			break;
		//	若Start按鈕被按下 則Level1.start();
		//	state = playing
		case (s_playing):
			if (!levels[CurrentLevel]->isStarted())
			{
				levels[CurrentLevel]->start();
			}
			levels[CurrentLevel]->handle_event(&e , currentstate, quit, );
			//player的handle event 
			break;
		//	則 handle : Level裡面的東西、角色碰撞、攻擊、 然後改變他們的x y 要不要顯示之類的 
		//	若 Pause 按鈕被按下 則state = pause
		case (s_pausing) :
			thepause.handle_event(&e, currentstate , quit);
			//	則handle: 按鈕
		//	若resume被按下 則
		//	若restart被按下 則level重置
		//	若Back_to_menu被按下 則level.end() , state = menu; 
			break;
		case (s_next_level):
			CurrentLevel++;
			levels[currentlevel]->start();
			currentstate = s_playing;
			break;
	}
}

void Gamemanager::render()
{
	switch (currentstate)
	{
		case ( menu ):
			themenu.render();
			break;
		case ( playing ):
			levels[CurrentLevel].render(g_renderer); // 渲染關卡
            penguin->render(); // 渲染玩家
            break;
		case ( pause ) :
			thepause.render();
			break;
	}
}

void Gamemanager::run()
{
	initSDL();
	while(!quit)
	{
		handleEvents();
		render();
	}
	closeSDL();
}

void Gamemanager::loadLevel
{
	//這裡是一次性載入關卡，是最繁瑣的地方 
	//level 1
		blablabla
	//level 2
		flaflafla
	//level 3
		olaolaola
}
