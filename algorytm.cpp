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
 	for(unsigned int j=0; j<dane_do_klasyfikacji.size();j++){
 		double min_odleglosc=DBL_MAX;
 		for (unsigned int i=0;i<metodoidy.size();i++){
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


 std::vector<double> Algorytm::intra_cluster_distance(std::vector<punkt> medoidy,std::vector<punkt> data){
	 //dla kazdego punktu liczyby sr odleglosc od medoidow
	 std::vector<double> intra_cluster_distance;
	 for(int i=0;i<data.size();i++){
		 double distance=0.0;
		 for(unsigned int j=0;j<medoidy.size();j++)
			 distance+=cij(medoidy.at(j),data.at(i));
		 intra_cluster_distance.push_back(distance/medoidy.size());
	 }
	 return intra_cluster_distance;

 }


 double Algorytm::odlegloscEuklidesowa(punkt i,punkt j){
	 return cij(i,j);
 }

// sysnonim odleglosc euklidesowa
 double Algorytm::cij(punkt i,punkt j){
 	double wynik=0;
 	double kwadrat_wyniku=0;
 	if(i.size()==j.size()){
 		for(unsigned int k=0;k<i.size();k++)
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

 double Algorytm::silhouette_score(std::vector<punkt> data,std::vector<punkt> medoids){

//	 srednia silhouette_samples
	 std::vector<double>samples= silhouette_samples(data,medoids);
	 double suma=0.0;
	 for(unsigned int i=0; i<samples.size();i++)
		 suma+=samples.at(i);
	 return suma/samples.size();
 }

 std::vector<double> Algorytm::silhouette_samples(std::vector<punkt> data,std::vector<punkt> medoids){
//	 The Silhouette Coefficient is calculated using the mean intra-cluster
//	     distance (``a``) and the mean nearest-cluster distance (``b``) for each
//	     sample.  The Silhouette Coefficient for a sample is ``(b - a) / max(a,
//	     b)``.
//	     Note that Silhouette Coefficent is only defined if number of labels
//	     is 2 <= n_labels <= n_samples - 1.
	 std::vector<double> sil_samples;
	 std::vector<int>klasyfikacja_punktow_= klasyfikacja_punktow(medoids,data);
	 std::vector<double> A=intra_cluster_distance( medoids,data); // dystans od najblizszego klastra (nie tego doktorego nalezy punkt)


	 std::vector<double> B; // dystans do najblizszego klastra (do ktorego nalezy)
	 for(int i;i<data.size();i++)
		 B.push_back( cij(data.at(i),medoids.at(klasyfikacja_punktow_.at(i))) );

	 sil_samples = iloraz(roznica(B,A), maximum(A, B))   ;

	 return sil_samples;
 }
 std::vector<double> Algorytm::maximum(std::vector<double> A, std::vector<double> B){
	 std::vector<double> max;
	 if(A.size()==B.size()){
	 		for(unsigned int i=0;i<A.size();i++)
	 			if (A.at(i)>B.at(i))
	 				max.push_back(A.at(i));
	 			else
	 				max.push_back(B.at(i));
	 	}
	 	else
	 	{
	 		const std::string SIZE_OF_COMPARED_VECTORS_DONT_MATCH="SIZE_OF_COMPARED_VECTORS_DONT_MATCH";
	 		throw SIZE_OF_COMPARED_VECTORS_DONT_MATCH;
	 }
	 return max;
 }

 std::vector<double> Algorytm::roznica(std::vector<double> A, std::vector<double> B){
	 std::vector<double> roznica;
	 if(A.size()==B.size()){
		 for(unsigned int i=0;i<A.size();i++)
			 roznica.push_back(A.at(i)-B.at(i));
	 	}
	 	else
	 	{
	 		const std::string SIZE_OF_COMPARED_VECTORS_DONT_MATCH="SIZE_OF_COMPARED_VECTORS_DONT_MATCH";
	 		throw SIZE_OF_COMPARED_VECTORS_DONT_MATCH;
	 }
	 return roznica;
 }

 std::vector<double> Algorytm::iloraz(std::vector<double> A, std::vector<double> B){
 	 std::vector<double> iloraz;
 	 if(A.size()==B.size()){
 		 for(unsigned int i=0;i<A.size();i++)
 			iloraz.push_back(A.at(i)/B.at(i));
 	 	}
 	 	else
 	 	{
 	 		const std::string SIZE_OF_COMPARED_VECTORS_DONT_MATCH="SIZE_OF_COMPARED_VECTORS_DONT_MATCH";
 	 		throw SIZE_OF_COMPARED_VECTORS_DONT_MATCH;
 	 }
 	 return iloraz;
  }
