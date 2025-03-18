#pragma once

#include <iostream>
#include <vector>
#include <SDL3/SDL.h>
#include "block.h"
#include "button.h"

struct page{
    std::vector<block*> blocks;
    std::vector<button*> buttons;
    std::vector<std::pair<SDL_FRect ,SDL_Texture*> > images;
    std::vector<std::pair<SDL_FRect ,SDL_Color> > rects;
    SDL_Color backgraund;
    SDL_Renderer* rend;
	
    page(){}

    ~page(){}

    void render();
     
};