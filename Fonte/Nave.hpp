/*
 * Nave.hpp
 *
 *  Created on: 11/06/2016
 *      Author: Guilherme
 */

#ifndef NAVE_HPP_
#define NAVE_HPP_

#include"Imagens.hpp"
#include"Sounds.hpp"
#include"Jogador.hpp"

//Nave
class Nave {
public:
	SDL_Texture *nave = NULL;
	SDL_Texture *naveVoa = NULL;
	SDL_Texture *currentNave = NULL;
	SDL_Texture *tiro = NULL;
	SDL_RendererFlip flip;
	SDL_Rect oNave;
	SDL_Rect oTiro;

	SDL_Event events;

	Sounds *som;

	//Nave
	float anguloNave;
	float anguloRadiano;
	float seno, cosseno;
	float velocidade, velocidadeMax, velocidadeMin;
	float vx, vy;
	float acel;
	float desacel;
	bool morto;

	//Tiro
	bool atirou;
	float velocidadeTiro;
	float vxTiro, vyTiro;
	float vxT, vyT;
	bool camisinha;
	float anguloTiro;

	int xFinal, yFinal, xInicial, yInicial;

	//Inicializa as variaveis
	void inicializaVar() {
		anguloNave = 270;
		velocidade = 2.0;
		acel = 0.5;
		desacel = 0.5;
		velocidadeMax = 10000.0;
		velocidadeMin = 2.0;
		oNave.x = 500;
		oNave.y = 325;
		oNave.h = 30;
		oNave.w = 36;
		morto = false;
		//Tiro
		oTiro.h = 5;
		oTiro.w = 5;
		oTiro.x = oNave.x + (oNave.w / 2);
		oTiro.y = oNave.y + (oNave.h / 2);
		velocidadeTiro = 6.0;
		anguloTiro = anguloNave;
		atirou = false;
	}

	//Carrega Imagens
	void loadNave(SDL_Renderer *render) {
		inicializaVar();
		nave = IMG_LoadTexture(render, "Imagens/Nave/Nave.png");
		naveVoa = IMG_LoadTexture(render, "Imagens/Nave/NaveVoa.png");
		tiro = IMG_LoadTexture(render, "Imagens/Nave/Tiro.png");
		currentNave = nave;

	}

	//Atualiza a Nave
	void attNave(SDL_Renderer *render) {
		oNave.h = 30;
		oNave.w = 36;
		SDL_RenderCopyEx(render, currentNave, NULL, &oNave, anguloNave, NULL,
				flip);
	}

	//Movimenta nave
	void moveNave(SDL_Event *evento, Imagens *imagem) {
		if (evento->type == SDL_KEYDOWN) {
			switch (evento->key.keysym.sym) {
			//Seta direita
			case SDLK_RIGHT:
				anguloNave = anguloNave + 10;
				anguloTiro = anguloTiro + 10;
				oTiro.x = oNave.x + (oNave.w / 2);
				oTiro.y = oNave.y + (oNave.h / 2);
				if ((anguloNave > 360) && (anguloTiro < 0)) {
					anguloNave = anguloNave - 360;
					anguloTiro = anguloTiro - 360;

				}
				atirou = false;
				break;

				//Seta esquerda
			case SDLK_LEFT:
				anguloNave = anguloNave - 10;
				anguloTiro = anguloTiro - 10;
				oTiro.x = oNave.x + (oNave.w / 2);
				oTiro.y = oNave.y + (oNave.h / 2);
				if ((anguloNave < 0) && (anguloTiro < 0)) {
					anguloNave = anguloNave + 360;
					anguloTiro = anguloTiro - 360;

				}
				atirou = false;
				break;

				//Seta cima
			case SDLK_UP:
				som->playVoando();
				currentNave = naveVoa;
				//acelera(&oNave);
				velocidade+=5;
				oTiro.x = oNave.x + (oNave.w / 2);
				oTiro.y = oNave.y + (oNave.h / 2);
				atirou = false;
				break;

				//Esc
			case SDLK_ESCAPE:
				imagem->currentTela = imagem->menu;
				oNave.x = 500;
				oNave.y = 325;
				oTiro.x = oNave.x + (oNave.w / 2);
				oTiro.y = oNave.y + (oNave.h / 2);
				anguloNave = 270;

				atirou = false;
				break;

			case SDLK_SPACE:
				//som->playTiro();
				//atirou = false;
				atirou = true;

				break;
			}
		}
		if (evento->type == SDL_KEYUP) {
			switch (evento->key.keysym.sym) {
			case SDLK_UP:
				currentNave = nave;
				velocidade-=5;
				break;
			case SDLK_SPACE:
				oTiro.x = oNave.x + (oNave.w / 2);
				oTiro.y = oNave.y + (oNave.h / 2);
				atirou = false;
				break;
			}
		}
	}

	//Atira
	void atirar(SDL_Rect *oTiro, SDL_Rect *oNave, Imagens *imagem) {
		if ((atirou == true) && (morto == false)) {
			anguloRadiano = grausRadiano(anguloTiro);
			cosseno = floatToInt(cos(anguloRadiano));
			seno = floatToInt(sin(anguloRadiano));

			vxT = round(velocidadeTiro * cosseno);
			vyT = round(velocidadeTiro * seno);

			verificaParede(oTiro);
			oTiro->x = vxT + oTiro->x;
			oTiro->y = vyT + oTiro->y;
			SDL_Delay(2);

		} else {
			anguloTiro = anguloNave;
		}
	}

	//Atualiza o tiro
	void attTiro(Imagens *imagem) {
		oTiro.h = 5;
		oTiro.w = 5;
		if (atirou == true) {
			SDL_RenderCopyEx(imagem->render, tiro, NULL, &oTiro, anguloNave,
			NULL, flip);
		}
	}

	//Acelera nave
	void acelera(SDL_Rect *oImagem) {
		if (velocidade < velocidadeMax) {
			velocidade = velocidade + acel;
		}
		SDL_Delay(2);
		anguloRadiano = grausRadiano(anguloNave);
		cosseno = floatToInt(cos(anguloRadiano));
		seno = floatToInt(sin(anguloRadiano));

		vx = round(velocidade * cosseno);
		vy = round(velocidade * seno);
		//cout << "Vel Down: " << velocidade << endl;
		verificaParede(&oNave);
		oImagem->x = vx + oImagem->x;
		oImagem->y = vy + oImagem->y;

	}

	//Graus para Radianos
	float grausRadiano(float anguloGraus) {

		float anguloRadiano;
		anguloRadiano = 3.14 * (anguloGraus / 180);
		return anguloRadiano;
	}

	//Converte float para int
	float floatToInt(float numero) {
		int aux;
		aux = numero * 100;
		numero = ((aux * 1.0) / 100);
		return numero;
	}

	//Verifica se não está na parede
	void verificaParede(SDL_Rect *oRect) {
		if (oRect->x > 1000) {
			oRect->x = 0;
		}
		if (oRect->x < 0) {
			oRect->x = 1000;
		}
		if (oRect->y > 650) {
			oRect->y = 0;
		}
		if (oRect->y < 0) {
			oRect->y = 650;
		}
	}

	//Verifica a situação da Nave
	bool verificaEstado(Jogador *jogador) {
		if (morto == true) {
			jogador->mudouVida = true;
			jogador->vidas--;
			oNave.x = rand() % 1000;
			oNave.y = rand() % 650;
			oTiro.x = oNave.x + ((oNave.x) / 2) - 5;
			oTiro.y = oNave.y + ((oNave.y) / 2) - 5;
			SDL_Delay(500);
		}
	}

	//Destrutor
	~Nave() {

		SDL_DestroyTexture(nave);
		SDL_DestroyTexture(currentNave);
		SDL_DestroyTexture(naveVoa);
	}
};

#endif /* NAVE_HPP_ */
