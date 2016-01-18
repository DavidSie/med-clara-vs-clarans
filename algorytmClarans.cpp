/*
 * algorytmClarans.cpp
 *
 *  Created on: 12 gru 2015
 *      Author: davidsiecinski
 */

 #include "algorytmClarans.h"

 #include <stdlib.h>
 #include <time.h>
 #include <algorithm>

std::vector<punkt> AlgorytmClarans::calculate()
{
    wektorPunktow current;
    wektorPunktow neighbor;
    wektorPunktow bestNode;

    // Initialization
    double minCost = DBL_MAX;
    double tcCurrent = DBL_MAX;
    double tcNeighbor = DBL_MAX;

    for(int i = 0; i<num_local; i++)
    {
        // Pick random node from graph
        current = pickRandomNode();

        // Test purposes - printing vector
        std::cout << "Current vector: " << std::endl;
        for(int i=0; i<current.size(); i++)
        {
            std::cout << "Point " << i << ": < ";
            for(int j=0; j<current.at(i).size(); j++)
            {
                std::cout << current.at(i).at(j);
                if(i!=current.size()-1) std::cout << ", ";
                else std::cout << ">" << std::endl;
            }
        }

        for(int j = 0; j<max_neighbor; )
        {
            // Pick random neighbor of current node


            // Calculate cost of picked neighbor


            // Check neighbor cost
            if(tcNeighbor < tcCurrent)
            {
                current = neighbor;
                j=0;
            }
            else j++;
        }

        // Check current cost against global
        if(tcCurrent < minCost)
        {
            minCost = tcCurrent;
            bestNode = current;
        }
    }

    return bestNode;
}

wektorPunktow AlgorytmClarans::pickRandomNode()
{
    wektorPunktow node;
    bool found = false;

    int randPos;
    std::vector<int> usedPos;
    std::vector<int>::iterator it;

    // We choose k random points from data and eliminate possibility of duplicates
    for(int i=0; i < k_; i++)
    {
        // We try to pick random position with uniform distribution
        while(!found)
        {
            randPos = 0 + (rand() % (int)(n_-1 - 0 + 1));
            it = std::find(usedPos.begin(),usedPos.end(),randPos);

            if(it != usedPos.end())
            {
                found = true;
                usedPos.push_back(randPos);
            }
        }

        found = false;

        node.push_back(dane_.at(randPos));
    }

    // Test purposes - printing vector
    std::cout << "Used position vector: < ";
    for(int i=0; i<usedPos.size(); i++)
    {
        std::cout << usedPos.at(i);
        if(i!=usedPos.size()-1) std::cout << ", ";
        else std::cout << ">" << std::endl;
    }

    return node;
}

/*
 std::vector<punkt> AlgorytmClarans::wyliczenieMedodoidow()
 {
	std::vector<punkt> wynik;
	std::vector<wektorPunktow> wyniki;
	std::vector<double> tc_;
	for(int i=0;i<5;i++)
    {
	//	losujemy 40+2k danych ze zbioru
		std::cout<<"[INFO][CLARA] iteracja "<<i<<std::endl;
		std::vector<punkt> daneLosowe=losowanieProbekDanych(dane_,40+2*k_);
		AlgorytmPam pam=AlgorytmPam(daneLosowe,k_);
		wyniki.push_back(pam.pam());

		//	 liczymy dla wszystkich elementow average dissimilarity
		tc_.push_back(tc(pam,dane_));

	}

	// znajdywanie wyniku z najmniejszym tc
	double tc_min=DBL_MAX;
	for (int i=0;i<wyniki.size();i++)
    {
		if(tc_.at(i)<tc_min){
			tc_min=tc_.at(i);
			wynik=wyniki.at(i);
		}
	}
	std::cout<<"[INFO][CLARA] najlepszy wynik dla całego zbioru : "<<tc_min<<" dla punktow "<<std::endl;
	for (int i=0; i<wynik.size(); i++)
		wypiszPunkt( wynik.at(i));
	medoidy_=wynik;
	return wynik;
}
*/




