/*
 * algorytmClarans.h
 *
 *  Created on: 17.01.2016
 *      Author: Michal Lutoborski
 */

 #include "algorytmClarans.h"

 #include <stdlib.h>
 #include <time.h>
 #include <algorithm>

std::pair<nodeClarans, double> AlgorytmClarans::calculate()
{
    /*
    Should find an improvement not to pick node which was already picked once
    */

    nodeClarans current;
    nodeClarans neighbor;

    AlgorytmPam pam;

    std::pair<nodeClarans, double> result;

    // Initialization
    double minCost = DBL_MAX;
    double tcCurrent = DBL_MAX;
    double tcNeighbor = DBL_MAX;

    for(int i = 0; i<num_local; i++)
    {
        std::cout << "<-----------------------MAIN ITERATION NO " << i << "----------------------->" << std::endl;
        // Pick random node from graph
        current = pickRandomNode();
        tcCurrent = pam.totalCost(dane_, current.getPosVector()).first;

        // current.printPosVector();
        // current.printDataVector();

        for(int j = 0; j<max_neighbor; )
        {
            // Pick random neighbor of current node
            neighbor = current.pickRandomNeighbor(dane_, k_);

            // Calculate cost of picked neighbor
            tcNeighbor = pam.totalCost(dane_, neighbor.getPosVector()).first;

            /*
            std::cout << "Current data:" << std::endl;
            current.printPosVector();
            // current.printDataVector();

            std::cout << "Neighbor data:" << std::endl;
            neighbor.printPosVector();
            // neighbor.printDataVector();

            std::cout << "Current total cost: " << tcCurrent << std::endl;
            std::cout << "Neighbor total cost: " << tcNeighbor << std::endl;
            */

            // Check neighbor cost
            if(tcNeighbor < tcCurrent)
            {
                current = neighbor;
                tcCurrent = tcNeighbor;
                j=0;
            }
            else j++;
        }

        // Check current cost against global
        if(tcCurrent < minCost)
        {
            bestNodeTC = minCost = tcCurrent;
            bestNode = current;
        }

        std::cout << "Best node data (so far):" << std::endl;
        bestNode.printPosVector();

        std::cout << "Best node total cost (so far): " << bestNodeTC << std::endl;
        result = std::make_pair(bestNode, bestNodeTC);
    }

    std::cout << "Best node data:" << std::endl;
    bestNode.printPosVector();

    std::cout << "Best node total cost: " << bestNodeTC << std::endl;

    result = std::make_pair(bestNode, bestNodeTC);

    return result;
}

nodeClarans AlgorytmClarans::pickRandomNode()
{
    nodeClarans node;
    wektorPunktow nVector;
    bool found = true;

    int randPos;
    std::vector<int> usedPos;
    std::vector<int>::iterator it;

    // We choose k random points from data and eliminate possibility of duplicates
    for(int i=0; i < k_; i++)
    {
        // We try to pick random position with uniform distribution
        while(found)
        {
            randPos = 0 + (rand() % (int)(n_-1 - 0 + 1));
            it = std::find(usedPos.begin(),usedPos.end(),randPos);

            if(it == usedPos.end())
            {
                found = false;
                usedPos.push_back(randPos);
            }
        }

        found = true;

        nVector.push_back(dane_.at(randPos));
    }

    node.setNode(usedPos, nVector);

    return node;
}
