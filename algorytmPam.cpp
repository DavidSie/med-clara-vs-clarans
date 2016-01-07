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
	for(int i=0;i<medodoidy_.size(); i++){
		std::cout<<"(";
		for (int k=0;k<medodoidy_.at(i).size();k++)
			std::cout<<(double)medodoidy_.at(i).at(k)<<", ";
		std::cout<<")"<<std::endl;
	}
	//	 Dla każdej pary: (obiekt zwykły h, obiekt reprezentatywny i ) wyznacz całkowity koszt zamiany TCih
	double tc_=10; // dodatnia liczba
	bool kolejnaPentla=false;
	do{
		// przydzial do klas
		std::vector<int> klasyfikacjaPunktow=klasyfikacja_punktow(medodoidy_,dane_);

		// obliczenie TCih i zwracanie nowych medodoidow
		tc_=tc(klasyfikacjaPunktow);

		kolejnaPentla=false;

		if(tc_<0){
			kolejnaPentla=true;
		}
		std::cout<<"tc= "<<tc_<<std::endl;

		for(int s=0;s<medodoidy_.size();s++){
					std::cout<<"nowy medodoid nr "<<s<<" (";
					for(int k=0;k<medodoidy_.at(s).size();k++)
						std::cout<<medodoidy_.at(s).at(k)<<", ";
					std::cout<<")"<<std::endl;
		}
	}while(kolejnaPentla);
	return medodoidy_;
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

double AlgorytmPam::tc(std::vector<int> klasyfikacjaPunktow){

//	policz sume cijh dla wszystkich elementow dla nowego medodoidu

// jesli stary metodoid nie zawieral obiektu Oj i nowy tez nie bedzie zawieral to cijh=0
// w przeciwnym wypadku policz Cjmp = d(Oj,O Nowy metodoid)-d(Oj,O stary metodoid)

	std::vector<punkt> nowe_medodoidy=medodoidy_;
	double tc_suma=0.0;
	for (int m=0;m<medodoidy_.size();m++){
	// stare medodidy
		double tc_min=DBL_MAX;
		for (int p=0; p<dane_.size(); p++){
			double tc=0.0;
			// kandydaci na nowe medodoidy
			std::vector<punkt> tymczasowe_nowe_metodoidy=medodoidy_;
			tymczasowe_nowe_metodoidy.at(m)=dane_.at(p); // wstawiamy nowy punkt w miejsce starego
			std::vector<int> nowa_klasyfikacja = klasyfikacja_punktow(tymczasowe_nowe_metodoidy,dane_);
			for(int j=0; j<dane_.size();j++){
			// klasyfikacja punktow dla nowej klasyfikacja
//				std::cout<<"przed if'ami"<<std::endl;
				// scenariusz 1. Oj przechodzi z Om do Oj,2
				if(klasyfikacjaPunktow.at(j)==m && nowa_klasyfikacja.at(j)!=p){
					tc+=cjmp(dane_.at(j),medodoidy_.at(m),dane_.at(nowa_klasyfikacja.at(j) ));
				}
				// scenariusz 2. Oj  z Om do Op
				if(klasyfikacjaPunktow.at(j)==m &&  nowa_klasyfikacja.at(j)==p){
					tc+=cjmp(dane_.at(j),medodoidy_.at(m),dane_.at(p));
				}
				// scenariusz 3. Oj nie było w klasie Om i nie przechodzi do Op
				if (klasyfikacjaPunktow.at(j)!=m &&  nowa_klasyfikacja.at(j)!=p)
					continue;
				// scenariusz 4. Oj nalezy do klasy reprezentowanej przez Oj,2
				// i przechodzi do klasy Op
				if (klasyfikacjaPunktow.at(j)!=m &&  nowa_klasyfikacja.at(j)==p){
					tc+=cjmp(dane_.at(j),medodoidy_.at(klasyfikacjaPunktow.at(j)),dane_.at(p));
				}


			}
			std::cout<<"nr "<< m <<" : (";
			for(int k=0;k<dane_.at(p).size();k++)
								std::cout<<dane_.at(p).at(k)<<", ";
							std::cout<<")"<<" z wynikiem tc= "<<tc;
			std::cout<<" w starej klasyfikacji:"<<klasyfikacjaPunktow.at(p)<<" w nowej: "<<nowa_klasyfikacja.at(p)<<std::endl;
			if (tc<tc_min){
				std::cout<<"tc_min= "<<tc_min<<"  ";
				tc_min=tc;
				// jezeli jakis punkt wpadnie a  potem wypadnie to tez sie dodaje :/
				tc_suma=+tc;
				nowe_medodoidy.at(m)=dane_.at(p);
				std::cout<<"nowy metodoid nr "<< m <<" : (";
				for(int k=0;k<nowe_medodoidy.at(m).size();k++)
					std::cout<<nowe_medodoidy.at(m).at(k)<<", ";
				std::cout<<")"<<" z wynikiem tc= "<<tc<<std::endl;
			}
		}
	}
	medodoidy_ =nowe_medodoidy;
	return tc_suma;
}

double AlgorytmPam::cij(punkt i,punkt j){
	double wynik=0;
	double kwadrat_wyniku=0;
	if(i.size()==j.size()){
		for(int k=0;k<i.size();k++)
			kwadrat_wyniku+=(i.at(k)-j.at(k))*(i.at(k)-j.at(k));
	}
	else
	{
		const std::string SIZE_OF_COMPARED_VECTORS_DONT_MATCH="SIZE_OF_COMPARED_VECTORS_DONT_MATCH";
		throw SIZE_OF_COMPARED_VECTORS_DONT_MATCH;
	}

	wynik=sqrt(kwadrat_wyniku);
	return wynik;
}

double AlgorytmPam::cjmp(punkt j,punkt m, punkt p){
	double wynik=cij(j,p)-cij(j,m);
	return wynik;
}

std::vector<int> AlgorytmPam::klasyfikacja_punktow(std::vector<punkt> metodoidy,std::vector<punkt> dane_do_klasyfikacji){
// klasyfikujemy punkt do najblizszego medodidu
	std::vector<int> klasyfikacja_punktow (dane_do_klasyfikacji.size());
	for(int j=0; j<dane_do_klasyfikacji.size();j++){
		double min_odleglosc=DBL_MAX;
		for (int i=0;i<metodoidy.size();i++){
			double odleglosc=cij(metodoidy.at(i),dane_do_klasyfikacji.at(j));
			if (odleglosc<min_odleglosc){
				min_odleglosc=odleglosc;
				klasyfikacja_punktow.at(j)=i;
			}

		}
//		std::cout<<"klasyfikacja punktu: ("<<dane_.at(j).first<<", "<<dane_.at(j).second<<") do klasy: "<<klasyfikacja_punktow.at(j)<<std::endl;
	}

	return klasyfikacja_punktow;
}



