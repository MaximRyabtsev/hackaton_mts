#define SDL_MAIN_USE_CALLBACKS 1

#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

SDL_AppResult  SDL_AppInit(void** appstate, int argc, char* argv[]){
	SDL_SetAppMetadata("Example Renderer Clear", "1.0", "com.example.renderer-clear");
	if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
	
    if (!SDL_CreateWindowAndRenderer("examples/renderer/clear", 640, 480, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
	TTF_Init();

	return SDL_APP_CONTINUE;
}



SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event){
	switch (event->type){
		case SDL_EVENT_QUIT:
			return SDL_APP_SUCCESS;
		case SDL_EVENT_KEY_DOWN:
			printf("\n");
			if(event->key.scancode == 4){
				printf("\n");
			}
			break;

		case SDL_EVENT_KEY_UP:
			break;

		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			printf("\n");
			if(event->button.button == 'f' | event->button.x == 77){}
			break;

	}
	return SDL_APP_CONTINUE;
}


int a = 1;
SDL_AppResult SDL_AppIterate(void* appstate){
	uint64_t b = SDL_GetTicks();
	SDL_SetRenderDrawColor(renderer, 0, 250, 0, 255);
	SDL_RenderClear(renderer);
	uint64_t c = SDL_GetTicks() - b;
	SDL_Delay(16-c);


	SDL_RenderPresent(renderer);
	return SDL_APP_CONTINUE; 
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}