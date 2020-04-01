#include "Neural.h"
#include "TopSynthFunction.h"

#define inputsize 5
#define neuronamout 2

void TopFun(dataType inputData[inputsize])
{
	dataType bufferOne[inputsize] = {0};
	dataType bufferTwo[inputsize] = {0};

	for (int i = 0; i < inputsize; i++)
	{
		bufferOne[i] = inputData[i];
	}


//Creating memory interfaces and bias uploads

	Layer<dataType, neuronamout, inputsize, sigmoid> firstLayer;
	Layer<dataType, neuronamout-1, neuronamout, sigmoid> secondLayer;

	dataType FirstgetBiasBuffer[neuronamout][inputsize];
	dataType SecondgetBiasBuffer[neuronamout-1][neuronamout];

	dataType getBiasBuffer [2][2] = {
			{FirstgetBiasBuffer[neuronamout][inputsize], sigmoid},
			{SecondgetBiasBuffer[neuronamout-1][neuronamout], sigmoid}
	};

//!@!

	firstLayer.layerGetInputValues(bufferOne);
	firstLayer.layerPropagate(bufferTwo);

	secondLayer.layerGetInputValues(bufferTwo);
	secondLayer.layerPropagate(bufferOne);

	dataType output = bufferOne[0];
	dataType targetVal = 0;

	dataType error = pow((output-targetVal), 2) /2;

	#ifndef __SYNTHESIS__
		std::cout << "Output: " << bufferOne[0] << std::endl;
		std::cout << "SquaredError: " << error << std::endl;
	#endif



	firstLayer.layersGetBiases(FirstgetBiasBuffer);
	secondLayer.layersGetBiases(SecondgetBiasBuffer);

	//aktualizacja wag

	//aktualizacja wag


	firstLayer.layersSetBiases(FirstgetBiasBuffer);
	secondLayer.layersSetBiases(SecondgetBiasBuffer);

};



