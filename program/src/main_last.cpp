#define SDL_MAIN_USE_CALLBACKS 1

#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include "button.h"
#include "block.h"
#include "page.h"
#include "file.h"

#if 0
#define err(S) do{\
    const char* err_string = #S;\
    cout << "Couldn't initialize" << err_string;\
    return SDL_APP_FAILURE;\
} while(0)
#endif

const char* passw = "pass/pass.txt";
int pa(int p){
    return p+1;
}
pass p(pa, passw);


SDL_Color block_color = {100, 0 ,0, 255};
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

int z = 0, z1 = 0;
int l = 0; //сюда писать следующую стр
void g(){
    if(z1 < 10)
        ++z1;
    else{
        if(page_number == 1)
            page_number = 2;
        else    
            page_number = 1;
        ++z;
        if(z == 8){
            page_number = l;
        z = 0;
        }
        z1 = 0;
    }
}

void h(){
    l = 0;
    page_number = 1;
}


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

    SDL_Color t_color = {255, 255 ,255, 255};
    SDL_Color p_color = {1, 100 ,255, 255};
    SDL_FRect bl = {0, 200, 400, 100};
    SDL_FRect bl1 = {20, 220, 360, 60};
    pages[0]->textblocks.push_back(new textblock(renderer, font, block_color, t_color, p_color, bl, bl1));
    pages[0]->textblocks[0]->func = h;


    pages.push_back(new page());
    pages[1]->rend = renderer;
    pages[1]->backgraund.a = 255; pages[1]->backgraund.g = 100; pages[1]->backgraund.b = 255; pages[1]->backgraund.r = 255;
    SDL_FRect gg = {200, 300, 100,100};
    pages[1]->images.push_back(std::make_pair(gg,IMG_LoadTexture(renderer, "icons/1.png")));
    pages.push_back(new page());
    pages[2]->rend = renderer;
    pages[2]->backgraund.a = 255; pages[2]->backgraund.g = 100; pages[2]->backgraund.b = 255; pages[2]->backgraund.r = 255;
    pages[2]->images.push_back(std::make_pair(gg,IMG_LoadTexture(renderer, "icons/2.png")));
    pages[2]->func = g;
    pages[1]->func = g;

	return SDL_APP_CONTINUE;
}



SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event){
    size_t button_count; 
    int x, y;
	switch (event->type){
		case SDL_EVENT_QUIT:
			return SDL_APP_SUCCESS;

		case SDL_EVENT_KEY_UP:
            if(pages[page_number]->textblocks[page_number]->active == 1){
                if(event->key.scancode == SDL_SCANCODE_BACKSPACE){
                    if(!pages[page_number]->textblocks[0]->str.empty())
                        pages[page_number]->textblocks[0]->pop_back();
                    break;
                }
                if(event->key.scancode == 40){
                    if(p.check(pages[page_number]->textblocks[0]->simb))
                        pages[page_number]->textblocks[0]->func();
                    break;
                }
                pages[page_number]->textblocks[0]->push_back(event->key.scancode+19);
            }
            break;


		case SDL_EVENT_MOUSE_BUTTON_DOWN:
        //смена цвета кнопки 
            button_count = pages[page_number]->buttons.size();
            x = event->button.x, y = event->button.y;
            for(int i = 0; i < button_count; ++i){
                if(((x - (pages[page_number]->buttons[i]->rect.x)) <= pages[page_number]->buttons[i]->rect.w) && ((x - pages[page_number]->buttons[i]->rect.x) >= 0) && ((y - pages[page_number]->buttons[i]->rect.y) <= pages[page_number]->buttons[i]->rect.h) && ((y - pages[page_number]->buttons[i]->rect.y) >= 0)){
                    pages[page_number]->buttons[i]->b_color.first = 1;
                }
            }

            button_count = pages[page_number]->blocks.size();
            for(int i = 0; i < button_count; ++i){
                if(((x - (pages[page_number]->blocks[i]->rect.x)) <= pages[page_number]->blocks[i]->rect.w) && ((x - pages[page_number]->blocks[i]->rect.x) >= 0) && ((y - pages[page_number]->blocks[i]->rect.y) <= pages[page_number]->blocks[i]->rect.h) && ((y - pages[page_number]->blocks[i]->rect.y) >= 0)){
                    pages[page_number]->blocks[i]->b_color.first = 1;
                }
            }
			break;

        case SDL_EVENT_MOUSE_BUTTON_UP:
        //смена цвета кнопки + функционал
            button_count = pages[page_number]->buttons.size();
            x = event->button.x;
            y = event->button.y;
            for(int i = 0; i < button_count; ++i){
                if(((x - (pages[page_number]->buttons[i]->rect.x)) <= pages[page_number]->buttons[i]->rect.w) && ((x - pages[page_number]->buttons[i]->rect.x) >= 0) && ((y - pages[page_number]->buttons[i]->rect.y) <= pages[page_number]->buttons[i]->rect.h) && ((y - pages[page_number]->buttons[i]->rect.y) >= 0)){
                    pages[page_number]->buttons[i]->b_color.first = 0;
                }
            }
            button_count = pages[page_number]->blocks.size();
            for(int i = 0; i < button_count; ++i){
                if(((x - (pages[page_number]->blocks[i]->rect.x)) <= pages[page_number]->blocks[i]->rect.w) && ((x - pages[page_number]->blocks[i]->rect.x) >= 0) && ((y - pages[page_number]->blocks[i]->rect.y) <= pages[page_number]->blocks[i]->rect.h) && ((y - pages[page_number]->blocks[i]->rect.y) >= 0)){
                    pages[page_number]->blocks[i]->b_color.first = 0;
                }
            }

            button_count = pages[page_number]->textblocks.size();
            for(int i = 0; i < button_count; ++i){
                if(((x - (pages[page_number]->textblocks[i]->rect.x)) <= pages[page_number]->textblocks[i]->rect.w) && ((x - pages[page_number]->textblocks[i]->rect.x) >= 0) && ((y - pages[page_number]->textblocks[i]->rect.y) <= pages[page_number]->textblocks[i]->rect.h) && ((y - pages[page_number]->textblocks[i]->rect.y) >= 0)){
                    pages[page_number]->textblocks[i]->active = 1;
                } else {
                    pages[page_number]->textblocks[i]->active = 0;
                }
            }
			break;
	}
	return SDL_APP_CONTINUE;
}


int a = 1;
SDL_AppResult SDL_AppIterate(void* appstate){
	uint64_t b = SDL_GetTicks();

    pages[page_number]->render();

	uint64_t c = SDL_GetTicks() - b;
	SDL_Delay(16-c);


	SDL_RenderPresent(renderer);
	return SDL_APP_CONTINUE; 
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    
    /* SDL will clean up the window/renderer for us. */
}