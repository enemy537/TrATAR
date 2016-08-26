#include "KalmanMult.h"

KalmanMult::KalmanMult(){
	this->util = new Util();
    float m[3][2] = {{1, 1}, {0, 1}};
	kalman = KalmanFilter(2, 1, 0);
	measurement = Mat(1, 1, CV_32FC1);
	state  = Mat(2, 1, CV_32FC1);
	measurement_noise = Mat(1, 1, CV_32FC1);
	process_noise = Mat(2, 1, CV_32FC1);

	kalman.transitionMatrix = Mat(2, 2, CV_32FC1, m);

	setIdentity(kalman.measurementMatrix,Scalar(1));
	setIdentity(kalman.processNoiseCov,  Scalar(1e-5));
	setIdentity(kalman.measurementNoiseCov, Scalar(1e-1));
	setIdentity(kalman.errorCovPost, Scalar(1));

	randu(state, Scalar(0), Scalar(0.1));
	randu(kalman.statePost, Scalar(0), Scalar(0.1));
	randn(measurement_noise, Scalar(0),Scalar(0.1,0.1));
	randn(process_noise, Scalar(0),Scalar(0.1,0.1));
	randn(measurement_noise, Scalar(0),Scalar(0.1,0.1));
}
double* KalmanMult::prever(Board& board){
	double temp[16], * posicaoFinal;
	board.glGetModelViewMatrix(temp);
	posicaoFinal = util->getCenter(temp);

	state.at<float>(0) = posicaoFinal[0];
	state.at<float>(1) = posicaoFinal[1];
	state.at<float>(2) = posicaoFinal[2];

	kalman.predict();

	measurement = kalman.measurementMatrix* state+ measurement_noise;

	kalman.correct(measurement);

	process_noise = kalman.processNoiseCov.at<float>(0,0);

	state = kalman.transitionMatrix* state + process_noise;

	posicaoFinal[0] = state.at<float>(0);
	posicaoFinal[1] = state.at<float>(1);
	posicaoFinal[2] = state.at<float>(2);

	return posicaoFinal;
}
