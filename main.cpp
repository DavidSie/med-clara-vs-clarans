
//#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "algorytmClara.h"
#include "algorytmClarans.h"
#include "readingModule.h"
#include "algorytmPam.h"

//std::vector<punkt> generujDane();
void ReadFile(wektorPunktow *pVector);
void ShowMenu(wektorPunktow dane);

// Global variables
AlgorytmPam algPam;
bool pamCalculated = false;

using namespace std;

int main() {
	// std::vector<punkt> dane=generujDane();

	// Initialize random
	srand( time( NULL ) );

	// Set data vector which is taking data from Reading Module
	vector<punkt> dane;
	ReadFile(&dane);

	while(1) ShowMenu(dane);

    return 0;
}

void ReadFile(wektorPunktow *pVector)
{
    string fullPath = "";
    vector<double> yeti;
    bool pathOK = false;
    char ster = '0';
    bool sterOK = false;
    ifstream infile;

    cout << "<< ---------- READING MODULE ---------- >>" << endl;
    cout << "File which will be loaded to the program must contain information" << endl;
    cout << "written in form and order described in the link below:" << endl;
    cout << "http://archive.ics.uci.edu/ml/machine-learning-databases/car/car.c45-names" << endl;

    while(!pathOK)
    {
        sterOK = false;
        string defaultPath = "c:\\users\\michal\\desktop\\car.data.txt";

        cout << "Please enter full path to the file:" << endl;

        // To defaultPath just uncomment the following line and comment the line after it
        fullPath = defaultPath;
        // cin >> fullPath;

        cin.clear();
        cin.sync();

        while(!sterOK)
        {
            cout << "PATH: " << fullPath << endl;
            cout << "Is path correct? [Y/N]" << endl;
            cin >> ster;
            cin.clear();
            cin.sync();

            if(ster=='Y')
            {
                infile.open(fullPath.c_str());
                if(infile.good())
                {
                    sterOK = true;
                    pathOK = true;
                }
                else
                {
                    cout << "The path which you provided is wrong. Maybe filename with extension is not included in path?" << endl;
                }
            }
            else if(ster=='N') sterOK = true;
            else cout << "You inserted wrong symbol. Try again" << endl;
        }
    }

    // Reading from file and transforming data
    cout << endl << "Your file was opened correctly. Data contained in the file will be now transformed to vector of points";
    cout << "which makes it enable for further calculations. Transformation values are listed in project documentation." << endl;

    string sTemp, line;
    int sStart = 0;
    int categoryId = 0;
    punkt pTemp;

    while(!infile.eof())
    {
        pTemp.clear();
        categoryId = 0;

        getline(infile,line);

        // cout << line << endl;
        for(int i = 0; i < line.size(); i++)
        {
            if(line[i]==',')
            {
                sTemp = line.substr(sStart,i-sStart);

                // cout << sTemp << endl;

                switch(categoryId)
                {
                case 0:
                    {
                        if(sTemp=="vhigh") pTemp.push_back(1.4);
                        else if(sTemp=="high") pTemp.push_back(1.3);
                        else if(sTemp=="med") pTemp.push_back(1.2);
                        else if(sTemp=="low") pTemp.push_back(1.1);
                        break;
                    }
                case 1:
                    {
                        if(sTemp=="vhigh") pTemp.push_back(2.4);
                        else if(sTemp=="high") pTemp.push_back(2.3);
                        else if(sTemp=="med") pTemp.push_back(2.2);
                        else if(sTemp=="low") pTemp.push_back(2.1);
                        break;
                    }
                case 2:
                    {
                        if(sTemp=="2") pTemp.push_back(3.1);
                        else if(sTemp=="3") pTemp.push_back(3.2);
                        else if(sTemp=="4") pTemp.push_back(3.3);
                        else if(sTemp=="5more") pTemp.push_back(3.4);
                        break;
                    }
                case 3:
                    {
                        if(sTemp=="2") pTemp.push_back(4.1);
                        else if(sTemp=="4") pTemp.push_back(4.2);
                        else if(sTemp=="more") pTemp.push_back(4.3);
                        break;
                    }
                case 4:
                    {
                        if(sTemp=="small") pTemp.push_back(5.1);
                        else if(sTemp=="med") pTemp.push_back(5.2);
                        else if(sTemp=="big") pTemp.push_back(5.3);
                        break;
                    }
                case 5:
                    {
                        if(sTemp=="low") pTemp.push_back(6.1);
                        else if(sTemp=="med") pTemp.push_back(6.2);
                        else if(sTemp=="high") pTemp.push_back(6.3);
                        break;
                    }
                }

                categoryId++;
                sStart = i+1;
            }
            else if(i==line.size()-1)
            {
                sTemp = line.substr(sStart,i-sStart+1);

                // cout << sTemp << endl;

                if(sTemp=="unacc") pTemp.push_back(0.1);
                else if(sTemp=="acc") pTemp.push_back(0.2);
                else if(sTemp=="good") pTemp.push_back(0.3);
                else if(sTemp=="vgood") pTemp.push_back(0.4);
                sStart = 0;
            }
        }

        pVector->push_back(pTemp);
    }

    infile.close();

    // Part checking if creating pointVector works correctly -> WORKS
    /*
    for(int i = 0; i < pVector->size(); i++)
    {
        cout << "Wiersz nr. " << i << ": ";

        for(int j = 0; j < 7; j++)
        {
            cout << pVector->at(i).at(j);
            if(j!=6) cout << ", ";
            else cout << endl;
        }
    }
    */
}

void ShowMenu(wektorPunktow dane)
{
    /*
    Method contains menu for an application. It should be devided to 3 parts for 3 algorithms.
    It would be cool if user could input all necessary parameters. To be implemented for now.
    Time measuring function should give time in miliseconds - can be provided from my other
    project if necessary.
    */

    cout << "\n<<---------------------- CLARA VS CLARANS ---------------------->>" << endl;
    cout << "Wybierz metode grupowania: [a/b]" << endl;
    cout << "a - grupowanie przy uzyciu algorytmu CLARA" << endl;
    cout << "b - grupowanie przy uzyciu algorytmu CLARANS" << endl;
    cout << "W celu zamkniecia programu nacisnij kombinacje klawiszy CTRL+C lub" << endl;
    cout << "po prostu zamknij program." << endl;

    bool sterOK = false;
    char ster = ' ';

    std::pair<nodeClarans, double> claransBest;

    int k = 2;
    int kMNClar = 250;
    int kNLClar = 2;

    clock_t startPam, endPam;

    while(!sterOK)
    {
        cin >> ster;
        cin.clear();
        cin.sync();

        if(ster=='a')
        {
            sterOK = true;

            std::cout << "Prosze wprowadzic parametry algorytmu" << std::endl;
            std::cout << "Prosze wprowadzic liczbe medioidow: " << std::endl;
            std::cin >> k;

            std::cout << "<<---------------------- CLARA ALGORITHM ---------------------->>" << std::endl;

            AlgorytmClara algClara=AlgorytmClara(dane,k);
            clock_t startClara = std::clock();
            algClara.wyliczenieMedodoidow();
            clock_t endClara = std::clock();

            if(pamCalculated==false)
            {
                algPam=AlgorytmPam(dane,k);
                startPam = std::clock();
                algPam.pam();
                endPam = std::clock();
                pamCalculated = true;
            }

            std::cout<<"[INFO][CLARA] Średnia F-miara dla alg. CLARA: "<<std::endl;
            algClara.fmiara(dane,algPam.getMedoids(),algClara.getMedoids());

            std::cout<<"[INFO][PAM] Współczynnik Silhouette dla alg. Pam: "<<algPam.silhouette_score(dane,algPam.getMedoids())<<endl;
            double timePam = (endPam - startPam) / (double)(CLOCKS_PER_SEC / 1000);
            std::cout<<"[INFO][PAM] Czas wykonania algorytmu Pam: "<<timePam<<" ms"<<std::endl;

            std::cout<<"[INFO] wspolczynnik Silhouette dla alg. Clara: "<<algClara.silhouette_score(dane,algClara.getMedoids())<<endl;
            double timeClara = (endClara - startClara) / (double)(CLOCKS_PER_SEC / 1000);
            std::cout<<"[INFO] Czas wykonania algorytmu Clara: "<<timeClara<<" ms"<<std::endl;
        }
        else if(ster=='b')
        {
            sterOK = true;

            std::cout << "Prosze wprowadzic parametry algorytmu" << std::endl;
            std::cout << "Prosze wprowadzic liczbe medioidow: " << std::endl;
            std::cin >> k;

            std::cout << "Prosze wprowadzic maksymalna liczbe sasiadow: " << std::endl;
            std::cin >> kMNClar;

            std::cout << "Prosze wprowadzic liczbe iteracji algorytmu: " << std::endl;
            std::cin >> kNLClar;

            std::cout << "<<---------------------- CLARANS ALGORITHM ---------------------->>" << std::endl;

            AlgorytmClarans algClarans = AlgorytmClarans(dane, kMNClar, kNLClar, k);
            clock_t startClarans = std::clock();
            claransBest = algClarans.calculate();
            clock_t endClarans = std::clock();

            if(pamCalculated==false)
            {
                algPam=AlgorytmPam(dane,k);
                startPam = std::clock();
                algPam.pam();
                endPam = std::clock();
                pamCalculated = true;
            }

            std::cout<<"[INFO][PAM] Współczynnik Silhouette dla alg. Pam: "<<algPam.silhouette_score(dane,algPam.getMedoids())<<std::endl;
            double timePam = (endPam - startPam) / (double)(CLOCKS_PER_SEC / 1000);
            std::cout<<"[INFO][PAM] Czas wykonania algorytmu Pam: "<<timePam<<" ms"<<std::endl;

            std::cout << "[INFO][CLARANS] Średnia F-miara dla alg. Clarans: " << std::endl;
            algClarans.fmiara(dane,algPam.getMedoids(),claransBest.first.getDataVector());

            std::cout << "[INFO][CLARANS] Współczynnik Silhouette dla alg. Clarans: " << std::endl;
            std::cout << algClarans.silhouette_score(dane,claransBest.first.getDataVector()) << std::endl;

            double timeClarans = (endClarans - startClarans) / (double)(CLOCKS_PER_SEC / 1000);
            std::cout<<"[INFO][CLARANS] Czas wykonania algorytmu Clarans: "<< timeClarans << " ms" << std::endl;

            std::cout << "Reset PAM [y/n]?" << std::endl;

            char sterPam;
            std::cin >> sterPam;
            if(sterPam=='y') pamCalculated = false;

        }
        else cout << "Niewlasciwy znak. Wybierz opcje a lub b." << endl;
    }

    getchar();
}
