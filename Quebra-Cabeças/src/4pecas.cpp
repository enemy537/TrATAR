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
	BoardConfiguration config_1("cubos/cubo1.yml");	BoardConfiguration config_2("cubos/cubo2.yml");
	BoardConfiguration config_3("cubos/cubo3.yml");	BoardConfiguration config_4("cubos/cubo4.yml");
	vectorConfig.push_back(config_1);vectorConfig.push_back(config_2);
	vectorConfig.push_back(config_3);vectorConfig.push_back(config_4);

	DetectorMult detectorMult(0.5,0,caminho,0.2,vectorConfig);
	detectorMult.inicializar(parametros);

	ObjetoMult cb1(.5,"img/1P.bmp", obj::TEX);ObjetoMult cb2(.5,"img/2P.bmp", obj::TEX);
	ObjetoMult cb3(.5,"img/3P.bmp", obj::TEX);ObjetoMult cb4(.5,"img/4P.bmp", obj::TEX);

	vector<ObjetoMult> objetos;
	objetos.push_back(cb1);objetos.push_back(cb2);
	objetos.push_back(cb3);objetos.push_back(cb4);
//	objetos.push_back(cb5);objetos.push_back(cb6);

	//ObjetoMult endGame(0.10,"parabens.obj");
	ObjetoMult endGame(0.10,"PARABENS2.bmp",obj::TEX);

	ShowGLMult showGL(detectorMult,objetos,endGame,"applause.wav");
	showGL.setEspacamento(.01); showGL.setDeslocamento(.1);
	//showGL.setExemplo(ObjetoMult(.5,"img/tartaruga.bmp",obj::TEX));
	showGL.executar(argc,argv);
}
