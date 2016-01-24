/*
 * algorytmClarans.h
 *
 *  Created on: 17.01.2016
 *      Author: Michal Lutoborski
 */

#ifndef ALGORYTMCLARANS_H_
#define ALGORYTMCLARANS_H_

#include "algorytm.h"
#include "algorytmPam.h"
#include "nodeClarans.h"

class AlgorytmClarans : public  Algorytm
{
    public:
        AlgorytmClarans(const std::vector<punkt> &dane,int max_neighbor, int num_local, int medoidsQuantity)
        {
            dane_=dane;
            k_= medoidsQuantity;
            n_=dane.size();

            this->max_neighbor = max_neighbor;
            this->num_local = num_local;
        }

        std::pair<nodeClarans, double> calculate();

    private:
        int max_neighbor;
        int num_local;
        int k_;
        int n_;
        int sampleSize;

        nodeClarans bestNode;
        double bestNodeTC;

        nodeClarans pickRandomNode();
};




#endif /* ALGORYTMCLARANS_H_ */
