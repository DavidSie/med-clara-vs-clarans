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

		std::cout<<"[INFO][PAM]current_cost: "<< current_cost<<std::endl;

		if( best_choice == medoids_idx){
			for(int i=0; i<medoids_idx.size();i++){
				medodoidy_.at(i)=dane_.at(medoids_idx.at(i));
				wypiszPunkt(medodoidy_.at(i));
				medoids_idx_=medoids_idx;
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


