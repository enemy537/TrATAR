/*
 * ShowGLMult.h
 *
 *  Created on: 28/01/2015
 *      Author: pedro
 */

#ifndef SHOWGLMULT_H_
#define SHOWGLMULT_H_

#include <GL/gl.h>
#include <GL/glut.h>
#include <algorithm>
#include "DetectorMult.h"
#include "ObjetoMult.h"
#include "Util.hpp"
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "KalmanMult.h"
#include <time.h>

using namespace cv;

class ShowGLMult{
private:
	static float* deslocamentos;
	string caminhoMusica;
	static void mudarOrdemElementos();
	static void ativarIluminacao();
	static void desativarIluminacao();
	static void emEspera();
	static void desenharExemplo();
	static void desenharTela();
	static void desenharObjetos();
	static void desenharUltimaPosicao();
	static void desenharKalman();
	static void desenharMultTecnicas();
	static bool isOrdenado();
	static bool jigsawPuzzle();
	static void teclas(unsigned char,int,int);
	static void teclasEspeciais(int,int,int);
	static void redimensionar(GLsizei, GLsizei);
	static void chamadaThread();
public:
	static Mix_Chunk * musica;
	static Util util;
	static int MODOS;
	static bool gameOver;
	static DetectorMult detector;
	static vector<ObjetoMult> objetos;
	static vector<ObjetoMult> ultimasPosicoes;
	static KalmanMult kalman;
	static ObjetoMult endGame;
	static ObjetoMult exemplo;
	ShowGLMult(DetectorMult&,vector<ObjetoMult>,ObjetoMult&,string);
	void executar(int&,char**);
	void setExemplo(ObjetoMult);
	void setEspacamento(float);
	void setDeslocamento(float);
};

#endif /* SHOWGLMULT_H_ */
