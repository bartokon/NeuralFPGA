#include <iostream>

#ifndef _TopSynthFunction_h_
#define _TopSynthFunction_h_
#include "TopSynthFunction.h"
#endif

using namespace std;
#include <stdlib.h>     /* srand, rand */
#include <time.h>

#ifndef __SYNTHESIS__
#define __SYNTHESIS__
#endif

template <int arrsize> //Unused
dataType calculateErrorr(dataType resultglob[arrsize], ioDataType targetglob[arrsize])
	{
		dataType totalErrorr = 0;
		dataType result[arrsize];
		dataType target[arrsize];


		for(int i = 0; i < arrsize; i++)
		{
			result[i] = resultglob[i];
			target[i] = (dataType)targetglob[i];
		}

		for (int i = 0; i < arrsize; i++)
		{
				totalErrorr = totalErrorr +  ((target[i] - result[i])*(target[i] - result[i]))/2;
		}
		return totalErrorr;
	};



int main(){
	srand (time(NULL));


	ap_uint<2> instruction = 1;

	ioDataType A[2] = {0, 0};
	ioDataType B[1] = {0};


	dataType bufferOne[inputsize] = {0};
	dataType bufferTwo[inputsize] = {0};
	dataType outputErrorDerivative[2] = {0};
	dataType total;
	int iter = 0;
	int maxiter = 0;
	int limit = 0;
	dataType maxerror = 50;
	dataType gold[0];

	do {
			A[0] = rand() % 2;
			A[1] = rand() % 2;
			B[0] = (bool)A[0]^(bool)A[1];
			gold[0] = B[0];

			TopFun(A, B, 0); //0 = sprawdzenie
			total = abs(B[0]-gold[0]);




			if (total <= 0.45) //Czy taki blad jest wystarczajacy na rozwiazanie problemu XOR? (W sensie po odpowiednim zaokragleniu wiadomo czy wynikiem bylo 0 czy 1)
				{
					iter++;
				}
			else
				{
				if (maxerror >= total)
					{
						maxerror = total;
						cout << maxerror <<endl;
					}
				TopFun(A, gold, 1); //1 = nauka
				//cout << " Combo: " << iter << endl;
				//std::cout << "act_mistake: " << total << std::endl;
				//cout << B[0] << " = " << gold[0] << endl;
				limit++;
					if (iter >= maxiter)
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


return 0;
}

