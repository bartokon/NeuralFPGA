#include "Neural.h"
#include "TopSynthFunction.h"

void TopFun(dataType inputData[1000])
{
	dataType buffer[1000] = {0};
	for (int i = 0; i < 1000; i++)
	{
		buffer[i] = inputData[i];
	}


	dataType biases[1000] = { 5 };
	dataType miniBuffer[2] = {0};
	dataType out = 69;
	//template <class neuronDataType, int inputs, int layerNumber>

	Neuron<dataType, 1, 0, sigmoid> neu11;
	Neuron<dataType, 1, 0, sigmoid> neu12;

	Neuron<dataType, 2, 1, multiplication> neu21;

	neu11.getInputvalues(buffer);
	neu12.getInputvalues(buffer);

	neu11.setBias(biases);
	neu12.setBias(biases);

	miniBuffer[0] = neu11.propagate();
	miniBuffer[1] = neu12.propagate();

#ifndef __SYNTHESIS__
		std::cout << std::endl << std::endl;
		std::cout << "Minibuffer is: " << miniBuffer[0] << miniBuffer[1] << std::endl;

#endif

	neu21.getInputvalues(miniBuffer);
	neu21.setBias(biases);

#ifndef __SYNTHESIS__
		std::cout << "Output Val: " << out << " -> ";
#endif
		out = neu21.propagate();
#ifndef __SYNTHESIS__
		std::cout << out << std::endl;
#endif



};



























	/*
	int temp[50] = {0};
	int ispointer[50] = {5};
	AtoZero(a);
	TopFunPlus(a,b, temp);
	AtoZero(ispointer);

	TopFunPlus(ispointer, b, temp);

	for(int i = 0; i < 50; i++){
		exit[i] = temp[i];
	}

	Multiplier <3647> mnozarka;
	mnozarka.changeNumber(b[a[50]]);

	if (mnozarka.returnNumber() == 1){

		for(int i = 0; i < 50; i++){
			Multiplier <214748> mnozarkaa[50];
			mnozarka.changeNumber(b[a[i]]);
			exit[i] = mnozarkaa[i].returnNumber();
				}
			}


	exit[0] = mnozarka.returnNumber();


};

void TopFunPlus(int a[50], int b[50], int exit[50])
{
	int c[50];

	for (int i = 0; i < 50; i++)
	{
		exit[i] = a[i]+b[i];
	}
};

void AtoZero(int a[50])
{
	for (int i = 0; i < 50; i++)
	{
		a[i]=0;
	}

};

*/
