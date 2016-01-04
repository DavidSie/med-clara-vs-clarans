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
std::vector<punkt> AlgorytmPam::pam(){
	// losowanie k obiektow ze zbioru n obiektow
	std::vector<int> juz_wylosowane_k;
	for(int j=0;j<k_;j++){
		juz_wylosowane_k.push_back(wylosuj(juz_wylosowane_k));
		medodoidy_.push_back(dane_.at(juz_wylosowane_k.at(j)));
	}
	std::cout<<"metodoidy:"<<std::endl;
	for(int i=0;i<medodoidy_.size(); i++)
		std::cout<<"("<<(double)medodoidy_.at(i).first<<", "<<(double)medodoidy_.at(i).second<<")"<<std::endl;
	//	 Dla każ dej pary: (obiekt zwykły h, obiekt reprezentatywny i ) wyznacz całkowity koszt zamiany TCih
	std::vector<punkt> nowe_medodoidy =medodoidy_;
	std::vector<punkt> stare_metodoidy;
	bool kolejnaPentla=false;
	do{
		stare_metodoidy=nowe_medodoidy;
		// przydzial do klas
		std::vector<int> klasyfikacjaPunktow=klasyfikacja_punktow();

		// obliczenie TCih
		nowe_medodoidy=tc(klasyfikacjaPunktow);

		kolejnaPentla=false;
		for(int h=0;h<nowe_medodoidy.size();h++)
			if(nowe_medodoidy.at(h)!=stare_metodoidy.at(h)){
				kolejnaPentla=true;
				break;
			}

//		for(int s=0;s<stare_metodoidy.size();s++)
//					std::cout<<"stary medodoid nr "<<s<<"("<<stare_metodoidy.at(s).first<<", "<<stare_metodoidy.at(s).second<<")"<<std::endl;
//		for(int s=0;s<nowe_medodoidy.size();s++)
//					std::cout<<"nowy medodoid nr "<<s<<"("<<nowe_medodoidy.at(s).first<<", "<<nowe_medodoidy.at(s).second<<")"<<std::endl;

	}while(kolejnaPentla);
	return nowe_medodoidy;
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

std::vector<punkt> AlgorytmPam::tc(std::vector<int> klasyfikacja_punktow){

//	policz sume cijh dla wszystkich elementow dla nowego medodoidu
//	jesli medodoid i punkt sa w roznych klasach to cijh=0
	std::vector<punkt> nowe_medodoidy (k_);
	for (int i=0;i<medodoidy_.size();i++){
	// stare medodidy

		for (int k=0; k<dane_.size(); k++){
			double tc_min=INT_MAX;
			double tc=0.0;
			// kandydaci na nowe medodoidy

			// kandydat musi nalezec do danej klasy
			if (klasyfikacja_punktow.at(k)!=i)
				continue;
			for(int j=0; j<dane_.size();j++){
			// punkty od ktorych liczymy odleglosc
					tc+=cjih(dane_.at(j),medodoidy_.at(i),dane_.at(k));
			}
			if (tc<tc_min){
				tc_min=tc;
				nowe_medodoidy.at(i)=dane_.at(k);
				std::cout<<"nowy nr "<< i<<" metodoid: ("<<nowe_medodoidy.at(i).first<<", "<<nowe_medodoidy.at(i).second<<")"<<std::endl;
			}
		}
	}
	return nowe_medodoidy;
}

double AlgorytmPam::cij(punkt i,punkt j){
	double wynik=sqrt((i.first-j.first)*(i.first-j.first)+(i.second-j.second)*(i.second-j.second));
	return wynik;
}

double AlgorytmPam::cjih(punkt j,punkt i, punkt h){
	double wynik=cij(j,h)-cij(j,i);
	return wynik;
}

std::vector<int> AlgorytmPam::klasyfikacja_punktow(){
// klasyfikujemy punkt do najblizszego medodidu
	std::vector<int> klasyfikacja_punktow (dane_.size());
	for(int j=0; j<dane_.size();j++){
		double min_odleglosc=INT_MAX;
		for (int i=0;i<medodoidy_.size();i++){
			double odleglosc=cij(medodoidy_.at(i),dane_.at(j));
			if (odleglosc<min_odleglosc){
				min_odleglosc=odleglosc;
				klasyfikacja_punktow.at(j)=i;
			}

		}
//		std::cout<<"klasyfikacja punktu: ("<<dane_.at(j).first<<", "<<dane_.at(j).second<<") do klasy: "<<klasyfikacja_punktow.at(j)<<std::endl;
	}

	return klasyfikacja_punktow;
}



