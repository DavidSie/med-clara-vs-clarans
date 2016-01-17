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


 std::vector < std::vector <double> > Algorytm::fmiara(std::vector<punkt> dane,std::vector<punkt> medoidy,std::vector<punkt> estymata_medoidow){
	 std::vector<int> przydzial_do_klas= klasyfikacja_punktow(medoidy,dane);
	 std::vector<int> estymata_przydzialu_do_klas= klasyfikacja_punktow(estymata_medoidow,dane);
	 // nij - liczba obiektow klasy i przydzielona do klasy j
	 // ni  - liczba obiektow w klasie i (dot. estymaty)
	 // nj - liczba obiektow w klasie j (dot. estymaty)
	 std::vector<int> nj(estymata_medoidow.size(),0); // liczba obiektow przydzielonych do kolejnych klas
	 for(unsigned int i=0;i<estymata_przydzialu_do_klas.size();i++)
		 nj.at(estymata_przydzialu_do_klas.at(i))+=1;

	 std::vector<int> ni(medoidy.size(),0); // liczba obiektow przydzielonych do kolejnych klas
	 for(unsigned int i=0;i<przydzial_do_klas.size();i++)
		 ni.at(przydzial_do_klas.at(i))+=1;

	 std::vector < std::vector <int> > nij; // zewnetrzny wektor i - do kad powinny trafic , wew j- dokad trafily finalnie
	 std::vector < std::vector <double> > recall;
	 std::vector < std::vector <double> > precision;
	 std::vector < std::vector <double> > fMiara;

	 //inicjalizacja
	 for(unsigned int i=0;i<medoidy.size();i++){
		 std::vector <int> tmp;
		 std::vector <double> tmpDouble;
		 recall.push_back(tmpDouble);
		 precision.push_back(tmpDouble);
		 fMiara.push_back(tmpDouble);
		 nij.push_back(tmp);
		 for(unsigned int j=0;j<estymata_medoidow.size();j++){
			 nij.at(i).push_back(0);
			 recall.at(i).push_back(0.0);
			 precision.at(i).push_back(0.0);
			 fMiara.at(i).push_back(0.0);
		 }
	 }


	 for(unsigned int i=0;i<dane.size();i++)
		 nij.at(przydzial_do_klas.at(i)).at(estymata_przydzialu_do_klas.at(i))+=1;


	 double sredniaFmiara=0.0;
	 for(unsigned int i=0;i< nij.size(); i++)
		 for(unsigned int j=0;j< nij.at(i).size(); j++){
			 std::cout<<"i= "<<i<<" j= "<<j<<std::endl;
			 std::cout<<"nij.at(i).at(j) "<<nij.at(i).at(j)<<std::endl;
			 std::cout<<"ni.at(i) "<<(double)ni.at(i)<<std::endl;
			 std::cout<<"nj.at(j) "<<(double)nj.at(j)<<std::endl;
			 recall.at(i).at(j)=nij.at(i).at(j)/(double)ni.at(i);
			 std::cout<<"recall.at(i).at(j) "<<recall.at(i).at(j)<<std::endl;
			 precision.at(i).at(j)=nij.at(i).at(j)/(double)nj.at(j);
			 std::cout<<"precision.at(i).at(j) "<<precision.at(i).at(j)<<std::endl;
			 if (precision.at(i).at(j)<0.0001 && recall.at(i).at(j)<0.0001 )
				 continue;
			 fMiara.at(i).at(j)=2*recall.at(i).at(j)*precision.at(i).at(j)/(precision.at(i).at(j)+recall.at(i).at(j));
			 std::cout<<"fMiara.at(i).at(j) "<<fMiara.at(i).at(j)<<std::endl;
			 std::cout<<"_______________________________________ "<<std::endl;
			 sredniaFmiara+= fMiara.at(i).at(j);
		 }
	 std::cout<<"[INFO] macierz F-miary";
	 // rysowanie macierzy
	 rysujMacierz(fMiara);

	 return fMiara;
 }
 void  Algorytm::rysujMacierz( std::vector < std::vector <double> > dane){
	 std::cout<<std::endl;
	 for(unsigned int i=0;i< dane.size(); i++){

		std::cout<<"[INFO] |";
	 	for(unsigned int j=0;j< dane.at(i).size(); j++)
	 		std::cout<< dane.at(i).at(j)<<"  ";
	 	std::cout<<"|";
	 	std::cout<<std::endl;
	 }
	 std::cout<<std::endl;
 }
