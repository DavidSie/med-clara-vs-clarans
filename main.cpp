

//#include <stdio.h>
#include <iostream>
#include <sstream>
#include "algorytmClara.h"
#include "algorytmClarans.h"
#include "readingModule.h"
#include "algorytmPam.h"

std::vector<punkt> generujDane();


using namespace std;

int main() {
	std::vector<punkt> dane=generujDane();

	AlgorytmClara algClara=AlgorytmClara(dane,2);
	time_t startClara = time(0);
	algClara.wyliczenieMedodoidow();
	time_t endClara = time(0);
	std::cout<<"[INFO] wspolczynnik Silhouette dla alg. Clara: "<<algClara.silhouette_score(dane,algClara.getMedoids())<<endl;

	double timeClara = difftime(endClara, startClara);
	std::cout<<"[INFO] czas wykonania algorytmu Clara: "<<timeClara<<" s"<<std::endl;

	AlgorytmPam algPam=AlgorytmPam(dane,2);
	time_t startPam = time(0);
	algPam.pam();
	time_t endPam = time(0);
	std::cout<<"[INFO] wspolczynnik Silhouette dla alg. Pam: "<<algPam.silhouette_score(dane,algPam.getMedoids())<<endl;
	double timePam = difftime(endPam, startPam);
	std::cout<<"[INFO] czas wykonania algorytmu Pam: "<<timePam<<" s"<<std::endl;

	std::cout<<"[INFO] srednia F-miara dla alg. Clara: "<<endl;
	algClara.fmiara(dane,algPam.getMedoids(),algClara.getMedoids());
    return 0;
}

std::vector<punkt> generujDane(){
//    testy alg. pam
//	int n=3;
//	int dl_wektora=2;


//    testy alg. clara
	int n=100;
	int dl_wektora=2;
	std::vector<punkt> dane;
	for(int i=0;i<n;i++){
		punkt punktNr (dl_wektora,1+i);
		dane.push_back(punktNr);
	}

	for(int i=0;i<n;i++){
		punkt punktNr (dl_wektora,550+i);
		dane.push_back(punktNr);
	}
	return dane;
}



