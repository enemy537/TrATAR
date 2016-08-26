/*
 * ObjetoMult.h
 *
 *  Created on: 28/01/2015
 *      Author: pedro
 */

#ifndef OBJETOMULT_H_
#define OBJETOMULT_H_
 #include <cstdio>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <aruco/aruco.h>
#include <SDL2/SDL.h>
#include "../lib/objparser.h"
#include "../lib/renderer.h"

namespace obj{
	enum FORMAS{CUBO,CONE,ESFERA,NONE};
	enum TEXTURA{TEX,NOTEX};
}

class ObjetoMult{
private:
	aruco::BoardConfiguration config;
	obj::FORMAS forma;
	obj::TEXTURA textura;
	aruco::Board board;
	float tamanhoMarcador;
	vector<float> cores;
	char* caminho;
	OBJMesh* carregaOBJ;
	Renderer* renderizador;
	GLuint* imagemTextura;
public:
	ObjetoMult();
	ObjetoMult(float,obj::FORMAS);
	ObjetoMult(float,char*);
	ObjetoMult(float,char*,obj::TEXTURA);
	void carregarTextura();
	void desenharObjeto();
	void desenharPosicao(float,float,float,bool);
	void setCores(const vector<float>& cores);
	void setConfig(aruco::BoardConfiguration&);
	aruco::BoardConfiguration getConfig() const;
	void setBoard(const aruco::Board& marcador);
};



#endif /* OBJETOMULT_H_ */
