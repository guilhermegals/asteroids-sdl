/*
 * Fontes.hpp
 *
 *  Created on: 11/06/2016
 *      Author: Guilherme
 */

#ifndef FONTES_HPP_
#define FONTES_HPP_
#include"Asteroides.hpp"

//Fonts
class Fontes {
public:
	TTF_Font *fontVidas;
	TTF_Font *fontScore;
	SDL_Color textColor;

	SDL_Surface *printNVidas;
	SDL_Surface *printNScore;
	SDL_Surface *printFases;

	SDL_Texture *textoTela;
	SDL_Texture *textoFases;
	SDL_Texture *textoScores;

	FILE *arqVida;
	FILE *arqScore;
	FILE *arqFase;

	SDL_Rect oVidas;
	SDL_Rect oScore;
	SDL_Rect oFases;
	char nVidas[3], nScores[10], nFases[10];

	SDL_Rect oScoreFinal;

	//Inicializa as fontes
	void inicializFontes(Imagens *imagem, Jogador *jogador) {
		textColor = {255, 255, 255, 1};
		fontScore = TTF_OpenFont("Fontes/Pata.ttf", 40);
		fontVidas = TTF_OpenFont("Fontes/Alien.ttf", 25);
		//Vidas
		oVidas.x = 50;
		oVidas.y = 32;
		arqVida=fopen("Lifes.txt","w");
		printNVidas = TTF_RenderText_Solid(fontVidas, "aaa", textColor);
		textoTela = SDL_CreateTextureFromSurface(imagem->render, printNVidas);
		SDL_QueryTexture(textoTela, NULL, NULL, &oVidas.w, &oVidas.h);
		//Fase
		oFases.x = 900;
		oFases.y = 32;
		printFases = TTF_RenderText_Solid(fontScore,"1", textColor);
		textoFases = SDL_CreateTextureFromSurface(imagem->render, printFases);
		SDL_QueryTexture(textoFases, NULL, NULL, &oFases.w, &oFases.h);
		//Score
		oScore.x = 375;
		oScore.y = 32;
		printNScore = TTF_RenderText_Solid(fontScore ,"0" ,textColor);
		textoScores = SDL_CreateTextureFromSurface(imagem->render, printNScore);
		SDL_QueryTexture(textoScores ,NULL ,NULL , &oScore.w, &oScore.h);

	}

	//Printa os textos no jogo
	void fontePrintJogo(Imagens *imagem, Jogador *jogador) {
		//Número de vidas
		if(jogador->mudouVida == true) {
			if(jogador->vidas == 3) {
				arqVida = fopen("Lifes.txt","w");
				printNVidas = TTF_RenderText_Solid(fontVidas, "aaa", textColor);
				textoTela = SDL_CreateTextureFromSurface(imagem->render, printNVidas);
				SDL_QueryTexture(textoTela, NULL, NULL, &oVidas.w, &oVidas.h);
				fprintf(arqVida,"%d",jogador->vidas);
				jogador->mudouVida = false;
				fclose(arqVida);
			}
			if(jogador->vidas == 2) {
				arqVida = fopen("Lifes.txt","w");
				printNVidas = TTF_RenderText_Solid(fontVidas, "aax", textColor);
				textoTela = SDL_CreateTextureFromSurface(imagem->render, printNVidas);
				SDL_QueryTexture(textoTela, NULL, NULL, &oVidas.w, &oVidas.h);
				fprintf(arqVida,"%d",jogador->vidas);
				jogador->mudouVida = false;
				fclose(arqVida);
			}
			if(jogador->vidas == 1) {
				arqVida = fopen("Lifes.txt","w");
				printNVidas = TTF_RenderText_Solid(fontVidas, "axx", textColor);
				textoTela = SDL_CreateTextureFromSurface(imagem->render, printNVidas);
				SDL_QueryTexture(textoTela, NULL, NULL, &oVidas.w, &oVidas.h);
				fprintf(arqVida,"%d",jogador->vidas);
				jogador->mudouVida = false;
				fclose(arqVida);
			}
		}
		//Mudou Score
		if(jogador->mudouScore == true) {
			arqScore = fopen("Scores.txt","w");
			intToString(jogador->nScore,nScores);
			printNScore = TTF_RenderText_Solid(fontScore ,nScores,textColor);
			textoScores = SDL_CreateTextureFromSurface(imagem->render, printNScore);
			SDL_QueryTexture(textoScores ,NULL ,NULL , &oScore.w, &oScore.h);
			fprintf(arqScore,"%d",jogador->nScore);
			fclose(arqScore);
			jogador->mudouScore = false;
		}
		//Mudou fase
		if(jogador->mudouFase == true) {
			arqFase = fopen("Fases.txt","w");
			intToString(jogador->nFase,nFases);
			printFases = TTF_RenderText_Solid(fontScore ,nFases,textColor);
			textoFases = SDL_CreateTextureFromSurface(imagem->render, printFases);
			SDL_QueryTexture(textoFases, NULL, NULL, &oFases.w, &oFases.h);
			fprintf(arqFase,"%d",jogador->nFase);
			fclose(arqFase);
			jogador->mudouFase = false;
		}

		SDL_RenderCopy(imagem->render, textoTela, NULL, &oVidas);
		SDL_RenderCopy(imagem->render, textoFases, NULL, &oFases);
		SDL_RenderCopy(imagem->render, textoScores, NULL, &oScore);

	}

	//Printa o score final
	void scoreFinal(Imagens *imagem, Jogador *jogador){
		oScoreFinal.x = 385;
		oScoreFinal.y = 300;
		if(jogador->fimJogo == true){
			intToString(jogador->nScore,nScores);
			printNScore = TTF_RenderText_Solid(fontScore ,nScores,textColor);
			textoScores = SDL_CreateTextureFromSurface(imagem->render, printNScore);
			jogador->fimJogo = false;
		}
		SDL_QueryTexture(textoScores ,NULL ,NULL , &oScoreFinal.w, &oScoreFinal.h);
		SDL_RenderCopy(imagem->render, textoScores, NULL, &oScoreFinal);
	}


	//Converte Inteiro para Caractere
	void intToString(int i, char aux[]) {
		itoa(i,aux,10);
	}

};

#endif /* FONTES_HPP_ */
