#include "nodeClarans.h"

nodeClarans nodeClarans::pickRandomNeighbor()
{
    nodeClarans randomNeighbour;
    std::vector<int> positionVector = posVector;

    bool stop = false;

    while(!stop)
    {
        rand()
    }



    return randomNeighbour;
}

void nodeClarans::printPosVector()
{
    // Test purposes - printing vector
    std::cout << "Used position vector: < ";
    for(int i=0; i<posVector.size(); i++)
    {
        // Table notation is from 0 not from 1 so we need to add 1 for correct numeration
        std::cout << posVector.at(i) + 1;
        if(i!=posVector.size()-1) std::cout << ", ";
        else std::cout << ">" << std::endl;
    }
}

void nodeClarans::printDataVector()
{
    // Test purposes - printing vector
    std::cout << "Current vector: " << std::endl;
    for(int i=0; i<dataVector.size(); i++)
    {
        std::cout << "Point " << i << ": < ";
        for(int j=0; j<dataVector.at(i).size(); j++)
        {
            std::cout << dataVector.at(i).at(j);
            if(j!=dataVector.at(i).size()-1) std::cout << ", ";
            else std::cout << ">" << std::endl;
        }
    }
}



