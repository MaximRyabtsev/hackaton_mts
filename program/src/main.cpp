#define SDL_MAIN_USE_CALLBACKS 1

#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include "button.h"
#include "block.h"
#include "page.h"

#if 0
#define err(S) do{\
    const char* err_string = #S;\
    cout << "Couldn't initialize" << err_string;\
    return SDL_APP_FAILURE;\
} while(0)
#endif

int page_number = 0;
std::vector<page*> pages;
#define y_size 750
#define x_size 400
SDL_Color text_color = {0,0,0,0};
block* tert;

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
//0 1 2 -- кнопки меню
std::vector<button *> buttons;
button *testr;

SDL_AppResult  SDL_AppInit(void** appstate, int argc, char* argv[]){
	SDL_SetAppMetadata("Example Renderer Clear", "1.0", "com.example.renderer-clear");
	if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
	
    if (!SDL_CreateWindowAndRenderer("examples/renderer/clear", x_size, y_size, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!TTF_Init()) {
        SDL_Log("Couldn't initialize TTF");
        return SDL_APP_FAILURE;
    }
    pages.push_back(new page());
    pages[0]->rend = renderer;
    pages[0]->backgraund.a = 255; pages[0]->backgraund.g = 100; pages[0]->backgraund.b = 255; pages[0]->backgraund.r = 255;
    //инициализациыя шрифта ------------------------------------------------
    TTF_Font* font = TTF_OpenFont("fonts/main.ttf", 30);
    SDL_Surface* surf = TTF_RenderText_Solid(font, "divece", 5, text_color);
    pages[0]->buttons.push_back(new button(0 , y_size*0.9, x_size/3, y_size*0.1, 0, 200, 200, 255, 0, 100, 100 ,255, 0, SDL_CreateTextureFromSurface(renderer, surf), renderer));
    SDL_DestroySurface(surf);

    surf = TTF_RenderText_Solid(font, "scen", 5, text_color);
    pages[0]->buttons.push_back(new button(x_size/3 , y_size*0.9, x_size/3, y_size*0.1, 0, 200, 200, 255, 0, 100, 100 ,255, 0, SDL_CreateTextureFromSurface(renderer, surf), renderer));
    SDL_DestroySurface(surf);

    surf = TTF_RenderText_Solid(font, "settings", 5, text_color);
    pages[0]->buttons.push_back(new button(x_size/3*2, y_size*0.9, x_size/3, y_size*0.1, 0, 200, 200, 255, 0, 100, 100 ,255, 0, SDL_CreateTextureFromSurface(renderer, surf), renderer));
    SDL_DestroySurface(surf);
    //инициализациыя шрифта ------------------------------------------------
    //инициализациыя шрифта ------------------------------------------------
    surf = TTF_RenderText_Solid(font, "SWIN CHECKING", 13, text_color);
    pages[0]->blocks.push_back( new block(0, 0, 400, 100, 0, 200, 200, 255, 0, 100, 100, 255, 1, SDL_CreateTextureFromSurface(renderer, surf), renderer, IMG_LoadTexture(renderer, "icons/settings.png")));
    SDL_DestroySurface(surf);
    //инициализациыя шрифта ------------------------------------------------

	return SDL_APP_CONTINUE;
}



SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event){
    size_t button_count; 
    int x, y;
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
        //смена цвета кнопки 
            button_count = buttons.size();
            x = event->button.x, y = event->button.y;
            for(int i = 0; i < button_count; ++i){
                if(((x - (buttons[i]->rect.x)) <= buttons[i]->rect.w) && ((x - buttons[i]->rect.x) >= 0) && ((y - buttons[i]->rect.y) <= buttons[i]->rect.h) && ((y - buttons[i]->rect.y) >= 0)){
                    buttons[i]->b_color.first = 1;
                }
            }
			break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
        //смена цвета кнопки + функционал
			button_count = buttons.size();
            x = event->button.x;
            y = event->button.y;
            for(int i = 0; i < button_count; ++i){
                if(((x - (buttons[i]->rect.x)) <= buttons[i]->rect.w) && ((x - buttons[i]->rect.x) >= 0) && ((y - buttons[i]->rect.y) <= buttons[i]->rect.h) && ((y - buttons[i]->rect.y) >= 0)){
                    buttons[i]->b_color.first = 0;
                }
            }
			break;
	}
	return SDL_APP_CONTINUE;
}


int a = 1;
SDL_AppResult SDL_AppIterate(void* appstate){
	uint64_t b = SDL_GetTicks();

    pages[0]->render();

	uint64_t c = SDL_GetTicks() - b;
	SDL_Delay(16-c);


	SDL_RenderPresent(renderer);
	return SDL_APP_CONTINUE; 
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    
    /* SDL will clean up the window/renderer for us. */
}