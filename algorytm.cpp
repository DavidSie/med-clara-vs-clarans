/*
 * algorytm.cpp
 *
 *  Created on: 12 gru 2015
 *      Author: davidsiecinski
 */

#include "algorytm.h"


 void Algorytm::wypiszPunkt(punkt punkt_){
	 std::cout<<"[INFO] ( ";
	 for (int i=0; i<punkt_.size();i++)
		 std::cout<<punkt_.at(i)<<", ";
	 std::cout<<") "<<std::endl;
 }

 std::vector<int> Algorytm::klasyfikacja_punktow(std::vector<punkt> metodoidy,std::vector<punkt> dane_do_klasyfikacji){
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


 double Algorytm::cij(punkt i,punkt j){
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

// double Algorytm::silhouette_score(X, labels, metric='euclidean', sample_size=None,  random_state=None, **kwds){
//
////	 srednia silhouette_samples
//	 return 0.0;
// }
 std::vector<double> Algorytm::silhouette_samples(std::vector<punkt> data,std::vector<punkt> medoids){
//	 The Silhouette Coefficient is calculated using the mean intra-cluster
//	     distance (``a``) and the mean nearest-cluster distance (``b``) for each
//	     sample.  The Silhouette Coefficient for a sample is ``(b - a) / max(a,
//	     b)``.
//	     Note that Silhouette Coefficent is only defined if number of labels
//	     is 2 <= n_labels <= n_samples - 1.
	 std::vector<double> wynik;
	 return wynik;
 }
