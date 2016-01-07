

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
//	AlgorytmClara algClara=AlgorytmClara(dane,2);
//	algClara.wyliczenieMedodoidow();

	AlgorytmPam algPam=AlgorytmPam(generujDane(),2);
	algPam.pam();
    return 0;
}

std::vector<punkt> generujDane(){

	int n=5;
	std::vector<punkt> dane;
	for(int i=0;i<n;i++){
		punkt punktNr (4,1+i);
		dane.push_back(punktNr);
	}

	for(int i=0;i<n;i++){
		punkt punktNr (4,80+i);
		dane.push_back(punktNr);
	}
	return dane;
}



