/*
 * Tela.hpp
 *
 *  Created on: 11/06/2016
 *      Author: Guilherme
 */

#ifndef TELA_HPP_
#define TELA_HPP_

#include"Fontes.hpp"

//Telas
class Tela {
public:
	bool apareceu, apareceu2, changeFase;
	int contador, contadorMedio;
	//Atualiza a tela
	void atualizTudo(Imagens *imagem) {
		imagem->attTela();
		changeFase = false;
	}

	//Eventos Menu
	void eventosMenu(Imagens *imagem, SDL_Event *evento) {
		if (imagem->currentTela == imagem->menu) {
			if (evento->type == SDL_MOUSEMOTION) {
				if (evento->button.x >= 355 && evento->button.x < 649
						&& evento->button.y >= 240 && evento->button.y < 394) {
					apareceu = true;
				} else {
					apareceu = false;
				}
			}
			if (evento->type == SDL_MOUSEBUTTONUP) {
				if (evento->button.x >= 355 && evento->button.x < 649
						&& evento->button.y >= 240 && evento->button.y < 394) {
					imagem->currentTela = imagem->newGame;
					apareceu = false;
				} else {
					imagem->currentTela = imagem->credits;
				}
			}
		}
	}

	//Atualiza Menu
	void atualizaMenu(Imagens *imagem, SDL_Event *evento, Sounds *som) {
		imagem->oBotaoPlay.h = 150;
		imagem->oBotaoPlay.w = 300;
		imagem->oBotaoPlay.x = 350;
		imagem->oBotaoPlay.y = 245;
		if (imagem->currentTela == imagem->menu) {
			som->playMenu();
			if (apareceu == true) {
				SDL_RenderCopy(imagem->render, imagem->botaoPlay, NULL,
						&imagem->oBotaoPlay);
			}
		}
	}

	//Eventos Creditos
	void eventosCreditos(Imagens *imagem, SDL_Event *evento) {
		if (imagem->currentTela == imagem->credits) {
			if (evento->type == SDL_MOUSEMOTION) {
				if (evento->button.x >= 349 && evento->button.x < 648
						&& evento->button.y >= 461 && evento->button.y < 610) {
					apareceu2 = true;
				} else {
					apareceu2 = false;
				}
			}
			if (evento->type == SDL_MOUSEBUTTONUP) {
				if (evento->button.x >= 349 && evento->button.x < 648
						&& evento->button.y >= 461 && evento->button.y < 610) {
					imagem->currentTela = imagem->menu;
					apareceu2 = false;
				} else {
					imagem->currentTela = imagem->credits;
				}
			}
		}
	}

	//Atualiza Creditos
	void atulizaCreditos(Imagens *imagem, SDL_Event *evento) {
		imagem->oBotaoVoltar.h = 150;
		imagem->oBotaoVoltar.w = 300;
		imagem->oBotaoVoltar.x = 349;
		imagem->oBotaoVoltar.y = 461;
		if (imagem->currentTela == imagem->credits) {
			if (apareceu2 == true) {
				SDL_RenderCopy(imagem->render, imagem->botaoVoltar, NULL,
						&imagem->oBotaoVoltar);
			}
		}
	}

	//Eventos NewGame
	void eventosSaveGame(Imagens *imagem, SDL_Event *evento, Jogador *jogador,
			Fontes *fonte, Nave *nave) {
		if (imagem->currentTela == imagem->newGame) {
			jogador->fimJogo = false;
			if (evento->type == SDL_MOUSEBUTTONUP) {
				if (evento->button.x >= 100 && evento->button.x < 399
						&& evento->button.y >= 51 && evento->button.y < 200) {
					//Avisando que mudou essas ações
					jogador->mudouFase = true;
					jogador->mudouScore = true;
					jogador->mudouVida = true;
					//Zerando tudo
					jogador->nFase = 1;
					jogador->nScore = 0;
					jogador->vidas = 3;
					nave->oNave.x = 500;
					nave->oNave.y = 325;

					contador = jogador->nFase;
					imagem->currentTela = imagem->inGame;
				}
				if (evento->button.x >= 600 && evento->button.x < 899
						&& evento->button.y >= 425 && evento->button.y < 574) {
					fonte->arqVida = fopen("Lifes.txt", "r");
					fscanf(fonte->arqVida, "%d", &jogador->vidas);
					fonte->arqScore = fopen("Scores.txt", "r");
					fscanf(fonte->arqScore, "%d", &jogador->nScore);
					fonte->arqFase = fopen("Fases.txt", "r");
					fscanf(fonte->arqFase, "%d", &jogador->nFase);
					jogador->mudouFase = true;
					jogador->mudouScore = true;
					jogador->mudouVida = true;
					fclose(fonte->arqFase);
					fclose(fonte->arqScore);
					fclose(fonte->arqVida);
					imagem->currentTela = imagem->inGame;
				}
			}
		}
	}

	//InGame
	void eventosJogo(Imagens *imagem, Nave *nave, SDL_Event *evento) {
		if (imagem->currentTela == imagem->inGame) {
			nave->moveNave(evento, imagem);
		}
	}

	//Atualiza tela InGame
	void atualizaJogo(Imagens *imagem, Nave *nave, Fontes *fonte,
			Jogador *jogador, list<AsteroideGrande> *astGrande,
			list<AsteroideMedio> *astMedio, Ufo *ufo, Sounds *som) {

		if (imagem->currentTela == imagem->inGame) {

			fonte->fontePrintJogo(imagem, jogador);
			list<AsteroideGrande>::iterator i;
			list<AsteroideMedio>::iterator i2;

			int h;
			if ((contador == 0) && (changeFase = true)) {
				jogador->mudouFase = true;
				jogador->nFase++;
				contador = jogador->nFase;
				for (i = astGrande->begin(); i != astGrande->end(); i++) {
					(*i).loadPedraGrande(imagem);
					(*i).defineAngulo();
					(*i).iniciaPedraGrande();
				}
				changeFase = false;
			}
			nave->acelera(&nave->oNave);
			nave->attNave(imagem->render);
			nave->atirar(&nave->oTiro, &nave->oNave, imagem);
			nave->attTiro(imagem);
			int j;

			//Atualiza as pedras grandes
			for (j = 0, i = astGrande->begin();
					i != astGrande->end(), j < contador; i++, j++) {
				(*i).movePedra(&((*i).oPedraGrande));
				if ((*i).invisivel == false) {
					(*i).atualizaPedra(imagem->render, jogador);
				}
			}

			//Verifica colisão com Asteroides Grandes
			for (j = 0, i = astGrande->begin();
					i != astGrande->end(), j < contador; i++, j++) {
				(*i).invisivel = imagem->confereColisao(&nave->oTiro,
						&((*i).oPedraGrande));
				if ((*i).invisivel == true) {
					nave->atirou = false;
					nave->oTiro.x = nave->oNave.x + (nave->oNave.w / 2);
					nave->oTiro.y = nave->oNave.y + (nave->oNave.h / 2);
					astGrande->remove(*i);
					contador--;
					contadorMedio += 2;
					jogador->nScore += 100;
					jogador->mudouScore = true;

					/*for (h = 0; h < 2; h++) {
					 AsteroideMedio valor2;
					 astMedio->push_back(valor2);
					 }*/

					//if(contador == 0){
					//changeFase=true;
					//}
				}
				nave->morto = imagem->confereColisao(&nave->oNave,
						&((*i).oPedraGrande));
			}
			int l;
			/*for (l = 0, i2 = astMedio->begin();i2 != astMedio->end(), l < contadorMedio; i2++, l++) {
			 (*i2).movePedraMedia(&((*i2).oPedraMedia));
			 if ((*i2).invisivel2 == false) {
			 (*i2).atualizaPedraMedia(imagem->render, jogador);
			 }
			 cout<<l<<endl;
			 }*/
			/*Essas partes comentadas representa quando um asteroide grande for acertado, irá aparecer dois medios
			 * porem está bugando o código
			 */

			if ((jogador->nFase % 2) == 0) {
				ufo->moveUfo(&ufo->oUfo);
				ufo->atualizaUfo(imagem->render);
			}else{
				ufo->defineAnguloUfo();
			}

			//Verifica o estado
			nave->verificaEstado(jogador);

			//Game over
			jogador->gameOver(imagem);
			if (jogador->vidas == 0) {
				jogador->nFase = 1;
			}

		}
	}

	//Destroi tudo
	void fechaTudo(Imagens *imagem, Nave *nave, Fontes *fonte, Jogador *jogador,
			Sounds *som) {
		SDL_DestroyWindow(imagem->window);
		imagem->window = NULL;
		SDL_DestroyTexture(imagem->inGame);
		SDL_DestroyTexture(imagem->currentTela);
		SDL_DestroyTexture(imagem->menu);
		SDL_DestroyTexture(imagem->credits);
		SDL_DestroyTexture(imagem->botaoPlay);
		SDL_DestroyTexture(imagem->botaoVoltar);
		SDL_DestroyWindow(imagem->window);
		SDL_DestroyRenderer(imagem->render);

		Mix_Quit();
		IMG_Quit();
		SDL_Quit();
	}

	//Eventos Game Over
	void eventosGameOver(Imagens *imagem, SDL_Event *evento, Jogador *jogador,
			Fontes *fonte) {
		if (imagem->currentTela == imagem->gameOver) {
			if (evento->type == SDL_MOUSEBUTTONUP) {
				if (evento->button.x >= 350 && evento->button.x < 649
						&& evento->button.y >= 450 && evento->button.y < 599) {
					//Zerando tudo
					jogador->nFase = 1;
					jogador->mudouScore = 0;
					jogador->vidas = 3;
					imagem->currentTela = imagem->menu;

					fonte->arqVida = fopen("Lifes.txt", "w");
					fprintf(fonte->arqVida, "3", &jogador->vidas);
					fonte->arqScore = fopen("Scores.txt", "w");
					fprintf(fonte->arqScore, "0", &jogador->nScore);
					fonte->arqFase = fopen("Fases.txt", "w");
					fprintf(fonte->arqFase, "1", &jogador->nFase);
					jogador->mudouFase = true;
					jogador->mudouScore = true;
					jogador->mudouVida = true;
					fclose(fonte->arqFase);
					fclose(fonte->arqScore);
					fclose(fonte->arqVida);
				}

			}
		}
	}

	//Atualiza Game Over
	void atualizaGameOver(Imagens *imagem, Fontes *fonte, Jogador *jogador) {
		if (imagem->currentTela == imagem->gameOver) {
			fonte->scoreFinal(imagem, jogador);
		}
	}

};

#endif /* TELA_HPP_ */
