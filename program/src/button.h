#pragma once

#include <iostream>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

struct button{
	SDL_FRect rect; //размеры и позиция кнопки
    std::pair<char, std::pair<SDL_Color, SDL_Color> > b_color; //основной цвет и цвет во время нажатия
	char border; //наличие обводки 
    std::pair <SDL_FRect, SDL_Texture *> textt;
    SDL_Renderer *rend;
    void (*func)();
    

    button(float x, float y, float w, float h, float r0, float g0, float b0, float a0, float r1, float g1, float b1, float a1, char border, SDL_Texture *text, SDL_Renderer* rend):
    border(border), 
    rend(rend)
    {
        textt.second = text;
        SDL_GetTextureSize(text, &textt.first.w, &textt.first.h);
        textt.first.y = y + (h - textt.first.h)/2;
        textt.first.x = x + (w - textt.first.w)/2;
        rect.h = h; rect.w = w; rect.x = x; rect.y = y;

        b_color.first = 0;
        b_color.second.first.a = a0; b_color.second.first.r = r0; b_color.second.first.g = g0; b_color.second.first.b = b0;
        b_color.second.second.a = a1; b_color.second.second.r = r1; b_color.second.second.g = g1; b_color.second.second.b = b1;
    }

    ~button(){
        SDL_DestroyTexture(textt.second);
    }

    void render();

};