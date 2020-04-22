#ifndef _iostream_
#define _iostream_
#include <iostream>
#endif

#ifndef _limits_
#define _limits_
#include <limits>
#endif

#ifndef _neural_h_
#define _neural_h_
#include "Neural.h"
#endif

#ifndef _TopSynthFunction_h_
#define _TopSynthFunction_h_
#include "TopSynthFunction.h"
#endif


void TopFun(ioDataType inputData[inputsize], ioDataType outputData[outputsize], ap_uint<2> instruction){

	static MOJNN::Layer<dataType, 2, 2, MOJNN::hyperbolicTangent> firstLayer;
	static MOJNN::Layer<dataType, 2, 2, MOJNN::hyperbolicTangent> secondLayer;
	dataType bufferOne[inputsize] = {0};
	dataType bufferTwo[inputsize] = {0};
	dataType outputErrorDerivative[2] = {0};
	static bool isInit = false;

	if (isInit == false)
	{
		firstLayer.layersSetBiases(MOJNN::FirstgetBiasBuffer);
		secondLayer.layersSetBiases(MOJNN::SecondgetBiasBuffer);
		isInit = true;
	}

	//Load input Data to buffers
	for (int i = 0; i < inputsize; i++)
	{
		bufferOne[i]=inputData[i];
	};

	//Start Propagation
	firstLayer.layerPropagate(bufferOne, bufferTwo);
	secondLayer.layerPropagate(bufferTwo, bufferOne);

	//Check if backpropagation is enabled
	if (instruction == 1)
	{
		MOJNN::calculateError<1>(bufferOne, outputData, outputErrorDerivative);
		/*Odwrotna kolejnosc podawanych funkcji*/
		MOJNN::BackPropagate<
			dataType, 2, 2, MOJNN::hyperbolicTangent,
			dataType, 2, 2, MOJNN::hyperbolicTangent>(outputErrorDerivative, &secondLayer, &firstLayer);
	}

	if (instruction == 0)
	{
		//Send data back to user
		for (int i = 0; i < outputsize; i++)
		{
			outputData[i]=bufferOne[i];
		};
	}


};


