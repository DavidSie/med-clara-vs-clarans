

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
	punkt punkt1 (1,1);
	punkt punkt2 (1.2, 1.2);
	punkt punkt3 (1.8, 1.8);

	punkt punkt4 (15, 15);
	punkt punkt5 (16, 16);
	punkt punkt6 (16.5, 16.5);

	punkt punkt7 (7,7);
	punkt punkt8 (8,8);
	punkt punkt9 (9,9);

	punkt punkt10 (0.9,0.9);
	punkt punkt11 (1.9,1.9);
	punkt punkt12 (1.2,0.9);
	punkt punkt13 (1.2,0.9);

	std::vector<punkt> dane;
	dane.push_back(punkt1);
	dane.push_back(punkt2);
	dane.push_back(punkt3);
	dane.push_back(punkt4);
	dane.push_back(punkt5);
	dane.push_back(punkt6);
	dane.push_back(punkt7);
	dane.push_back(punkt8);
	dane.push_back(punkt9);

	for(int i=0;i<60;i++){
		punkt punktNr (1+0.01*i,1+0.01*i);
		dane.push_back(punktNr);
	}
	return dane;
}



