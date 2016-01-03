/*
 * algorytmPam.h
 *
 *  Created on: 27 gru 2015
 *      Author: davidsiecinski
 */

#ifndef ALGORYTMPAM_H_
#define ALGORYTMPAM_H_

#include "algorytm.h"
class AlgorytmPam : public  Algorytm{
	int k_; //liczba grup
	int n_;
	std::vector<punkt> medodoidy_;
	public:
	AlgorytmPam(const std::vector<punkt> &dane,int k){dane_=dane; k_=k; n_=dane.size(); srand(time(NULL));}
	void pam();
	int wylosuj(std::vector<int> juz_wylosowane);


};


#endif /* ALGORYTMPAM_H_ */
