#include <iostream>

#ifndef _TopSynthFunction_h_
#define _TopSynthFunction_h_
#include "TopSynthFunction.h"
#endif

using namespace std;
#include <stdlib.h>     /* srand, rand */
#include <cmath>
#include <time.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdio.h>

#define __SYNTHESIS__
void TestBench(float in1, float in2, float out){
	dataType FirstBiasBuffer[2][3] = {
				{ 0.15, 0.20, 0.35}, //neuron one w1 w2 w3
				{ 0.25, 0.30, 0.35}, //neuron two w1 w2 w3
			};
	dataType SecondBiasBuffer[2][3] = {
				{ 0.40, 0.45, 0.60}, //neuron one w1 w2 w3
				{ 0.50, 0.55, 0.60}, //neuron two w1 w2 w3
			};

	dataType GoldenFirstBiasBuffer[2][3] = {
				{ 0.149780716, 0.19956143, 0.35}, //neuron one w1 w2 w3
				{ 0.24975114, 0.29950229, 0.35}, //neuron two w1 w2 w3
			};

	dataType GoldenSecondBiasBuffer[2][3] = {
				{ 0.35891648, 0.408666186, 0.60}, //neuron one w1 w2 w3
				{ 0.511301270, 0.561370121, 0.60}, //neuron two w1 w2 w3
			};

	//Initialise weights


	//Do backprop once

	//Compare results
};


template <int arrsize>
float calcError(dataType resultglob[arrsize], ioDataType targetglob[arrsize])
		{
			dataType totalError = 0;
			dataType result[arrsize];
			dataType target[arrsize];


			for(int i = 0; i < arrsize; i++)
			{
				result[i] = resultglob[i];
				target[i] = (dataType)targetglob[i];
			}

			for (int i = 0; i < arrsize; i++)
			{
					totalError = totalError +  ((target[i] - result[i])*(target[i] - result[i]))/2;
			}
			return totalError;
		};

string convertToString(char* a, int size)
{
    string s = a;
    return s;
}


void read_record(float *allArray)
{
    // File pointer https://www.geeksforgeeks.org/csv-file-management-using-c/
    fstream fin;

    // Open an existing file
    fin.open("/home/bartek/VivadoHLS/NeuralNetworkV2/Data/IRTestShufle.txt", ios::in);

    // Read the Data from the file
    // as String Vector
    vector<float> row;
    string line, word, temp;
    int roll2, rollnum;
    int j = 0;

    while (!fin.eof()) {

        row.clear();
        // read an entire row and
        // store it in a string variable 'line'
        getline(fin, line);

        // used for breaking words
        stringstream s(line);

        // read every column data of a row and
        // store it in a string variable, 'word'
        while (getline(s, word, ',')) {
            // add all the column data
            // of a row to a vector
            row.push_back(stof(word));
        }
            for (int i = 0; i <= 6; i++)
            {
            	 allArray[j+i] = row[i];
            }
            j = j + 7;



    }

}

void xorTest();

int main(){

	cout.precision(6);
	float allArray[1050];
	read_record(allArray);
	//xorTest();

	ioDataType A[4] = {0, 0};
	ioDataType B[3] = {0};
	dataType gold[3] = {0};

	dataType bufferOne[inputsize] = {0};
	dataType bufferTwo[inputsize] = {0};
	dataType total;
	int iter = 0;
	int maxiter = 0;
	int limit = 0;
	dataType maxerror = 50; //przypadkowa wysoka wartosc
	int x = 0;






	do {
	for (int i = 0; i < (1050); i = i + 7) //150 danych 4 data we + 3 grupy. Leci przez caly dataset
	{

			//4 danych we
			A[0] = allArray[i];
			A[1] = allArray[i+1];
			A[2] = allArray[i+2];
			A[3] = allArray[i+3];
			//3 grupy

			gold[0] = allArray[i+4];
			gold[1] = allArray[i+5];
			gold[2] = allArray[i+6];


			TopFun(A, gold, 1); //1 = nauka

	}
	x++;
	cout << endl<< "XXX: " << x << endl;
	} while (x < 500);

	float tempacu = 0;

	int zlaKlasyfikacjaGrupy1 = 0, dobraKlasyfikacjaGrupy1 = 0;
	int zlaKlasyfikacjaGrupy2 = 0, dobraKlasyfikacjaGrupy2 = 0;
	int zlaKlasyfikacjaGrupy3 = 0, dobraKlasyfikacjaGrupy3 = 0;
	int zlaKlasyfikacja = 0, dobraKlasyfikacja = 0;

	 string line;
	 string filename = "/home/bartek/VivadoHLS/NeuralNetworkV2/Data/Classification.csv";
	 ofstream myfile(filename);
	 if (myfile.is_open())
		 {
					     myfile.close();
		}
					    else cout << "Unable to open file";
	for (int i = 0; i < (1050); i = i + 7) //150 danych 4 data we + 3 grupy. Leci przez caly dataset
		{

				//4 danych we
				A[0] = allArray[i];

				A[1] = allArray[i+1];
				A[2] = allArray[i+2];
				A[3] = allArray[i+3];
				//3 grupy
				gold[0] = allArray[i+4];
				gold[1] = allArray[i+5];
				gold[2] = allArray[i+6];

				TopFun(A, B, 0); //0 = sprawdzenie

				tempacu = tempacu+(calcError<3>(B, gold))/150;


				float minitemp = 0;
				float p1,p2,p3;

				p1 = B[0];
				p2 = B[1];
				p3 = B[2];


				if(p1 > p2 && p1 > p3)
				{
					B[0] = 1; B[1] = 0; B[2] = 0;
				}
				if(p2 > p1 && p2 > p3)
				{
					B[1] = 1; B[2] = 0; B[0] = 0;
				}
				if(p3 > p1 && p3 > p2)
				{
					B[2] = 1; B[0] = 0; B[1] = 0;
				}



				//(condition) ? (if_true) : (if_false)
				(abs(round(B[0])) != gold[0]) ? (zlaKlasyfikacjaGrupy1++) : (dobraKlasyfikacjaGrupy1++);
				(abs(round(B[1])) != gold[1]) ? (zlaKlasyfikacjaGrupy2++) : (dobraKlasyfikacjaGrupy2++);
				(abs(round(B[2])) != gold[2]) ? (zlaKlasyfikacjaGrupy3++) : (dobraKlasyfikacjaGrupy3++);


				 string line;
				 string filename = "/home/bartek/VivadoHLS/NeuralNetworkV2/Data/Classification.csv";
				 ofstream myfile(filename, std::ios_base::app);


				  if (myfile.is_open())
				    {
				      myfile << allArray[i] << "," << allArray[i+1] << "," <<	allArray[i+2] << "," <<	allArray[i+3] << "," << abs(round(B[0])) << "," << abs(round(B[1])) << "," << abs(round(B[2]))<<endl;
				      myfile.close();
				    }
				    else cout << "Unable to open file";





				if (abs(round(B[0])) != gold[0] || abs(round(B[1])) != gold[1] || abs(round(B[2])) != gold[2])
				{
					(zlaKlasyfikacja++);
							cout << endl;
							cout << "B0:" << B[0] << endl;
							cout << "B1:" << B[1] << endl;
							cout << "B2:" << B[2] << endl;
							cout << endl;
							cout << "G0:" << gold[0] << endl;
							cout << "G1:" << gold[1] << endl;
							cout << "G2:" << gold[2] << endl;
				}
				else
				{
					(dobraKlasyfikacja++);
				}

		}

	cout << "Usredniony blad bezwzgledny (bez zaokraglen): " << tempacu << endl;

	cout << "Ilosc zlych klasyfikacji 1: " << zlaKlasyfikacjaGrupy1 << endl;
	cout << "Ilosc dobrych klasyfikacji 1: " << dobraKlasyfikacjaGrupy1 << endl;

	cout << "Ilosc zlych klasyfikacji 2: " << zlaKlasyfikacjaGrupy2 << endl;
	cout << "Ilosc dobrych klasyfikacji 2: " << dobraKlasyfikacjaGrupy2 << endl;

	cout << "Ilosc zlych klasyfikacji 3: " << zlaKlasyfikacjaGrupy3 << endl;
	cout << "Ilosc dobrych klasyfikacji 3: " << dobraKlasyfikacjaGrupy3 << endl;

	cout << "Ilosc zlych klasyfikacji: " << zlaKlasyfikacja << endl;
	cout << "Ilosc dobrych klasyfikacji: " << dobraKlasyfikacja << endl;

	float overAllAcc = (float)dobraKlasyfikacja/(float)(dobraKlasyfikacja+zlaKlasyfikacja);
 	cout << "Poprawnych odp: " << overAllAcc*100 << "%" << endl;
 	overAllAcc = (float)dobraKlasyfikacjaGrupy1/(float)(dobraKlasyfikacjaGrupy1+zlaKlasyfikacjaGrupy1);
 	cout << "Poprawnych odp grupa 1: " << overAllAcc*100 << "%" << endl;
 	overAllAcc = (float)dobraKlasyfikacjaGrupy2/(float)(dobraKlasyfikacjaGrupy2+zlaKlasyfikacjaGrupy2);
 	cout << "Poprawnych odp grupa 2: " << overAllAcc*100 << "%" << endl;
 	overAllAcc = (float)dobraKlasyfikacjaGrupy3/(float)(dobraKlasyfikacjaGrupy3+zlaKlasyfikacjaGrupy3);
 	cout << "Poprawnych odp grupa 2: " << overAllAcc*100 << "%" << endl;

return 0;
}

void xorTest(){
	srand (time(NULL));

	ioDataType A[2] = {0, 0};
	ioDataType B[1] = {0};

	dataType bufferOne[inputsize] = {0};
	dataType bufferTwo[inputsize] = {0};
	dataType total;
	int iter = 0;
	int maxiter = 0;
	int limit = 0;
	dataType maxerror = 50; //przypadkowa wysoka wartosc
	dataType gold[0];

	do {
			A[0] = rand() % 2;
			A[1] = rand() % 2;
			B[0] = (bool)A[0]^(bool)A[1];
			gold[0] = B[0];

			TopFun(A, B, 0); //0 = sprawdzenie
			total = std::fabs(B[0]-gold[0]);




			if (total <= 0.45) //Czy taki blad jest wystarczajacy na rozwiazanie problemu XOR? (W sensie po odpowiednim zaokragleniu wiadomo czy wynikiem bylo 0 czy 1)
				{
					iter++;
				}
			else
				{
				if (maxerror > total)
					{
						maxerror = total;
						cout << maxerror <<endl;
					}
				TopFun(A, gold, 1); //1 = nauka
				//cout << " Combo: " << iter << endl;
				std::cout << "act_mistake: " << total << std::endl;
				//cout << B[0] << " = " << gold[0] << endl;
				limit++;
					if (iter > maxiter)
					{
						maxiter = iter;
						cout <<" Limit: " << limit << std::endl;
						cout <<" Max Combo: " << maxiter << "total error: " << total << std::endl;
					}
					iter=0;
					if (limit > 500000)
					{
						break;
					}

				}

	} while (iter < 1000); //1000 dobrych odp pod rzad
	maxiter = iter;

	cout << "Finish" << endl;
	cout <<" Limit: " << limit << std::endl;
	cout <<" Max Combo: " << maxiter << "total error: " << total << std::endl;



};
