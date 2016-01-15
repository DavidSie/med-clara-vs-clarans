/*
 * algorytmClara.cpp
 *
 *  Created on: 12 gru 2015
 *      Author: davidsiecinski
 */

#include "algorytmClara.h"



std::vector<punkt> AlgorytmClara::wyliczenieMedodoidow(){
	std::vector<punkt> wynik;
	std::vector<wektorPunktow> wyniki;
	std::vector<double> tc_;
	for(int i=0;i<5;i++){
	//	losujemy 40+2k danych ze zbioru
		std::cout<<"[INFO][CLARA] iteracja "<<i<<std::endl;
		std::vector<punkt> daneLosowe=losowanieProbekDanych(dane_,40+2*k_);
		AlgorytmPam pam=AlgorytmPam(daneLosowe,k_);
		wyniki.push_back(pam.pam());

		//	 liczymy dla wszystkich elementow average dissimilarity
		tc_.push_back(tc(pam,dane_));

	}

	// znajdywanie wyniku z najmniejszym tc
	double tc_min=DBL_MAX;
	for (int i=0;i<wyniki.size();i++){
		if(tc_.at(i)<tc_min){
			tc_min=tc_.at(i);
			wynik=wyniki.at(i);
		}
	}
	std::cout<<"[INFO][CLARA] najlepszy wynik dla całego zbioru : "<<tc_min<<" dla punktow "<<std::endl;
	for (int i=0; i<wynik.size(); i++)
		wypiszPunkt( wynik.at(i));
	return wynik;
}


// losujemy ze zbioru {1,2,3,4,5}
// wybieramy 2. Nowy zbior {1,3,4,5}
// losujemy ze zbioru {1,3,4,5}

std::vector<punkt> AlgorytmClara::losowanieProbekDanych(std::vector<punkt> data, int ilosc){
	std::vector<punkt> sprobkowaneDane;
	int nr;

	for(int i=0;i<ilosc;i++){
		nr=rand() % data.size();
		sprobkowaneDane.push_back(data.at(nr));
		data.erase (data.begin()+nr);
	}
	return sprobkowaneDane;
}
double AlgorytmClara::tc(AlgorytmPam pam, std::vector<punkt> dane){
	return pam.totalCost(dane, pam.getMedoidsIdx()).first;
}
