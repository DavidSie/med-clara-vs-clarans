/*
 * algorytmPam.cpp
 *
 *  Created on: 27 gru 2015
 *      Author: davidsiecinski
 */

#include "algorytmPam.h"



std::vector<punkt> AlgorytmPam::pam(){
	// losowanie k obiektow ze zbioru n obiektow

	std::vector<int> medoids_idx;
	for(int j=0;j<k_;j++){
		medoids_idx.push_back(wylosuj(medoids_idx));
		medodoidy_.push_back(dane_.at(medoids_idx.at(j)));
	}

	std::pair< double, std::map<int, std::vector<int> >  > extractor=totalCost(dane_,medoids_idx);
	double pre_cost=extractor.first;
	std::map<int, std::vector<int> > medoids=extractor.second;
	std::cout<<" medoids.size() "<<medoids.size()<<std::endl;
	double current_cost = pre_cost;
	std::vector<int> best_choice;
	std::map<int, std::vector<int> > best_res;
	int iter_count = 0;
	do{
		for (std::map<int, std::vector<int> >::iterator it = medoids.begin(); it != medoids.end(); it++ ){
			int m=it->first;
			std::vector<int> itemVector=it->second;
			for(std::vector<int>::iterator item = itemVector.begin(); item != itemVector.end(); ++item){
				if (*item!=m){
					int idx=index(medoids_idx,m);
					int swap_temp = medoids_idx.at(idx);
					medoids_idx.at(idx) = *item;
					std::pair< double, std::map<int, std::vector<int> >  > extractor2 = totalCost(dane_, medoids_idx);
					double tmp_cost=extractor2.first;
					std::map<int, std::vector<int> > tmp_medoids=extractor2.second;
					if (tmp_cost < current_cost){
						best_choice = medoids_idx; // Make a copy
						best_res = tmp_medoids;  // Make a copy
						current_cost = tmp_cost;
					}
					medoids_idx.at(idx) = swap_temp;
				}
			}
		}
		// Increment the counter
		iter_count += 1;

		std::cout<<"current_cost: "<< current_cost<<std::endl;

		if( best_choice == medoids_idx){
			for(int i=0; i<medoids_idx.size();i++){
				medodoidy_.at(i)=dane_.at(medoids_idx.at(i));
				wypiszPunkt(medodoidy_.at(i));
			}
			break;
		}

		// Update the cost and medoids
		if (current_cost <= pre_cost){
			pre_cost = current_cost;
			medoids = best_res;
			medoids_idx = best_choice;
		}

	}while(true);
	return medodoidy_;
}

int AlgorytmPam::index(std::vector<int> data,int value){
	int index=-1;
	for(int i=0;i<data.size();i++)
		if(data.at(i)==value){
			index=i;
		}
	return index;

}
 void AlgorytmPam::wypiszPunkt(punkt punkt_){
	 std::cout<<"( ";
	 for (int i=0; i<punkt_.size();i++)
		 std::cout<<punkt_.at(i)<<", ";
	 std::cout<<") "<<std::endl;
 }


// zwraca tc , medoids
std::pair< double, std::map<int, std::vector<int> >  >  AlgorytmPam::totalCost(std::vector<punkt> data,std::vector<int> medoids_idx){
	int size = dane_.size();
	double total_cost=0.0;
	std::map<int, std::vector<int> >  medoids;
	std::vector<int> emptyvector;
	for(int idx=0;idx<medoids_idx.size();idx++)
		medoids[medoids_idx.at(idx)]=emptyvector;

	for(int i=0;i<size;i++){
		int choice= -1;
		double min_cost=DBL_MAX;
		for (std::map<int, std::vector<int> >::iterator it = medoids.begin(); it != medoids.end(); it++ ){
			int m=it->first;
			double tmp=cij(data.at(m),data.at(i));
			if (tmp<min_cost){
				choice=m;
				min_cost=tmp;
			}
		}
		medoids.at(choice).push_back(i);
		total_cost += min_cost;
	}


	std::pair< double, std::map<int, std::vector<int> >  > wynik;
	wynik.first=total_cost;
	wynik.second=medoids;
	return wynik;
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

std::vector<double> AlgorytmPam::tc(std::vector<int> klasyfikacjaPunktow){

//	policz sume cijh dla wszystkich elementow dla nowego medodoidu


	std::vector<punkt> nowe_medodoidy=medodoidy_;
	double tc_suma=0.0;
	std::vector<double> tc_vector (k_,DBL_MAX);
	for (int m=0;m<medodoidy_.size();m++){
	// stare medodidy
		double tc_min=DBL_MAX;
		std::pair<int,double> medodoid_kandydat; // <polozenie,wyliczone tc>
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
//				if(klasyfikacjaPunktow.at(j)==m && nowa_klasyfikacja.at(j)!=p){
//					double tc_temp=cjmp(dane_.at(j),medodoidy_.at(m),dane_.at(nowa_klasyfikacja.at(j) ));
//					//std::cout<<"scenariusz 1 tmp+="<<tc_temp<<std::endl;
//					tc+=tc_temp;
//				}
//				// scenariusz 2. Oj  z Om do Op
//				if(klasyfikacjaPunktow.at(j)==m &&  nowa_klasyfikacja.at(j)==p){
				double tc_temp=cjmp(dane_.at(j),medodoidy_.at(m),dane_.at(p));
				std::cout<<"scenariusz 2 tmp+="<<tc_temp<<std::endl;
				tc+=tc_temp;
//				}
//				// scenariusz 3. Oj nie było w klasie Om i nie przechodzi do Op
//				if (klasyfikacjaPunktow.at(j)!=m &&  nowa_klasyfikacja.at(j)!=p)
//					//std::cout<<"scenariusz 3"<<std::endl;
//					continue;
//				// scenariusz 4. Oj nalezy do klasy reprezentowanej przez Oj,2
//				// i przechodzi do klasy Op
//				if (klasyfikacjaPunktow.at(j)!=m &&  nowa_klasyfikacja.at(j)==p){
//					double tc_temp=cjmp(dane_.at(j),medodoidy_.at(klasyfikacjaPunktow.at(j)),dane_.at(p));
////					std::cout<<"scenariusz 4 tmp+="<<tc_temp<<std::endl;
//					tc+= tc_temp;
//				}


			}
//			std::cout<<"nr "<< m <<" : (";
//			for(int k=0;k<dane_.at(p).size();k++)
//								std::cout<<dane_.at(p).at(k)<<", ";
//							std::cout<<")"<<" z wynikiem tc= "<<tc;
//			std::cout<<" w starej klasyfikacji:"<<klasyfikacjaPunktow.at(p)<<" w nowej: "<<nowa_klasyfikacja.at(p)<<std::endl;

			//	 zapisz polozenie  oraz tc nowego kandydata
			if(tc<medodoid_kandydat.second){
				medodoid_kandydat.first=p;
				medodoid_kandydat.second=tc;
			}
		}

		//		zamien stary medodoid z nowym
		// zamiast tc_suma zrob vector<tc> o dlugosci k_ i jego przekaz
		if (medodoid_kandydat.second<0){
			nowe_medodoidy.at(m)=dane_.at(medodoid_kandydat.first);
			tc_vector.at(m)=medodoid_kandydat.second;

			std::cout<<"nowy medodoid nr "<< m <<" : (";
			for(int k=0;k<medodoidy_.at(m).size();k++)
				std::cout<<medodoidy_.at(m).at(k)<<", ";
			std::cout<<")"<<" z wynikiem tc= "<<tc_vector.at(m)<<std::endl;
		}
	}
	medodoidy_ =nowe_medodoidy;
	return tc_vector;
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



