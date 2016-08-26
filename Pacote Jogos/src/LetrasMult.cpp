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

	ObjetoMult A(.2,"obj/_A.obj");
	float tempCores1[] = {1,1,1};
	A.setCores(vector<float>(tempCores1,tempCores1+3));

	ObjetoMult B(.2,"obj/_B.obj");
	B.setCores(vector<float>(tempCores1,tempCores1+3));

	ObjetoMult C(.2,"obj/_C.obj");
	C.setCores(vector<float>(tempCores1,tempCores1+3));

	vector<ObjetoMult> objetos;
	objetos.push_back(A); objetos.push_back(B);
	objetos.push_back(C);

	//ObjetoMult endGame(0.10,"parabens.obj");
	ObjetoMult endGame(5,"PARABENS2.bmp",obj::TEX);

	ShowGLMult showGL(detectorMult,objetos,endGame,"applause.wav");
	showGL.setEspacamento(.01); showGL.setDeslocamento(.1);
	showGL.executar(argc,argv);
}

