/*
 * Sounds.hpp
 *
 *  Created on: 11/06/2016
 *      Author: Guilherme
 */

#ifndef SOUNDS_HPP_
#define SOUNDS_HPP_

#include"Asteroides.hpp"

//Sons
class Sounds {

public:
	Mix_Music *mainSong;
	Mix_Music *voandoSong;
	Mix_Music *tiroSong;
	int volume;

	Sounds() {
		volume = 1;
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 2048);
		mainSong = Mix_LoadMUS("Sons/ThemeSong.mp3");
		//voandoSong = Mix_LoadMUS("Sons/Voa.mp3");
		tiroSong = Mix_LoadMUS("Sons/Tiro.mp3");
	}

	//Som do menu
	void playMenu() {
		if (Mix_PlayingMusic() == 0) {
			Mix_PlayMusic(mainSong, 1);
		}

	}

	//Som quando voar
	void playVoando() {
		//Mix_PlayMusic(voandoSong,0);
	}

	//Toca som tiro
	void playTiro() {
		if (Mix_PlayingMusic() == 0) {
			Mix_PauseMusic();
			Mix_PlayMusic(tiroSong, 0);
		}
	}

};

#endif /* SOUNDS_HPP_ */
