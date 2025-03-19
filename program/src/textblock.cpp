#include <iostream>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "textblock.h"
#include <string>

void textblock::push_back(char symb){
    simb.push_back(symb);

    SDL_Surface* surf = TTF_RenderText_Solid(font, &symb, 1, text_color);
    str.push_back(std::make_pair(palka, SDL_CreateTextureFromSurface(rend, surf)));
    SDL_GetTextureSize(str.back().second, &str.back().first.w, nullptr);
    palka.x += str.back().first.w;
    SDL_DestroySurface(surf);
}

void textblock::pop_back(){
    simb.pop_back();
    palka.x -= str.back().first.w;
    str.pop_back();
}

void textblock::render(){
    SDL_SetRenderDrawColor(rend, rcolor.r, rcolor.g, rcolor.b, rcolor.a);
    SDL_RenderFillRect(rend, &rect);

    SDL_SetRenderDrawColor(rend, tcolor.r, tcolor.g, tcolor.b, tcolor.a);
    SDL_RenderFillRect(rend, &text_rect);

    for(int i = 0; i < str.size(); ++i){
        SDL_RenderTexture(rend, str[i].second, NULL, &str[i].first);
    }
    if(active){
        if(a < 25){
            SDL_SetRenderDrawColor(rend, pcolor.r, pcolor.g, pcolor.b, pcolor.a);
            SDL_RenderFillRect(rend, &palka);
            ++a;
        } else{
            ++a;
            if(a == 50)
                a = 0;
        }
    } else {
        SDL_SetRenderDrawColor(rend, pcolor.r, pcolor.g, pcolor.b, pcolor.a);
        SDL_RenderFillRect(rend, &palka);
    }

}