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

	vectorConfig.push_back(config_1);vectorConfig.push_back(config_2);

	DetectorMult detectorMult(0.5,0,caminho,0.2,vectorConfig);
	detectorMult.inicializar(parametros);

	ObjetoMult cb1(.5,"img/1C.bmp", obj::TEX);ObjetoMult cb2(.5,"img/2C.bmp", obj::TEX);

	vector<ObjetoMult> objetos;
	objetos.push_back(cb1);objetos.push_back(cb2);

	ObjetoMult endGame(0.10,"PARABENS2.bmp",obj::TEX);

	ShowGLMult showGL(detectorMult,objetos,endGame,"applause.wav");
	showGL.setEspacamento(.01); showGL.setDeslocamento(.1);
	showGL.executar(argc,argv);
}
