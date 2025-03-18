#include "block.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

void block::render() {

    //выставляем цвет кнопки (обычный или нажата)
    if(b_color.first == 0)
        SDL_SetRenderDrawColor(rend, b_color.second.first.r, b_color.second.first.g, b_color.second.first.b, b_color.second.first.a);
    else
        SDL_SetRenderDrawColor(rend, b_color.second.second.r, b_color.second.second.g, b_color.second.second.b, b_color.second.second.a);

	SDL_RenderFillRect(rend, &rect);

    //кнопка с рамкой или обычная
	if(border != 0){
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 0xff); 
		SDL_RenderRect(rend, &rect);
	}

    SDL_RenderTexture(rend, textt.second, NULL, &textt.first);
    SDL_RenderTexture(rend, img.second, NULL, &img.first);

#if 0
	SDL_FRect br;
	SDL_GetTextureSize(but->text, &br.w, &br.h);
	br.y = but->rect.y + (but->rect.h - br.h)/2;
	br.x = but->rect.x + (but->rect.w - br.w)/2;
	SDL_RenderTexture(renderer, but->text, NULL, &br);
#endif
}

