/*
 * algorytmPam.h
 *
 *  Created on: 27 gru 2015
 *      Author: davidsiecinski
 */

#ifndef ALGORYTMPAM_H_
#define ALGORYTMPAM_H_

#include "algorytm.h"
class AlgorytmPam{
	int k; //liczba grup
	std::vector<punkt> medodoidy;
	public:
	AlgorytmPam(){ srand(time(NULL));}
	void pam();


};


#endif /* ALGORYTMPAM_H_ */
