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
	 //dla kazdego punktu
	 // srednia odleglosc punktu od do innych punktow w klastrze
	 std::vector<double> intra_cluster_distance;
	 std::vector<int> klasyfikacja=klasyfikacja_punktow(medoidy,data);
	 for(unsigned int i=0;i<data.size();i++){
		 double distance=0.0;
		 int nr_klastra=klasyfikacja.at(i);
		 std::vector<punkt> punkty_w_klastrze;
		 //poszykiwanie punktow z tego klastra
		 for(unsigned int j=0;j<data.size();j++){
			 if(klasyfikacja.at(j)==nr_klastra)
				 punkty_w_klastrze.push_back(data.at(j));
		 }
		 for(unsigned int k=0;k<punkty_w_klastrze.size();k++)
			 distance+=cij(punkty_w_klastrze.at(k),data.at(i));
		 intra_cluster_distance.push_back(distance/punkty_w_klastrze.size());
	 }
	 return intra_cluster_distance;

 }
 std::vector<double> Algorytm::nearest_cluster_distance(std::vector<punkt> medoidy,std::vector<punkt> data){
	 // liczymy srednia odleglosci od punktu w innych klastach
	 // zwracamy minimum powyższych wynikow
	 std::vector<double> nearest_cluster_distance(data.size(),DBL_MAX);
	 std::vector<int> klasyfikacja=klasyfikacja_punktow(medoidy,data);
	 unsigned int ilosc_klastrow=medoidy.size()+1;
	 for(unsigned int i=0;i<data.size();i++){
			 unsigned int nr_klastra=klasyfikacja.at(i);
			 std::vector<double> srednie; // srednie dla kazdego klastra

			 // iteracja po innych klastrach
			 for(unsigned int id_klastra=0;id_klastra<ilosc_klastrow;id_klastra++){
				 std::vector<punkt> punkty_w_klastrze;
				 if(id_klastra==nr_klastra)
					 continue;
				 for(unsigned int j=0;j<data.size();j++){
					 if(klasyfikacja.at(j)==id_klastra)
						 punkty_w_klastrze.push_back(data.at(j));
				 }
				 //sumujemy punkty w klastrze i dzielimy przez ilosc
				double suma=0.0;
				for(unsigned int j=0;j<punkty_w_klastrze.size();j++){
					suma+=cij(data.at(i),punkty_w_klastrze.at(j));
				}
				srednie.push_back(suma/punkty_w_klastrze.size());
			 }
			 //wyszukiwanie minimalnej sredniej
			 for(unsigned int iter=0; iter<srednie.size();iter++)
				 if(nearest_cluster_distance.at(i)>srednie.at(iter))
					 nearest_cluster_distance.at(i)=srednie.at(iter);
	 }
	 //poszykiwanie punktow z tego klastra

	 //

	 return nearest_cluster_distance;
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
 		const std::string SIZE_OF_COMPARED_VECTORS_DONT_MATCH="[ERROR][Cij] SIZE_OF_COMPARED_VECTORS_DONT_MATCH";
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

	 // srednia odleglosc punktu od do innych punktow w klastrze
	 std::vector<double> A=intra_cluster_distance( medoids,data); // dystans od najblizszego klastra (nie tego doktorego nalezy punkt)

	 // minimalny średni dystans pomiedzy i-tym punktem a wszystkimi pozostalymi punktami (z poza klastra)
	 std::vector<double> B=nearest_cluster_distance( medoids,data);

//	 for(unsigned int i=0;i<data.size();i++){
//		 B.push_back( cij(data.at(i),medoids.at(klasyfikacja_punktow_.at(i))) );
//	 }
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
	 		std::ostringstream size1;
	 		std::ostringstream size2;
	 		size1 << A.size();
	 		size2 << B.size();
	 		const std::string SIZE_OF_COMPARED_VECTORS_DONT_MATCH="[ERROR][MAXIMUM] SIZE_OF_COMPARED_VECTORS_DONT_MATCH no. 1 size= "+ size1.str() +" no. 2 size= " + size2.str();
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
	 		std::ostringstream size1;
	 		std::ostringstream size2;
	 		size1 << A.size();
	 		size2 << B.size();
	 		const std::string SIZE_OF_COMPARED_VECTORS_DONT_MATCH="[ERROR][ROZNICA] SIZE_OF_COMPARED_VECTORS_DONT_MATCH no. 1 size= "+ size1.str() +" no. 2 size= " + size2.str();
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
 	 		const std::string SIZE_OF_COMPARED_VECTORS_DONT_MATCH="[ERROR][ILORAZ] SIZE_OF_COMPARED_VECTORS_DONT_MATCH";
 	 		throw SIZE_OF_COMPARED_VECTORS_DONT_MATCH;
 	 }
 	 return iloraz;
  }
