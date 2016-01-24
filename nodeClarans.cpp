#include "nodeClarans.h"

nodeClarans nodeClarans::pickRandomNeighbor(const std::vector<std::vector<double> > &dane,const int medoidsQuantity)
{
    nodeClarans randomNeighbor;
    std::vector<int> positionVector = posVector;
    std::vector<int> tempPosVector = posVector;
    std::vector<int> checkPosVector;
    std::vector<std::vector<double> > dVector;
    int randPos;
    int n = dane.size();
    bool stop = false;
    bool notRandom = false;

    while(!stop)
    {
        notRandom = false;
        randPos = 0 + (rand() % (int)(n-1 - 0 + 1));
        for(int i = 0; i < tempPosVector.size(); i++)
        {
            if(tempPosVector.at(i)==randPos)
            {
                notRandom = true;
                break;
            }
        }
        if(!notRandom)
        {
            stop = true;

            tempPosVector.at(rand()%tempPosVector.size()) = randPos;

            for(int j = 0; j < createdNeighbors.size(); j++)
            {
                checkPosVector = createdNeighbors.at(j).getPosVector();
                if(tempPosVector==checkPosVector)
                {
                    tempPosVector = posVector;
                    notRandom = false;
                    stop = false;
                }
            }
        }
    }

    positionVector = tempPosVector;

    for(int i = 0; i < medoidsQuantity; i++)
    {
        dVector.push_back(dane.at(positionVector.at(i)));
    }

    randomNeighbor.setNode(positionVector, dVector);
    createdNeighbors.push_back(randomNeighbor);

    return randomNeighbor;
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



