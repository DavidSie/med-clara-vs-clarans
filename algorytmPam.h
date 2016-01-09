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

	int wylosuj(std::vector<int> juz_wylosowane);
	std::vector<double> tc(std::vector<int> klasyfikacjaPunktow);
	double cij(punkt i,punkt j);
	double cjmp(punkt j,punkt m, punkt p);
	std::vector<int> klasyfikacja_punktow(std::vector<punkt> metodoidy,std::vector<punkt> dane_do_klasyfikacji);

	public:
	AlgorytmPam(){srand(time(NULL));}
	void setData(const std::vector<punkt> &dane,int k){dane_=dane; k_=k; n_=dane.size();}
	AlgorytmPam(const std::vector<punkt> &dane,int k){dane_=dane; k_=k; n_=dane.size(); srand(time(NULL));}
	std::vector<punkt>  pam();




};


#endif /* ALGORYTMPAM_H_ */
