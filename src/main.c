#include <SDL2/SDL.h>
#include <stdio.h>
#include "./constants.h"

int game_is_running = FALSE;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;


int last_frame_time = 0;

struct square{
	float x;
	float y;
	float width;
	float height;
} square;

int initialize_window(void){

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		fprintf(stderr, "Error initializing SDL. \n");
		return FALSE;
	}
	window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);
	if(!window){
		fprintf(stderr, "Error creating window \n");
		return FALSE;
	}
	renderer = SDL_CreateRenderer(window, -1, 0);
	if(!renderer){
		fprintf(stderr, "Error creating renderer \n");
		return FALSE;
	}
		
	return TRUE;
}


void process_input(){
	
	SDL_Event event;
	SDL_PollEvent(&event);
	
	switch (event.type){
		case SDL_QUIT:
			game_is_running = FALSE;
				break;
		case SDL_KEYDOWN:
			if(event.key.keysym.sym == SDLK_ESCAPE)
				game_is_running = FALSE;
					break;
	}
	
	
}

void setup(){
	square.x = 20;
	square.y = 20;
	square.width = 15;
	square.height = 15;
}


void update(){
	
	int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
	
	if(time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME){
		SDL_Delay(time_to_wait);
	}
	
	float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;
	
	last_frame_time = SDL_GetTicks();
	
	square.x += 90 * delta_time;
	square.y += 50 * delta_time;
}

void render(){
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	
	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	SDL_Rect square_rect  = {(int)square.x, (int)square.y, (int)square.width, (int)square.height};
	SDL_RenderFillRect(renderer, &square_rect);
	
	SDL_RenderPresent(renderer);
}

void destroy_window(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(){

	game_is_running = initialize_window();
	
	setup();
	
	while(game_is_running){
		process_input();
		update();
		render();
	}
	
	destroy_window();
	
	return 0;
}
