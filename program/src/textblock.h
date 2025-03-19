#pragma once

#include <iostream>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

struct textblock{
	SDL_FRect rect, text_rect, palka; //размеры, позиция всего блока и строки текста в нем, указатель текста
    SDL_Color rcolor, tcolor, pcolor, text_color;
	char border; //наличие обводки 
    
    TTF_Font* font;
    std::vector<std::pair<SDL_FRect, SDL_Texture*> > str; 
    std::vector<int> simb;
    SDL_Renderer *rend;
    char active;
    int a;

    void (*func)(void);
    


    void render();
    void pop_back();
    void push_back(char);
    
    textblock(SDL_Renderer *render, TTF_Font* font, SDL_Color rcolor, SDL_Color tcolor, SDL_Color pcolor, SDL_FRect rect, SDL_FRect text_rect):
    rend(render),
    font(font),
    rcolor(rcolor), 
    tcolor(tcolor), 
    pcolor(pcolor),
    rect(rect), 
    text_rect(text_rect)
    {
        func = nullptr;
        active = 0; a = 0;
        palka.h = text_rect.h*0.8; palka.y = text_rect.y + text_rect.h*0.1;
        palka.w = 2; palka.x = text_rect.x + text_rect.h*0.1;
        text_color.a = 255; text_color.r = 0; text_color.g = 0; text_color.b = 0;
    }

    ~textblock(){
        
    }

};