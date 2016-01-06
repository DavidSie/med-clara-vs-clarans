/*
 * algorytmClara.cpp
 *
 *  Created on: 12 gru 2015
 *      Author: davidsiecinski
 */

#include "algorytmClara.h"



std::vector<punkt> AlgorytmClara::wyliczenieMedodoidow(){
	std::vector<punkt> wynik;

	for(int i=0;i<5;i++){
	//		losujemy 40+2k danych ze zbioru
		pam.setData(dane_,k_);
		pam.pam();
	// liczymy dla wszystkich elementow average dissimilarity
	// jesli jest mniejsze to wynik jest nowym najlepszym wynikiem
	}

	return wynik;
}
