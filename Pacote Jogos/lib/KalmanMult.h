/*
 * Kalman.h
 *
 *  Created on: 03/12/2014
 *      Author: pedro
 */

#ifndef KALMANMULT_H_
#define KALMANMULT_H_

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/tracking.hpp>
#include <aruco/aruco.h>
#include <vector>
#include "Util.hpp"

using namespace cv;
using namespace aruco;

class KalmanMult{
private:
	KalmanFilter kalman;
	Mat_<float> measurement;
	Mat_<float> measurement_noise;
	Mat state;
	Mat process_noise;
	Util* util;
public:
	KalmanMult();
	double* prever(Board&);
};



#endif /* KALMANMULT_H_ */
