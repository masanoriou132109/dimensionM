
#include "background.hpp"
#include<iostream>

			
void Background::display()
{
	SDL_RenderCopy( renderer_, texture_, NULL, NULL);
	for( int i = 0 ; i < solid_num ; i++ )
	{
		(*solids[i]).display();
	}
	
}
Background::Background
			( 
				SDL_Renderer *global_renderer, std::string image_path, 
				int solid_num_, int *xs, int *ys, int*ws, int*hs, const char** image_paths, 
				Mix_Music* background_music_ = NULL
			)
				:Entity( global_renderer, image_path ,0 ,0 ,SCREEN_WIDTH, SCREEN_HEIGHT ), 
				solid_num(solid_num_), music(music_)
			{
				for( int i = 0 ; i < solid_num ; i++ )
					{	
						solids.push_back(new Solid(renderer_,image_paths[i],xs[i],ys[i],ws[i],hs[i],NULL));	
					}
			}

