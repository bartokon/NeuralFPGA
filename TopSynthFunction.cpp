#include <iostream>
#include <limits>

#include "TopSynthFunction.h"
#include "Neural.h"
using namespace std;

template <int arrsize>
void calculateError(dataType resultglob[arrsize], dataType targetglob[arrsize], dataType outputErrorDerivative[arrsize]);

template<
	class dataType, int nbPrevLayerNeurons, int numberOfNeurons, MOJNN::activationFunctions activationFunction>
	void BackPropagate(
			dataType outputErrorDerivative[numberOfNeurons],
			MOJNN::Layer <dataType, nbPrevLayerNeurons, numberOfNeurons, activationFunction> *ostatniaWarstwa);

template<
	class dataType, int nbPrevLayerNeurons, int numberOfNeurons, MOJNN::activationFunctions activationFunction,
	class dataType1, int nbPrevLayerNeurons1, int numberOfNeurons1, MOJNN::activationFunctions activationFunction1>
	void BackPropagate(dataType outputErrorDerivative[numberOfNeurons],
			MOJNN::Layer <dataType, nbPrevLayerNeurons, numberOfNeurons, activationFunction> *ostatniaWarstwa,
			MOJNN::Layer <dataType1, nbPrevLayerNeurons1, numberOfNeurons1, activationFunction1> *warstwa1);

//Moga być globalne
	dataType tempBiaes[10] = {0};
	dataType newWeight;
	dataType learningRate = 0.5;
	dataType tempSum;

void TopFun(dataType inputData[inputsize], dataType outputData[outputsize]){
	cout.precision(8);

	MOJNN::Layer<dataType, 2, 2, MOJNN::sigmoid> firstLayer;
	MOJNN::Layer<dataType, 2, 2, MOJNN::sigmoid> secondLayer;

	dataType target[2] = {0.01, 0.99};
	dataType bufferOne[inputsize] = {0};
	dataType bufferTwo[inputsize] = {0};

	firstLayer.layersSetBiases(MOJNN::FirstgetBiasBuffer);
	secondLayer.layersSetBiases(MOJNN::SecondgetBiasBuffer);

TopFun_label0:for (int x = 0; x < 10000; x++)
{

	for (int i = 0; i < inputsize; i++){
		bufferOne[i]=inputData[i];
	 };

	//Creating memory interfaces and bias uploads


	firstLayer.layerPropagate(bufferOne, bufferTwo);
	secondLayer.layerPropagate(bufferTwo, bufferOne);

	cout << "OutputData 1: " << bufferOne[0] << endl;
	cout << "OutputData 2: " << bufferOne[1] << endl;

	dataType golden[2] =
	{
		0.01, 0.99,
	};

	dataType outputErrorDerivative[2] = {0};
	calculateError<2>(bufferOne, golden, outputErrorDerivative);
	BackPropagate<
			dataType, 2, 2, MOJNN::sigmoid,
			dataType, 2, 2, MOJNN::sigmoid>(outputErrorDerivative, &secondLayer, &firstLayer);


};

	outputData[0] = bufferOne[0];
	outputData[1] = bufferOne[1];
};
template <class dataType>
dataType getDerivative(dataType value, MOJNN::activationFunctions activationFunction)
{
	dataType returnVal;
	switch (activationFunction)
				{

				case MOJNN::multiplication:



				break;

				case MOJNN::hyperbolicTangent:



				break;

				case MOJNN::sigmoid:
					returnVal = value*(1-value);


				break;


				default:
					#ifndef __SYNTHESIS__
					//std::cout << "activationValue default: " << this->sum << std::endl;
					#endif
				break;
				};

	return returnVal;
};



template <int arrsize>
void calculateError(dataType resultglob[arrsize], dataType targetglob[arrsize], dataType outputErrorDerivative[arrsize])
	{
		#ifndef __SYNTHESIS__
			dataType totalError = 0;;
		#endif

		dataType result[arrsize];
		dataType target[arrsize];


		for(int i = 0; i < arrsize; i++)
		{
			result[i] = resultglob[i];
			target[i] = targetglob[i];
		}

		for (int i = 0; i < arrsize; i++)
		{
			#ifndef __SYNTHESIS__
				totalError = totalError +  ((target[i] - result[i])*(target[i] - result[i]))/2;
			#endif

			outputErrorDerivative[i] = result[i]-target[i];
		}

		#ifndef __SYNTHESIS__
				std::cout << std::endl << "Total Err: " << totalError << std::endl;
		#endif


		//neuron output

	};

//Dobre sprawdzone
template<
	class dataType, int nbPrevLayerNeurons, int numberOfNeurons, MOJNN::activationFunctions activationFunction>
	void BackPropagate(dataType outputErrorDerivative[numberOfNeurons],
			MOJNN::Layer <dataType, nbPrevLayerNeurons, numberOfNeurons, activationFunction> *ostatniaWarstwa)
	{
label0:;
/*
		dataType tempBiaes[nbPrevLayerNeurons] = {0}; //bez zmiany biasu
		dataType learningRate = 0.5;
*/

		for (int n = 0; n < numberOfNeurons; n++)
		{
			ostatniaWarstwa->neuronLayer[n].getBias(tempBiaes); //stare biasy aktualnego neuronu
			for (int b = 0; b < nbPrevLayerNeurons; b++)
					{
						//tempBiaes[b] = tempBiaes[b]-learningRate*outputErrorDerivative[n] * ostatniaWarstwa->neuronLayer[n].actValue*(1-ostatniaWarstwa->neuronLayer[n].actValue) *ostatniaWarstwa->neuronLayer[b].input[b];
						tempBiaes[b] = tempBiaes[b]-learningRate*outputErrorDerivative[n] * getDerivative<dataType>(ostatniaWarstwa->neuronLayer[n].actValue, activationFunction) *ostatniaWarstwa->neuronLayer[b].input[b];


						#ifndef __SYNTHESIS__
						//std::cout << "Neuron " << n << " bias " << b << " Nowa waga " << tempBiaes[b] << std::endl;
						#endif

					}
			ostatniaWarstwa->neuronLayer[n].setBias(tempBiaes); //nowe biasy aktualnego neuronu
		}


	};

template<
	class dataType, int nbPrevLayerNeurons, int numberOfNeurons, MOJNN::activationFunctions activationFunction,
	class dataType1, int nbPrevLayerNeurons1, int numberOfNeurons1, MOJNN::activationFunctions activationFunction1>
	void BackPropagate(dataType outputErrorDerivative[numberOfNeurons],
			MOJNN::Layer <dataType, nbPrevLayerNeurons, numberOfNeurons, activationFunction> *ostatniaWarstwa,
			MOJNN::Layer <dataType1, nbPrevLayerNeurons1, numberOfNeurons1, activationFunction1> *warstwa1)
{
label1:;
/*
	//Moga być globalne
	dataType tempBiaes[nbPrevLayerNeurons] = {0};
	dataType newWeight;
	dataType learningRate = 0.5;
	dataType tempSum;
*/


	for (int j = 0; j < numberOfNeurons1; j++)
	{
		tempSum = 0;

		for (int i = 0; i < numberOfNeurons; i++)
		{
				ostatniaWarstwa->neuronLayer[i].getBias(tempBiaes);
				tempSum = tempSum + outputErrorDerivative[i]*getDerivative<dataType>(ostatniaWarstwa->neuronLayer[i].actValue, activationFunction)*tempBiaes[0];
		}

		tempSum = tempSum * getDerivative<dataType>(warstwa1->neuronLayer[j].actValue, activationFunction1);
		tempSum = tempSum * learningRate;
		warstwa1->neuronLayer[j].getBias(tempBiaes);

		for (int i = 0; i < numberOfNeurons; i++)
		{

			newWeight = tempSum * warstwa1->neuronLayer[j].input[i];
			tempBiaes[i] = tempBiaes[i] - newWeight;


		}
		warstwa1->neuronLayer[j].setBias(tempBiaes);

	}






/*
	//W1 I W2
	tempSum = 0;
	ostatniaWarstwa->neuronLayer[0].getBias(tempBiaes);
	tempSum = tempSum + outputErrorDerivative[0]*getDerivative<dataType>(ostatniaWarstwa->neuronLayer[0].actValue, activationFunction)*tempBiaes[0];

	ostatniaWarstwa->neuronLayer[1].getBias(tempBiaes);
	tempSum = tempSum + outputErrorDerivative[1]*getDerivative<dataType>(ostatniaWarstwa->neuronLayer[1].actValue, activationFunction)*tempBiaes[0];

	tempSum = tempSum * getDerivative<dataType>(warstwa1->neuronLayer[0].actValue, activationFunction1);

	tempSum = tempSum * learningRate;

	warstwa1->neuronLayer[0].getBias(tempBiaes);

	newWeight = tempSum * warstwa1->neuronLayer[0].input[0];
	tempBiaes[0] = tempBiaes[0] - newWeight;

	newWeight = tempSum * warstwa1->neuronLayer[0].input[1];
	tempBiaes[1] = tempBiaes[1] - newWeight;

	warstwa1->neuronLayer[0].setBias(tempBiaes);


//W3 I W4
	tempSum = 0;

	ostatniaWarstwa->neuronLayer[0].getBias(tempBiaes);
	tempSum = tempSum + outputErrorDerivative[0]*getDerivative<dataType>(ostatniaWarstwa->neuronLayer[0].actValue, activationFunction1)*tempBiaes[1];

	ostatniaWarstwa->neuronLayer[1].getBias(tempBiaes);
	tempSum = tempSum + outputErrorDerivative[1]*getDerivative<dataType>(ostatniaWarstwa->neuronLayer[1].actValue, activationFunction1)*tempBiaes[1];

	tempSum = learningRate * tempSum * getDerivative<dataType>(warstwa1->neuronLayer[1].actValue, activationFunction1);

	warstwa1->neuronLayer[1].getBias(tempBiaes);

	newWeight = tempSum * warstwa1->neuronLayer[1].input[0];
	tempBiaes[0] = tempBiaes[0] - newWeight;

	newWeight = tempSum * warstwa1->neuronLayer[1].input[1];
	tempBiaes[1] = tempBiaes[1] - newWeight;

	warstwa1->neuronLayer[1].setBias(tempBiaes);


*/


	BackPropagate<dataType, nbPrevLayerNeurons, numberOfNeurons, activationFunction>(outputErrorDerivative, ostatniaWarstwa);


};
