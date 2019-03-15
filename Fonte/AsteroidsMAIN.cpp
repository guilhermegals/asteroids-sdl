//============================================================================
// Name        : Asteroids.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include"Tela.hpp"
#include<list>

//Main
int main(int argc, char *argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	Imagens imagem;
	Sounds som;
	Nave nave;
	Jogador jogador;
	Fontes fonte;
	Tela tela;
	Ufo ufo;
	SDL_Event evento;
	srand(time(NULL));

	fonte.inicializFontes(&imagem, &jogador);
	nave.loadNave(imagem.render);
	ufo.loadUfo(&imagem);

	bool rodando = true;
	//Listas
	list<AsteroideGrande> asteroideGrande;
	list<AsteroideGrande>::iterator i;

	list<AsteroideMedio> asteroideMedio;
	list<AsteroideMedio>::iterator i2;
	//

	//Iniciando a lista Asteroide Grande
	for (int j = 0; j < 100; j++) {
		AsteroideGrande valor;
		asteroideGrande.push_back(valor);
	}

	//Setando os valores da classe Pedra Grande
	for (i = asteroideGrande.begin(); i != asteroideGrande.end(); i++) {
		(*i).loadPedraGrande(&imagem);
		(*i).defineAngulo();
		(*i).iniciaPedraGrande();
	}

	//Iniciando a lista Asteroide Medio
	/*for (int k = 0; k < 200; k++) {
		AsteroideMedio valor2;
		asteroideMedio.push_back(valor2);
	}

	//Setando os valores da classe Pedra Media
	for (i2 = asteroideMedio.begin(); i2 != asteroideMedio.end(); i2++) {
		(*i2).loadPedraMedia(&imagem);
		(*i2).defineAnguloMedio();
		(*i2).iniciaPedraMedia();
	}*/

	/*Essa parte comentada representa a criação das listas dos asteroides medios*/


	tela.contador = jogador.nFase;
	tela.contadorMedio = 0;
	while (rodando) {

		while (SDL_PollEvent(&evento) != 0) {
			//Exit
			rodando = imagem.quitGame(&evento);

			//Menu
			tela.eventosMenu(&imagem, &evento);

			//Creditos
			tela.eventosCreditos(&imagem, &evento);

			//LoadSave
			tela.eventosSaveGame(&imagem, &evento, &jogador, &fonte, &nave);

			//InGame
			tela.eventosJogo(&imagem, &nave, &evento);

			//Game over
			tela.eventosGameOver(&imagem, &evento, &jogador, &fonte);

		}

		//Atualiza tudo
		tela.atualizTudo(&imagem);

		//Atualiza o Menu
		tela.atualizaMenu(&imagem, &evento, &som);

		//Atualiza o Creditos
		tela.atulizaCreditos(&imagem, &evento);

		//Atualiza o Jogo
		tela.atualizaJogo(&imagem, &nave, &fonte, &jogador, &asteroideGrande, &asteroideMedio,&ufo,&som);

		//Atualiza o Game Over
		tela.atualizaGameOver(&imagem,&fonte,&jogador);

		SDL_RenderPresent(imagem.render);
	}

	//Finaliza tudo
	tela.fechaTudo(&imagem, &nave, &fonte, &jogador, &som);
	return 0;
}

