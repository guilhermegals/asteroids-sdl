/*
 * Imagens.hpp
 *
 *  Created on: 11/06/2016
 *      Author: Guilherme
 */

#ifndef IMAGENS_HPP_
#define IMAGENS_HPP_
#include<list>
#include<iostream>
#include<stdio.h>
#include<cstdlib>
#include<stdlib.h>
#include<sstream>
#include<string>
#include<ctime>
#include<cmath>
#include<ctype.h>
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_mixer.h>
#include <SDL2\SDL_ttf.h>
#include<SDL2\SDL_thread.h>
using namespace std;
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 650;

class Colisao {
public:
	bool confereColisao(SDL_Rect objetoA, SDL_Rect objetoB) { //Essa lógica foi usada a partir da Aula de colisoes
															  //do lazyfool.net
		//Tamanhos dos objetos
		int direitaA, esquerdaA;
		int direitaB, esquerdaB;
		int topA, downA;
		int topB, downB;

		//Objeto A
		esquerdaA = objetoA.x;
		direitaA = objetoA.x + objetoA.w;
		topA = objetoA.y;
		downA = objetoA.y + objetoA.h;

		//Objeto B
		esquerdaB = objetoB.x;
		direitaB = objetoB.x + objetoB.w;
		topB = objetoB.y;
		downB = objetoB.y + objetoB.h;

		if (downA <= topB) {
			return false;
		}

		if (topA >= downB) {
			return false;
		}

		if (direitaA <= esquerdaB) {
			return false;
		}

		if (esquerdaA >= direitaB) {
			return false;
		}

		return true;
	}
};

//Imagens
class Imagens {
public:
	SDL_Window *window = NULL;

	SDL_Texture *inGame = NULL;
	SDL_Texture *currentTela = NULL;
	SDL_Texture *menu = NULL;
	SDL_Texture *credits = NULL;
	SDL_Texture *botaoPlay = NULL;
	SDL_Texture *botaoVoltar = NULL;
	SDL_Texture *newGame = NULL;
	SDL_Texture *gameOver = NULL;

	SDL_Renderer *render = NULL;

	SDL_Rect oBotaoPlay;
	SDL_Rect oBotaoVoltar;

	//Inicializa Imagens
	Imagens() {
		createTela();
		loadTela();
	}

	//Cria tela
	void createTela() {
		window = SDL_CreateWindow("ASTEROIDS", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	}

	//Carrega imagens
	void loadTela() {
		botaoPlay = IMG_LoadTexture(render, "Imagens/Telas/BotaoPlay.jpg");
		inGame = IMG_LoadTexture(render, "Imagens/Telas/InGame.jpg");
		menu = IMG_LoadTexture(render, "Imagens/Telas/Menu.jpg");
		botaoVoltar = IMG_LoadTexture(render, "Imagens/Telas/BotaoVoltar.jpg");
		credits = IMG_LoadTexture(render, "Imagens/Telas/Creditos.jpg");
		newGame = IMG_LoadTexture(render, "Imagens/Telas/LoadGame.jpg");
		gameOver = IMG_LoadTexture(render, "Imagens/Telas/GameOver.jpg");
		currentTela = menu;
	}

	//Fecha Jogo
	bool quitGame(SDL_Event *evento) {
		if (evento->type == SDL_QUIT) {
			return false;
		} else {
			return true;
		}
	}

	//Atualiza tela
	void attTela() {
		SDL_RenderClear(render);
		SDL_RenderCopy(render, currentTela, NULL, NULL);
	}

	//Destroi tudo
	void liberaImagem() {

		SDL_DestroyTexture(inGame);

		SDL_DestroyTexture(menu);
		SDL_DestroyTexture(credits);
		SDL_DestroyTexture(botaoPlay);
		SDL_DestroyTexture(botaoVoltar);
	}

	bool confereColisao(SDL_Rect *objetoA, SDL_Rect *objetoB) { //Essa lógica foi usada a partir da Aula de colisoes
															  //do lazyfool.net
		//Tamanhos dos objetos
		int direitaA, esquerdaA;
		int direitaB, esquerdaB;
		int topA, downA;
		int topB, downB;

		//Objeto A
		esquerdaA = objetoA->x;
		direitaA = objetoA->x + objetoA->w;
		topA = objetoA->y;
		downA = objetoA->y + objetoA->h;

		//Objeto B
		esquerdaB = objetoB->x;
		direitaB = objetoB->x + objetoB->w;
		topB = objetoB->y;
		downB = objetoB->y + objetoB->h;

		if (downA <= topB) {
			return false;
		}

		if (topA >= downB) {
			return false;
		}

		if (direitaA <= esquerdaB) {
			return false;
		}

		if (esquerdaA >= direitaB) {
			return false;
		}
		//cout<<"colide\n";
		return true;
	}

	//Destrutor
	~Imagens() {
		SDL_DestroyTexture(currentTela);
		currentTela = NULL;
		SDL_DestroyWindow(window);
		window = NULL;
		SDL_DestroyRenderer(render);
	}

};

#endif /* IMAGENS_HPP_ */
