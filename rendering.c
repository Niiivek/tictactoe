#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "game.h"
#include "rendering.h"

const SDL_Color GRID_COLOR={.r= 255, .g= 255, .b=255}; // blanc
const SDL_Color PLAYER_X_COLOR= {.r= 255, .g= 50, .b=50}; // rouge
const SDL_Color PLAYER_O_COLOR= {.r= 50, .g= 100, .b=255}; // bleu
const SDL_Color TIE_COLOR= {.r= 100, .g= 100, .b=100}; // gris


void render_grid(SDL_Renderer *renderer, const SDL_Color *color){ 
// trace les lignes et colonnes de ma grille
    SDL_SetRenderDrawColor(renderer,color->r,color->g,color->b,255); 

    for(int i=1;i<N;++i){ 
        SDL_RenderDrawLine(renderer,i* CELL_WIDTH, 0,i*CELL_WIDTH,SCREEN_HEIGHT);

        SDL_RenderDrawLine(renderer,0,i*CELL_HEIGHT, SCREEN_WIDTH,i*CELL_HEIGHT);
    }

}

void DrawDisc(SDL_Renderer *renderer,int x, int y,int r,const SDL_Color *color){
//dessine un cercle sur une case dont les coordonnées du centre sont x et y et le rayon r
	for(int i=x-r;i<=x+r;i++){
		for(int j=y-r;j<=y+r;j++){
			if((i-x)*(i-x) + (j-y)*(j-y)<(r*r)){		//on vérifie si le point appartient au disque à partir de son inéquation
				SDL_RenderDrawPoint(renderer,i,j);
			}
		}
	}
}

void render_x(SDL_Renderer *renderer,int row,int column,const SDL_Color *color){
// trace une croix
    const float half_box_side=fmin(CELL_HEIGHT,CELL_WIDTH)*0.25; // rayon
    const float center_x=CELL_WIDTH*0.5+column*CELL_WIDTH; // milieu en x
    const float center_y=CELL_HEIGHT*0.5+row*CELL_HEIGHT; // milieu en y

    SDL_SetRenderDrawColor(renderer,color->r,color->g,color->b,255);

    SDL_RenderDrawLine(renderer,center_x-half_box_side,center_y-half_box_side,center_x+half_box_side,center_y+half_box_side);
    SDL_RenderDrawLine(renderer,center_x-half_box_side,center_y+half_box_side,center_x+half_box_side,center_y-half_box_side);
    
}

void render_o(SDL_Renderer *renderer,int row,int column,const SDL_Color *color){
//trace un cercle
    const float half_box_side=fmin(CELL_HEIGHT,CELL_WIDTH)*0.25; // rayon
    const float center_x=CELL_WIDTH*0.5+column*CELL_WIDTH; // milieu en x
    const float center_y=CELL_HEIGHT*0.5+row*CELL_HEIGHT; // milieu en y

    SDL_SetRenderDrawColor(renderer,color->r,color->g,color->b,255);
    DrawDisc(renderer,center_x,center_y,half_box_side+10,color);

    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    DrawDisc(renderer,center_x,center_y,half_box_side+8,color);
    //SDL_RenderDrawLine(renderer,center_x-half_box_side,center_y-half_box_side,center_x+half_box_side,center_y+half_box_side);
    //SDL_RenderDrawLine(renderer,center_x-half_box_side,center_y+half_box_side,center_x+half_box_side,center_y-half_box_side);
    
}

void render_board(SDL_Renderer *renderer, const int *board, const SDL_Color *player_x_color, const SDL_Color *player_o_color){
//
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            switch(board[i*N+j]){
            case PLAYER_X:
                render_x(renderer,i,j,player_x_color);
                break;

            case PLAYER_O:
                render_o(renderer,i,j,player_o_color);
                break;

            default:{}
            }
        }
    }
}

void render_running_state(SDL_Renderer *renderer, const game_t *game){
    render_grid(renderer,&GRID_COLOR);
    render_board(renderer, game->board,&PLAYER_X_COLOR,&PLAYER_O_COLOR);

}

void render_game_over_state(SDL_Renderer *renderer, const game_t *game, const SDL_Color *color){
// 
    render_grid(renderer,color);
    render_board(renderer, game->board,color,color);
}

void render_game(SDL_Renderer *renderer, const game_t *game){
    switch(game->state){
    case RUNNING_STATE:
        render_running_state(renderer,game);
        break;
    
    case PLAYER_X_WON_STATE:
        render_game_over_state(renderer,game,&PLAYER_X_COLOR);
        break;
    
    case PLAYER_O_WON_STATE:
        render_game_over_state(renderer,game,&PLAYER_O_COLOR);
        break;
    
    case TIE_STATE:
        render_game_over_state(renderer,game,&TIE_COLOR);
        break;
    
    default:{}
    }
}

