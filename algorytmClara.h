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
	int k_;
	int n_;
	std::vector<punkt> losowanieProbekDanych(std::vector<punkt> data, int ilosc);
	double tc(AlgorytmPam pam, std::vector<punkt> dane);
public:
	AlgorytmClara(const std::vector<punkt> &dane,int k){dane_=dane; k_=k; n_=dane.size();}
	std::vector<punkt> wyliczenieMedodoidow();
};


#endif /* ALGORYTMCLARA_H_ */
