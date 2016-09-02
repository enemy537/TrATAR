Treatment Assistant using Augmented Reality **TrATAR**


* Esse pacote de jogos foi desenvolvido na distribuição Ubuntu 14.10 64-bits
* Antes de prosseguir com a instalação certifique-se que as seguintes bibliotecas estão instaladas:
	OpenCV 2.4.9; ArUco 1.2.5; CMake 2.8; FreeGLUT 3; GLM (last); SDL2 + mixer;
* Para instalar as dependências:
	sudo apt-get -y install libglm-dev freeglut3-dev libsdl2-dev libsdl2-mixer-dev cmake libopencv-dev build-essential libgtk2.0-dev pkg-config python-dev python-numpy libdc1394-22 libdc1394-22-dev libjpeg-dev libpng12-dev libjasper-dev libavcodec-dev libavformat-dev libswscale-dev libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev libv4l-dev libtbb-dev libqt4-dev libfaac-dev libmp3lame-dev libopencore-amrnb-dev libopencore-amrwb-dev libtheora-dev libvorbis-dev libxvidcore-dev x264 v4l-utils unzip libxmu-dev libxi-dev

* Atentar à necessidade de atualizar as bibliotecas dinâmicas! sudo ldconfig

* Cada arquivo CMake da pasta deve ser compilado separadamente! Recorte os arquivos CMake para outra pasta e coloqueos um a um na pasta.
  Mude o nome do arquivo que será compilado na vez por CMakeLists.txt e então prossiga.
  Repita o processo para cada CMake da pasta.

* Compile o programa na pasta onde está o arquivo CMakeLists.txt pois os arquivos necessários para rodar o executável estão nessa pasta.

* Caso ocorra algum erro quanto a configuração de câmera, mude o valor do arquivo .cpp na pasta src (main) para 0. Ex.:
---------------------------------------------------------------------
    DetectorMult detectorMult(0.5,1,caminho,0.2,vectorConfig);
                                  ^
                                  ^
                             mude para 0
---------------------------------------------------------------------

* Todos os marcadores estão na pasta BOARDS.
