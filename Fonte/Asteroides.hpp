/*
 * Asteroides.hpp
 *
 *  Created on: 11/06/2016
 *      Author: Guilherme
 */

#ifndef ASTEROIDES_HPP_
#define ASTEROIDES_HPP_

#include"Nave.hpp"

//Asteroids
class AsteroideGrande {
public:
	SDL_Texture *pedraGrande;
	float velocidadeGrande;
	float anguloPedraGrande;
	float vxP, vyP;
	float anguloRadiano;
	bool invisivel;

	SDL_Rect oPedraGrande;
	SDL_RendererFlip flip;

	AsteroideGrande() {
		defineAngulo();
		iniciaPedraGrande();
	}

	//Define o angulo
	void defineAngulo() {
		anguloPedraGrande = rand() % 360;
	}

	//Inicia as variaveis
	void iniciaPedraGrande() {
		velocidadeGrande = 1.0;
		defineAngulo();
		oPedraGrande.x = rand() % 1000;
		oPedraGrande.y = rand() % 650;
		oPedraGrande.h = 146;
		oPedraGrande.w = 132;
		invisivel = false;
	}

	//Load imagem
	void loadPedraGrande(Imagens *imagem) {
		pedraGrande = IMG_LoadTexture(imagem->render,
				"Imagens/Pedras/PedraGrande.png");
	}

	//Movimenta a pedra
	void movePedra(SDL_Rect *oRect) {
		if (invisivel == false) {
			float seno, cosseno;
			anguloRadiano = grausRadiano(anguloPedraGrande);
			cosseno = floatToInt(cos(anguloRadiano));
			seno = floatToInt(sin(anguloRadiano));

			vxP = round(velocidadeGrande * cosseno);
			vyP = round(velocidadeGrande * seno);

			verificaParede(oRect);
			oRect->x += vxP;
			oRect->y += vyP;
			SDL_Delay(1);
		}
	}

	//Converte graus para radiano
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

	//Atualiza a pedra
	void atualizaPedra(SDL_Renderer *render, Jogador *jogador) {
		if (invisivel == false) {
			oPedraGrande.h = 146;
			oPedraGrande.w = 132;
			SDL_RenderCopyEx(render, pedraGrande, NULL, &oPedraGrande,
					anguloPedraGrande, NULL, flip);
		} else {
			jogador->mudouScore = true;
			jogador->nScore = jogador->mudouScore + 100;
		}
	}

	bool operator==(const AsteroideGrande& a) {
		if ((a.oPedraGrande.x == this->oPedraGrande.x)
				&& (a.oPedraGrande.y == this->oPedraGrande.y)) {
			return true;
		} else {
			return false;
		}
	}
};

//Asteroide Medio
class AsteroideMedio: public AsteroideGrande {
public:
	SDL_Texture *pedraMedia;
	float velocidadeMedia;
	float anguloMedia;
	float vxM, vyM;
	float anguloMedioRadiano;
	bool invisivel2;
	SDL_Rect oPedraMedia;
	//SDL_RendererFlip flip2;

	//Construtor
	AsteroideMedio() {
		defineAnguloMedio();
		iniciaPedraMedia();
	}

	//Define o angulo da Pedra Media
	void defineAnguloMedio() {
		anguloMedia = rand() % 360;

	}

	//Inicia as variaveis de Pedra Media
	void iniciaPedraMedia() {
		velocidadeMedia = 2.0;
		defineAnguloMedio();
		oPedraMedia.x = oPedraGrande.x;
		oPedraMedia.y = oPedraGrande.y;
		oPedraMedia.h = 27;
		oPedraMedia.w = 25;
		invisivel2 = false;
	}

	//Load Pedra media
	void loadPedraMedia(Imagens *imagem) {
		pedraMedia = IMG_LoadTexture(imagem->render,
				"Imagens/Pedras/PedraMedia.png");
	}

	//Movimenta a pedra Media
	void movePedra(SDL_Rect *oRect) {
		if (invisivel2 == false) {
			float seno, cosseno;
			anguloMedioRadiano = grausRadiano(anguloMedia);
			cosseno = floatToInt(cos(anguloMedioRadiano));
			seno = floatToInt(sin(anguloMedioRadiano));

			vxM = round(velocidadeMedia * cosseno);
			vyM = round(velocidadeMedia * seno);

			verificaParede(oRect);
			oRect->x += vxP;
			oRect->y += vyP;
			SDL_Delay(1);
		}
	}

	bool operator==(const AsteroideMedio& b) {
		if ((b.oPedraGrande.x == this->oPedraGrande.x)
				&& (b.oPedraGrande.y == this->oPedraGrande.y)) {
			return true;
		} else {
			return false;
		}
	}

};

//Ufo
class Ufo: public AsteroideGrande {
public:
	float anguloUfo, anguloUfoRadiano;
	SDL_Texture *ufo;
	SDL_Rect oUfo;
	float vxF, vyF;
	bool someUfo;
	float velocidadeUfo;

	Ufo() {
		defineAnguloUfo();
		iniciaUfo();
	}

	//Define o angulo
	void defineAnguloUfo() {
		anguloUfo = rand() % 360;
	}

	//Inicia as variaveis
	void iniciaUfo() {
		velocidadeUfo = 1.0;
		defineAnguloUfo();
		oUfo.x = rand() % 1000;
		oUfo.y = rand() % 650;
		oUfo.h = 50;
		oUfo.w = 40;
		someUfo = false;
	}

	//Load imagem
	void loadUfo(Imagens *imagem) {
		ufo = IMG_LoadTexture(imagem->render, "Imagens/Nave/Ufo.png");
	}

	//Movimenta o Ufo
	void moveUfo(SDL_Rect *oRect) {
		if (invisivel == false) {
			float seno, cosseno;
			anguloUfoRadiano = grausRadiano(anguloUfo);
			cosseno = floatToInt(cos(anguloUfoRadiano));
			seno = floatToInt(sin(anguloUfoRadiano));

			vxF = round(velocidadeUfo * cosseno);
			vyF = round(velocidadeUfo * seno);

			verificaParede(oRect);
			oRect->x += vxF;
			oRect->y += vyF;
		}
	}

	//Atualiza o Ufo
	void atualizaUfo(SDL_Renderer *render) {
		if (someUfo == false) {
			oUfo.h = 50;
			oUfo.w = 40;
			SDL_RenderCopy(render, ufo, NULL, &oUfo);
		}
	}
};

#endif /* ASTEROIDES_HPP_ */
