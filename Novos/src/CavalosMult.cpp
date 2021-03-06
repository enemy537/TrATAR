//============================================================================
// Name        : CubosCoresMult.cpp
// Author      : Pedro
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <aruco/aruco.h>
#include "../lib/DetectorMult.h"
#include "../lib/ObjetoMult.h"
#include "../lib/ShowGLMult.h"
using namespace std;
using namespace aruco;

int main(int argc,char **argv) {
	string caminho = "intrinsics.yml";
	CameraParameters* parametros = new CameraParameters();
	parametros->readFromXMLFile(caminho);

	vector<BoardConfiguration> vectorConfig;
	BoardConfiguration config_1("board_2x3_1.yml");
	BoardConfiguration config_2("board_2x3_2.yml");
	BoardConfiguration config_3("board_2x3_3.yml");

	vectorConfig.push_back(config_1); vectorConfig.push_back(config_2);
	vectorConfig.push_back(config_3);

	DetectorMult detectorMult(0.5,0,caminho,0.2,vectorConfig);
	detectorMult.inicializar(parametros);

	ObjetoMult p1(.5,"img/c1.bmp", obj::TEX);
	ObjetoMult p2(.5,"img/c2.bmp", obj::TEX);
	ObjetoMult p3(.5,"img/c3.bmp", obj::TEX);


	vector<ObjetoMult> objetos;
	objetos.push_back(p1);
	objetos.push_back(p2);
	objetos.push_back(p3);
	//	ObjetoMult endGame(0.10,"parabens.obj");
	ObjetoMult endGame(0.10,"PARABENS2.bmp",obj::TEX);

	ShowGLMult showGL(detectorMult,objetos,endGame,"applause.wav");
	showGL.setEspacamento(.1); showGL.setDeslocamento(1);
	showGL.executar(argc,argv);
}
