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

static float temp[16][5];

//	{ 1, 3, -1 }, //neuron one w1 w2 w3 w4 w5
//	{ 5, 8, 1 },  //neuron two w1 w2 w3 w4 w5
float FirstgetBiasBuffer[8][5] = {0};
float SecondgetBiasBuffer[3][9] = {0};
float hiddenLayerBiasBuffer[8][9] = {0};

void TopFun(ioDataType inputData[inputsize], ioDataType outputData[outputsize], int instruction){

	static MOJNN::Layer<dataType, 4, 8, MOJNN::sigmoid> firstLayer;
	static MOJNN::Layer<dataType, 8, 3, MOJNN::sigmoid> secondLayer;
	static MOJNN::Layer<dataType, 8, 8, MOJNN::sigmoid> hiddenLayer;

	dataType bufferOne[inputsize] = {0};
	dataType bufferTwo[inputsize] = {0};
	dataType outputErrorDerivative[3] = {0};
	static bool isInit = false;

	if (isInit == false)
	{
		MOJNN::randomBias<dataType, 8, 5>(FirstgetBiasBuffer);
		MOJNN::randomBias<dataType, 3, 9>(SecondgetBiasBuffer);
		MOJNN::randomBias<dataType, 8, 9>(hiddenLayerBiasBuffer);

		firstLayer.layersSetBiases(FirstgetBiasBuffer);
		secondLayer.layersSetBiases(SecondgetBiasBuffer);
		hiddenLayer.layersSetBiases(hiddenLayerBiasBuffer);
		isInit = true;
	}


	//Load input Data to buffers
	for (int i = 0; i < inputsize; i++)
	{
		bufferOne[i]=inputData[i];
	}

	//Start Propagation
	firstLayer.layerPropagate(bufferOne, bufferTwo);
	hiddenLayer.layerPropagate(bufferTwo, bufferOne);
	secondLayer.layerPropagate(bufferOne, bufferTwo);

	//Check if backpropagation is enabled
	if (instruction == 1)
	{
		MOJNN::BackPropagate<dataType, 8, 3, MOJNN::sigmoid>(outputData, &secondLayer);
		MOJNN::BackPropagate<dataType, 8, 8, MOJNN::sigmoid>(&hiddenLayer);
		MOJNN::BackPropagate<dataType, 4, 8, MOJNN::sigmoid>(&firstLayer);
	}



	if (instruction == 0)
	{
		//Send data back to user
		for (int i = 0; i < 3; i++) //3 cos znaczy!
		{
			outputData[i]=bufferTwo[i];
		}
	}


};


