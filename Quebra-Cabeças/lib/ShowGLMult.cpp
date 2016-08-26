/*
 * ShowGLMult.cpp
 *
 *  Created on: 28/01/2015
 *      Author: pedro
 */

#include "ShowGLMult.h"

DetectorMult ShowGLMult::detector = DetectorMult();
Util ShowGLMult::util = Util();
int ShowGLMult::MODOS = 0;
vector<ObjetoMult> ShowGLMult::objetos = vector<ObjetoMult>();
vector<ObjetoMult> ShowGLMult::ultimasPosicoes = ShowGLMult::objetos;
KalmanMult ShowGLMult::kalman = KalmanMult();
ObjetoMult ShowGLMult::endGame = ObjetoMult();
ObjetoMult ShowGLMult::exemplo = ObjetoMult();
bool ShowGLMult::gameOver = false;
Mix_Chunk * ShowGLMult::musica = NULL;
float* ShowGLMult::deslocamentos = new float[2];
static clock_t start;
int controle = 0;

ShowGLMult::ShowGLMult(DetectorMult& detector,vector<ObjetoMult> objetos, ObjetoMult& endgame, string musica){
	if(objetos.size() == detector.getBoards().size()){
		ShowGLMult::detector = detector;
		ShowGLMult::objetos = objetos;
		for(unsigned int i=0;i<objetos.size();i++)
			ShowGLMult::objetos.at(i).setConfig(ShowGLMult::detector.getBoards().at(i));
		ShowGLMult::ultimasPosicoes = ShowGLMult::objetos;
		ShowGLMult::endGame = endgame;
		this->caminhoMusica = musica;
	}
}
void ShowGLMult::mudarOrdemElementos(){
	random_shuffle(ShowGLMult::objetos.begin(),ShowGLMult::objetos.end());
	ShowGLMult::gameOver = false;
	controle = 0;
}
void ShowGLMult::teclas(unsigned char tecla, int xmouse, int ymouse){
	switch(tecla){
	case 'r':
		ShowGLMult::gameOver = false;
		controle = 0;
		break;
	case 'm':
		mudarOrdemElementos();
		break;
	case 27:
		exit(0);
	default:
		break;
	}
}
void ShowGLMult::ativarIluminacao(){
	float luzAmbiente[]={0.2,0.2,0.2,1.0};
	float luzDifusa[]={0.9,0.7,0.7,1.0};
	float luzEspecular[] = {1.0, 1.0, 1.0, 1.0};
	float posicaoLuz[]={50, 25.0, 50.0, 1.0};

	float especularidade[] = {1.0,1.0,1.0,1.0};
	int especMaterial = 60;

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}
void ShowGLMult::desativarIluminacao(){
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
}
void ShowGLMult::setEspacamento(float x){
	this->deslocamentos[1] = x;
}
void ShowGLMult::setDeslocamento(float x){
	this->deslocamentos[0] = x;
}
void ShowGLMult::setExemplo(ObjetoMult exemplo){
	ShowGLMult::exemplo = exemplo;
}
bool ShowGLMult::isOrdenado(){
	vector<Board>marcadores = ShowGLMult::detector.detectar();
	if(marcadores.size() == ShowGLMult::objetos.size()){
		map<double,BoardConfiguration> dic;
		for(unsigned int i=0;i<marcadores.size();i++){
			double temp[16];
			marcadores[i].glGetModelViewMatrix(temp);
			dic[ShowGLMult::util.getCenter(temp)[0]] = marcadores[i].conf;
		}
		int contador = 0;
		for(map<double,BoardConfiguration>::iterator i=dic.begin();i!=dic.end();i++){
			if(!ShowGLMult::util.isBoardEqual(ShowGLMult::objetos[contador].getConfig(),i->second))
				return false;
			contador++;
		}
		return true;
	}else
		return false;
}
bool ShowGLMult::jigsawPuzzle(){
	vector<Board>marcadores = ShowGLMult::detector.detectar();
	if(marcadores.size() == ShowGLMult::objetos.size()){
		map<pair<double,double>,BoardConfiguration> dic;
		for(unsigned int i=0;i<marcadores.size();i++){
			double temp[16];
			marcadores[i].glGetModelViewMatrix(temp);
			pair<double,double> chave;
			chave.first = ShowGLMult::util.getCenter(temp)[0];
			chave.second = ShowGLMult::util.getCenter(temp)[1];
			dic[chave]= marcadores[i].conf;
		}
		vector<pair<double,double> > lista;
		map<pair<double,double>,BoardConfiguration>::iterator i = dic.begin();
		for(unsigned int j=0;j<ShowGLMult::objetos.size();j++){
			for(;i!=dic.end();i++){
				if(util.isBoardEqual(i->second,objetos[j].getConfig()))
					lista.push_back(i->first);
			}
			i = dic.begin();
		}
		unsigned int contador = 0;
		for(unsigned int x=0;x<(lista.size()/2)-1;x++){
			if(lista[x].first > lista[x+1].first &&
			   lista[x+(dic.size()/2)].first > lista[x+(dic.size()/2)+1].first)
				contador ++;
			if(lista[x].second < lista[x+dic.size()/2].second)
				contador ++;
		}
		cout << contador << endl;
		return contador == dic.size() - 2;
	}else
		return false;
}
void ShowGLMult::desenharExemplo(){
	if(ShowGLMult::exemplo.isTextura()){
		ShowGLMult::exemplo.desenharPosicao(.6,.65,0,true);
	}else{
		float posicao = 0;
		for(int i=ShowGLMult::objetos.size()-1;i>=0;i--){
			ativarIluminacao();
			ShowGLMult::objetos[i].desenharPosicao(-posicao+deslocamentos[0],0.8,.5,true);
			desativarIluminacao();
			posicao += ShowGLMult::detector.getTamanhoMarcador()*.7+deslocamentos[1];

		}
	}
}
void ShowGLMult::desenharObjetos(){
	vector<Board>boards = ShowGLMult::detector.detectar();
	for(unsigned int x=0;x<boards.size();x++){
		for(unsigned int y=0;y<ShowGLMult::objetos.size();y++){
			if(util.isBoardEqual(boards[x].conf,ShowGLMult::objetos[y].getConfig())){
				ShowGLMult::objetos[y].setBoard(boards[x]);
//				ativarIluminacao();
				ShowGLMult::objetos[y].desenharObjeto();
//				desativarIluminacao();
			}
		}
	}
}
void ShowGLMult::desenharUltimaPosicao(){
	for(unsigned int x=0;x<ShowGLMult::ultimasPosicoes.size();x++){
		ativarIluminacao();
		ShowGLMult::ultimasPosicoes[x].desenharObjeto();
		desativarIluminacao();
	}
	vector<Board> detectados = ShowGLMult::detector.detectar();
	for(unsigned int x=0;x<detectados.size();x++){
		for(unsigned int y=0;y<ShowGLMult::ultimasPosicoes.size();y++){
			if(util.isBoardEqual(detectados[x].conf, ShowGLMult::ultimasPosicoes[y].getConfig()))
				ShowGLMult::ultimasPosicoes[y].setBoard(detectados[x]);
		}
	}
}
void ShowGLMult::desenharKalman(){
	vector<Board>marcadores = ShowGLMult::detector.detectar();
	vector<ObjetoMult>objetos = ShowGLMult::objetos;
	for(unsigned int x=0;x<marcadores.size();x++){
		for(unsigned int y=0;y<objetos.size();y++){
			if(util.isBoardEqual(marcadores[x].conf,objetos[y].getConfig())){
				double* temp = ShowGLMult::kalman.prever(marcadores[x]);
				ativarIluminacao();
				objetos[y].desenharPosicao(temp[0],temp[1],temp[2],false);
				desativarIluminacao();
			}
		}
	}
}
void ShowGLMult::desenharMultTecnicas(){
	for(unsigned int x=0;x<ShowGLMult::ultimasPosicoes.size();x++){
		ativarIluminacao();
		ShowGLMult::ultimasPosicoes[x].desenharObjeto();
		desativarIluminacao();
	}
	vector<Board> detectados = ShowGLMult::detector.detectar();
	for(unsigned int x=0;x<detectados.size();x++){
		for(unsigned int y=0;y<ShowGLMult::ultimasPosicoes.size();y++){
//			if(detectados[x].conf == ShowGLMult::ultimasPosicoes[y].getConfig())
//				ShowGLMult::ultimasPosicoes[y].setBoard(
//						ShowGLMult::kalman.prever(detectados[x])
//				);
		}
	}
}
void * inicializarThread(void *){
	Mix_PlayChannel(-1,ShowGLMult::musica,0);
	SDL_Delay(1000);
	return NULL;
}
void ShowGLMult::chamadaThread(){
	inicializarThread(NULL);
}
void ShowGLMult::desenharTela(){
	if (detector.getImagemRedimensionada().rows==0)
	    return;
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, detector.getTamanhoJanela().width, 0, detector.getTamanhoJanela().height, -1.0, 1.0);
    glViewport(0, 0, detector.getTamanhoJanela().width , detector.getTamanhoJanela().height);
    glPixelZoom( 1, -1);
    glRasterPos3f( 0, detector.getTamanhoJanela().height  - 0.5, -1.0 );
    glDrawPixels ( detector.getTamanhoJanela().width , detector.getTamanhoJanela().height , GL_RGB ,
    		GL_UNSIGNED_BYTE , detector.getImagemRedimensionada().ptr(0) );
    glLoadIdentity();

    bool ordenado;
    if(ShowGLMult::objetos[0].isTextura())
    	ordenado = jigsawPuzzle();
    else
    	ordenado = isOrdenado();
    if(ordenado){
		ShowGLMult::gameOver = true;
		controle++;
    }
	if(gameOver){
		if(controle == 1){
			cout << controle << endl;
			chamadaThread();start = clock();
		}
		if(int(clock() - start)/1000000 > 3){
			ShowGLMult::endGame.desenharPosicao(0,0,0,false);
		}
	}

    glMatrixMode(GL_PROJECTION);
    double proj_matrix[16];
    detector.getParametrosCamera().glGetProjectionMatrix(
    		detector.getImagemEntrada().size(),detector.getTamanhoJanela(),proj_matrix,0.05,10
	);
    glLoadIdentity();
    glLoadMatrixd(proj_matrix);

    if(ShowGLMult::MODOS ==  0)
    	desenharObjetos();
    else if(ShowGLMult::MODOS == 1)
    	desenharUltimaPosicao();
    else if(ShowGLMult::MODOS == 2)
    	desenharKalman();
    else if(ShowGLMult::MODOS == 3)
    	desenharMultTecnicas();

    glutSwapBuffers();
}

void ShowGLMult::teclasEspeciais(int key, int x, int y){
	switch(key) {
		case GLUT_KEY_F1 :
			ShowGLMult::MODOS = 0; break;
		case GLUT_KEY_F2 :
			ShowGLMult::MODOS = 1; break;
		case GLUT_KEY_F3 :
			ShowGLMult::MODOS = 2; break;
		case GLUT_KEY_F4 :
			ShowGLMult::MODOS = 3; break;
		}
}
void ShowGLMult::emEspera(){
	detector.recapturar();
	glutPostRedisplay();
}
void ShowGLMult::redimensionar(GLsizei largura, GLsizei altura){
		detector.setTamanhoJanela(Size(largura,altura));
	    if (largura*3%4!=0) {
	        largura+=largura*3%4;
	        redimensionar(largura,detector.getTamanhoJanela().height);
	    }
	    else {
	        if (detector.getImagem_Copia().rows!=0)
	        detector.redimensionar();
	    }
}
void ShowGLMult::executar(int & argc, char** argv){
	glutInit(&argc, argv);
	SDL_Init(SDL_INIT_EVERYTHING);
	Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096);
	//Audio de fundo
	Mix_Music* fundo = Mix_LoadMUS("under_the_sea.mp3");
	Mix_PlayMusic(fundo,-1);
	//
	ShowGLMult::musica = Mix_LoadWAV(this->caminhoMusica.c_str());
	glutInitWindowPosition( 0, 0);
	Mat imagemEntrada = detector.getImagemEntrada();
	glutInitWindowSize(1024,768);
	glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE );
	glutCreateWindow( "Letrinhas" );
	for(unsigned int i=0; i<ShowGLMult::objetos.size(); i++){
		if(ShowGLMult::objetos[i].isTextura())
			ShowGLMult::objetos[i].carregarTextura();
	}

	ShowGLMult::endGame.carregarTexturaAlpha();

	glutDisplayFunc( desenharTela );
	glutIdleFunc( emEspera );
	glutReshapeFunc( redimensionar );
	glutSpecialFunc( teclasEspeciais );
	glutKeyboardFunc( teclas );
	glClearColor( 0.0, 0.0, 0.0, 1.0 );
	glClearDepth( 1.0 );
	detector.setTamanhoJanela(imagemEntrada.size());
	Size tamanhoJanela = detector.getTamanhoJanela();
	redimensionar(tamanhoJanela.width,tamanhoJanela.height);
	glutMainLoop();
}


