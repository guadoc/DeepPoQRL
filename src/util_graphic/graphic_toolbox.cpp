
#ifndef TABLE_LIB_UTILS_H_
#define TABLE_LIB_UTILS_H_

#include "../StdAfx.h"

using namespace std;
//	static char get_char_from_sdlkey(SDL_Keycode key, SDL_Keymod mod)
//	{
//	    char ret = 0;
//	    if(key >= SDLK_0 && key <= SDLK_9)
//	       ret = key - SDLK_0 + '0';
//	    else if(key >= SDLK_0 && key <= SDLK_9)
//	       ret = key - SDL_SCANCODE_0 + '0';
//	    else if(key >= SDLK_a && key <= SDLK_z)
//	       ret = key - SDLK_a + (mod&KMOD_SHIFT? 'A' : 'a');
//	    return ret;
//	}

static void plot(list<unsigned int> list, int max_value, int min_value, int n_points_max){
		std::list<unsigned int>::iterator value_list_it = list.begin();
		unsigned int min_val = *value_list_it;
		unsigned int max_val = *value_list_it;
		while (value_list_it != list.end()){
			unsigned int val = *value_list_it;
			if (val > max_val){
				max_val = val;
			}
			else if(val< min_val){
				min_val = val;
			}
			value_list_it++;
		}
		unsigned int y_size = 400;//min(400, (int)max_val - (int)min_val);
		float scale = (float) y_size / (float)(max_val - min_val);

		int list_size = list.size();
		int n_point = min(list_size, n_points_max);
		unsigned int factor = (unsigned int) ceil((float) list.size()/(float) n_point);

		unsigned int w_x_size = n_point;//max((int)n_point, 300);
		unsigned int w_y_size = y_size + 40;
		SDL_Point points[n_point];
		value_list_it = list.begin();
		for ( int i = 0; i< n_point; i++){
			int val = 0;
			for (unsigned int j = 0; j<factor; j++){
				val += *value_list_it;
				value_list_it++;
			}
			points[i] = {i, (int)(scale*(float)((int)max_val - (int)((float)val/(float)factor)))};
		}
		if (SDL_Init(SDL_INIT_VIDEO) == 0) {
				SDL_Window* window = NULL;
				SDL_Renderer* renderer = NULL;
				if (SDL_CreateWindowAndRenderer(w_x_size, w_y_size, 0, &window, &renderer) == 0) {
					SDL_bool done = SDL_FALSE;
					while (!done) {
						SDL_Event event;
						SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
						SDL_RenderClear(renderer);

						SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
						SDL_RenderDrawLines(renderer, points, n_point);
						SDL_RenderPresent(renderer);

//						done = SDL_TRUE;
						while (SDL_PollEvent(&event)) {

							switch(event.type)
								{
								case SDL_WINDOWEVENT:
									switch(event.window.event)
									{
									case SDL_WINDOWEVENT_CLOSE:
										done = SDL_TRUE;
										cout << "Closing window" << endl;
										break;
									}
									break;
								}
						}
					}
				}
				if (renderer) {
					SDL_DestroyRenderer(renderer);
				}
				if (window) {
					SDL_DestroyWindow(window);
				}
			}
			SDL_Quit();
	}



static void plot(list<int> list, int max_value, int min_value, int n_points_max){
	std::list< int>::iterator value_list_it = list.begin();
	int min_val = *value_list_it;
	int max_val = *value_list_it;
	while (value_list_it != list.end()){
		int val = *value_list_it;
		if (val > max_val){
			max_val = val;
		}
		else if(val< min_val){
			min_val = val;
		}
		value_list_it++;
	}
	unsigned int y_size = 400;//min(400, (int)max_val - (int)min_val);
	float scale = (float) y_size / (float)(max_val - min_val);

	int list_size = list.size();
	int n_point = min(list_size, n_points_max);
	int factor = (unsigned int) ceil((float) list.size()/(float) n_point);

	unsigned int w_x_size = n_point;//max((int)n_point, 300);
	unsigned int w_y_size = y_size + 40;
	SDL_Point points[n_point];
	value_list_it = list.begin();
	for ( int i = 0; i< (int)n_point; i++){
		int val = 0;
		for (int j = 0; j<factor; j++){
			val += *value_list_it;
			value_list_it++;
		}
		points[i] = {i, (int)(scale*(float)((int)max_val - (int)((float)val/(float)factor)))};
	}
	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
			SDL_Window* window = NULL;
			SDL_Renderer* renderer = NULL;
			if (SDL_CreateWindowAndRenderer(w_x_size, w_y_size, 0, &window, &renderer) == 0) {
				SDL_bool done = SDL_FALSE;
				while (!done) {
					SDL_Event event;
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
					SDL_RenderClear(renderer);

					SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
					SDL_RenderDrawLines(renderer, points, n_point);
					SDL_RenderPresent(renderer);

//						done = SDL_TRUE;
					while (SDL_PollEvent(&event)) {

						switch(event.type)
							{
							case SDL_WINDOWEVENT:
								switch(event.window.event)
								{
								case SDL_WINDOWEVENT_CLOSE:
									done = SDL_TRUE;
									cout << "Closing window" << endl;
									break;
								}
								break;
							}
					}
				}
			}
			if (renderer) {
				SDL_DestroyRenderer(renderer);
			}
			if (window) {
				SDL_DestroyWindow(window);
			}
		}
		SDL_Quit();
}




#endif /* TABLE_LIB_UTILS_H_ */
