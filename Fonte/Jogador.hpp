/*
 * Jogador.hpp
 *
 *  Created on: 11/06/2016
 *      Author: Guilherme
 */

#ifndef JOGADOR_HPP_
#define JOGADOR_HPP_

#include"Asteroides.hpp"

//Jogador
class Jogador {
public:
	int vidas;
	int nFase, nScore;
	bool mudouVida, mudouScore, mudouFase;
	int nGrandes,nMedios,nPequeno;
	bool fimJogo;

	//Inicializa Jogador
	Jogador() {
		vidas = 3;
		nFase = 1;
		nScore = 0;
		mudouVida = false;
		mudouFase = false;
		mudouScore = false;
		fimJogo = false;
	}

	void gameOver(Imagens *imagem){
		if(vidas==0){
			fimJogo = true;
			imagem->currentTela = imagem->gameOver;
		}
	}
};


#endif /* JOGADOR_HPP_ */
