#pragma once

#include <iostream>
#include <SDL3/SDL.h>
#include "page.h"

void page::render(){
    SDL_SetRenderDrawColor(rend, backgraund.r, backgraund.g, backgraund.b, backgraund.a);
    SDL_RenderClear(rend);
    for(int i = 0; i < rects.size(); ++i){
        SDL_SetRenderDrawColor(rend, rects[i].second.r, rects[i].second.g, rects[i].second.b, rects[i].second.a);
        SDL_RenderRect(rend, &rects[i].first);
    }

    for(int i = 0; i < images.size(); ++i){
        SDL_RenderTexture(rend, images[i].second, NULL, &images[i].first);
    }

    for(int i = 0; i < buttons.size(); ++i){
        buttons[i]->render();
    }

    for(int i = 0; i < blocks.size(); ++i){
        blocks[i]->render();
    }

    for(int i = 0; i < textblocks.size(); ++i){
        textblocks[i]->render();
    }
    if(func != nullptr){
        func();
    }
}