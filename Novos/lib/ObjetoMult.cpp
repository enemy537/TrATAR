/*
 * ObjetoMult.cpp
 *
 *  Created on: 28/01/2015
 *      Author: pedro
 */

#include "ObjetoMult.h"

// Private methods


void initTexture(GLuint* textura, char * caminho){
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	SDL_Surface* surface = SDL_LoadBMP(caminho);

	glGenTextures(1,textura);

	glBindTexture(GL_TEXTURE_2D,*textura);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,surface->w, surface->h,0,GL_BGR,GL_UNSIGNED_BYTE,surface->pixels);
	cout << caminho << endl;
	SDL_FreeSurface(surface);
}
void initTextureAlpha(GLuint* textura, char * caminho){
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	SDL_Surface* surface = SDL_LoadBMP(caminho);

	glGenTextures(1,textura);

	glBindTexture(GL_TEXTURE_2D,*textura);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,surface->w, surface->h,0,GL_BGRA,GL_UNSIGNED_BYTE,surface->pixels);
	SDL_FreeSurface(surface);
}

ObjetoMult::ObjetoMult(){}
ObjetoMult::ObjetoMult(float tamanhoMarcador, obj::FORMAS forma){
	this->tamanhoMarcador = tamanhoMarcador;
	this->carregaOBJ = NULL;
	this->renderizador = NULL;
	this->caminho = NULL;
	this->forma = forma;
	this->textura = obj::NOTEX;
}
ObjetoMult::ObjetoMult(float tamanhoMarcador,char caminho[]) {
	this->tamanhoMarcador = tamanhoMarcador;
	this->caminho = caminho;
	this->forma = obj::NONE;
	this->textura = obj::NOTEX;
	this->carregaOBJ = OBJParser().load(caminho);
	this->renderizador = new Renderer();
}
ObjetoMult::ObjetoMult(float tamanhoMarcador,char caminho[], obj::TEXTURA textura) {
	this->tamanhoMarcador = tamanhoMarcador;
	this->caminho = caminho;
	this->textura = textura;
	this->forma = obj::NONE;
	this->imagemTextura = new GLuint();
}

void ObjetoMult::desenharObjeto() {
	if(cores.size() == 3 )
		glColor3f(cores.at(0),cores.at(1),cores.at(2));
	double modelview_matrix[16];
	board.glGetModelViewMatrix(modelview_matrix);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixd(modelview_matrix);
	glTranslatef(0, 0, tamanhoMarcador/2);
	glPushMatrix();
	if(this->forma != obj::NONE)
		switch(this->forma){
		case obj::CUBO:
			glutSolidCube( tamanhoMarcador*7 );
			break;
		case obj::CONE:
			glTranslatef(0,.5,0);
			glRotated(90,1,0,0);
			glutSolidCone(tamanhoMarcador*3,tamanhoMarcador*7,50,50);
			break;
		case obj::ESFERA:
			glutSolidSphere(tamanhoMarcador*4,50,50);
			break;
	}else if(this->textura != obj::NOTEX){
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_NEAREST);
		glTranslatef(0,0,-1);
		glRotated(-90,0,0,1);
		glRotated(180,0,1,0);
		glScalef(tamanhoMarcador*1.85,tamanhoMarcador*1.85,1);
		glPushMatrix();
		glColor3f(1,1,1);
		glBindTexture(GL_TEXTURE_2D,*this->imagemTextura);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,  1.0f, 1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, 1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, 1.0f);
		glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_NEAREST);
	}else
		this->renderizador->render(this->carregaOBJ);
	glPopMatrix();
}
void ObjetoMult::desenharPosicao(float x,float y, float z,bool modo_exemplo){
	glLoadIdentity();
	if(this->cores.size() == 3 )
			glColor3f(this->cores.at(0),this->cores.at(1),this->cores.at(2));
	glTranslatef(x,y,z);
	if(this->forma != obj::NONE)
		switch(this->forma){
		case obj::CUBO:
			if(modo_exemplo){
				glRotated(195,0,1,0);
				glRotated(10,1,0,0);
				glScaled(1.6,1.6,1.6);
			}
			glutSolidCube( tamanhoMarcador );
			break;
		case obj::CONE:
			if(modo_exemplo){
				glTranslatef(.05,-.15,0);
				glRotated(270,1,0,0);
				glScaled(1.8,1.8,1.8);
			}
			glutSolidCone(tamanhoMarcador/2,tamanhoMarcador,20,20);
			break;
		case obj::ESFERA:
			if(modo_exemplo){
				glTranslatef(.05,0,0);
				glRotated(195,0,1,0);
				glScaled(1.8,1.8,1.8);
			}
			glutSolidSphere(tamanhoMarcador/2,20,20);
			break;
	}else if(this->textura != obj::NOTEX){
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_NEAREST);
		glRotated(-90,0,0,1);
		if(modo_exemplo)
			glScalef(.2,.2,1);
		glPushMatrix();
		glColor3f(1,1,1);
		glBindTexture(GL_TEXTURE_2D,*this->imagemTextura);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,  1.0f, 1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, 1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, 1.0f);
		glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_NEAREST);
	}else{
		glTranslatef(.35,0,0);
		glScaled(.2,.2,.8);
		this->renderizador->render(this->carregaOBJ);
	}
}
void ObjetoMult::carregarTextura(){
	initTexture(this->imagemTextura,this->caminho);
}
void ObjetoMult::carregarTexturaAlpha(){
	initTextureAlpha(this->imagemTextura,this->caminho);
}
void ObjetoMult::setCores(const vector<float>& cores) {
	this->cores = cores;
}
aruco::BoardConfiguration ObjetoMult::getConfig() const {
	return this->config;
}
void ObjetoMult::setBoard(const aruco::Board& board) {
	this->board = board;
}
void ObjetoMult::setConfig(aruco::BoardConfiguration&  config){
	this->config = config;
}
bool ObjetoMult::isTextura(){
	return !this->textura == obj::NOTEX;
}
