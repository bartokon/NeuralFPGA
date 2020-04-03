#include "Neural.h"
#include "TopSynthFunction.h"
#include <iostream>
using namespace std;
#define inputsize 5
#define neuronamout 2

struct Neurons {

	int inputLayer = inputsize;
	int firstLayer = neuronamout;
	int secondLayer = neuronamout-1;

};

struct Biases {

	dataType FirstgetBiasBuffer[neuronamout][inputsize] = {
				{1, 2, 3, 4, 5}, //neuron one w1 w2 w3 w4 w5
				{1, 2, 3, 4, 5}, //neuron two w1 w2 w3 w4 w5
		};

	dataType SecondgetBiasBuffer[neuronamout-1][neuronamout] = {
				{3, 3}, //neuron one w1 w2
		};

};

struct Activations {

	activationFunctions firstLayer = sigmoid;

	activationFunctions secondLayer = sigmoid;

};


void TopFun(dataType inputData[inputsize])
{
	dataType bufferOne[inputsize] = {0};
	dataType bufferTwo[inputsize] = {0};

	for (int i = 0; i < inputsize; i++)
	{
		bufferOne[i] = inputData[i];
	}


//Creating memory interfaces and bias uploads
	Biases biasMem;
	constexpr Activations activationMem;
	constexpr Neurons neuronMem;

	Layer<dataType, neuronMem.inputLayer, neuronMem.firstLayer, activationMem.firstLayer> firstLayer;
	Layer<dataType, neuronMem.firstLayer, neuronMem.secondLayer,  activationMem.secondLayer> secondLayer;

	dataType *pointerTest[2] = {
			*biasMem.FirstgetBiasBuffer,
			*biasMem.SecondgetBiasBuffer
	};

	//cout << *((*pointerTest)+1) << endl;

	firstLayer.layersSetBiases(biasMem.FirstgetBiasBuffer);
	secondLayer.layersSetBiases(biasMem.SecondgetBiasBuffer);


	firstLayer.layerGetInputValues(bufferOne);
	firstLayer.layerPropagate(bufferTwo);

	secondLayer.layerGetInputValues(bufferTwo);
	secondLayer.layerPropagate(bufferOne);

	dataType output = bufferOne[0];
	dataType targetVal = 0;

	dataType error = pow((output-targetVal), 2) /2;

	#ifndef __SYNTHESIS__
		std::cout << "Output: " << bufferOne[0] << std::endl;
		std::cout << "SquaredEr: " << error << std::endl;
	#endif


	firstLayer.layersGetBiases(biasMem.FirstgetBiasBuffer);
	secondLayer.layersGetBiases(biasMem.SecondgetBiasBuffer);

	//aktualizacja wag

	//aktualizacja wag


	firstLayer.layersSetBiases(biasMem.FirstgetBiasBuffer);
	secondLayer.layersSetBiases(biasMem.SecondgetBiasBuffer);



};



