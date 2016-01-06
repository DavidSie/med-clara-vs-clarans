/*
 * algorytmClara.h
 *
 *  Created on: 12 gru 2015
 *      Author: davidsiecinski
 */

#ifndef ALGORYTMCLARA_H_
#define ALGORYTMCLARA_H_

#include "algorytm.h"
#include "algorytmPam.h"

class AlgorytmClara : public  Algorytm{
	AlgorytmPam pam;
	int k_;
	int n_;
public:
	AlgorytmClara(const std::vector<punkt> &dane,int k){dane_=dane; k_=k; n_=dane.size(); pam=AlgorytmPam();}
	std::vector<punkt> wyliczenieMedodoidow();
};


#endif /* ALGORYTMCLARA_H_ */
