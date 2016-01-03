/*
 * algorytmPam.cpp
 *
 *  Created on: 27 gru 2015
 *      Author: davidsiecinski
 */

#include "algorytmPam.h"


// k losowych punktow staje sie medodaidami, reszta jest przypisana do najblizszych punktow
// losowo zamien zwykly punkt na medodid
// oblicz koszt zamiany
// jesli koszt jest mniejszy to zamien
// powtarzaj dopoki nie bedzie zmian
void AlgorytmPam::pam(){

	// losowanie k obiektow ze zbioru n obiektow
	std::vector<int> juz_wylosowane_k;
	for(int j=0;j<k_;j++){
		juz_wylosowane_k.push_back(wylosuj(juz_wylosowane_k));
		medodoidy_.push_back(dane_.at(juz_wylosowane_k.at(j)));
	}
	std::cout<<"metodoidy:"<<std::endl;
	for(int i=0;i<medodoidy_.size(); i++)
		std::cout<<"("<<(double)medodoidy_.at(i).first<<", "<<(double)medodoidy_.at(i).second<<")"<<std::endl;

}

int AlgorytmPam::wylosuj(std::vector<int> juz_wylosowane)
{
	bool nowa_liczba=true;
	int liczba;
	do {
		liczba=rand() % n_;
		for (int i=0; i< juz_wylosowane.size(); i++)
			if (juz_wylosowane.at(i)==liczba)
				nowa_liczba=false;

	}while(!nowa_liczba);
    return liczba;
}





