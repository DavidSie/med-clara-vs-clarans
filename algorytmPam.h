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
	std::vector<int> medoids_idx_;

	int wylosuj(std::vector<int> juz_wylosowane);
	double cij(punkt i,punkt j);
	std::vector<int> klasyfikacja_punktow(std::vector<punkt> metodoidy,std::vector<punkt> dane_do_klasyfikacji);
	int index(std::vector<int> data,int value);

	public:
	std::pair< double, std::map<int, std::vector<int> >  > totalCost(std::vector<punkt> dane_,std::vector<int> medoids_idx);
	AlgorytmPam(){srand(time(NULL));}
	void setData(const std::vector<punkt> &dane,int k){dane_=dane; k_=k; n_=dane.size();}
	AlgorytmPam(const std::vector<punkt> &dane,int k){dane_=dane; k_=k; n_=dane.size(); srand(time(NULL));}
	std::vector<punkt>  pam();

	std::vector<punkt> getMedoids(){return medodoidy_;}
	std::vector<int> getMedoidsIdx(){return medoids_idx_;}





};


#endif /* ALGORYTMPAM_H_ */
