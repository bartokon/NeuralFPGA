#ifndef _iostream_
#define _iostream_
#include <iostream>
#endif

#ifndef _math_h_
#define _math_h_
#include <math.h>
#endif

#include "TopSynthFunction.h"

namespace MOJNN
{



enum activationFunctions {
	multiplication, // derivative: x
	hyperbolicTangent, // derivative: 1/pow(cosh(x),2)
	sigmoid, // derivative: (1/(1+exp(-x))) * (1-(1/(1+exp(-x))))
};

//Startup biases for testing

dataType FirstgetBiasBuffer[neuronamout][inputsize + 1] = {
		{ 1, 3, -1 }, //neuron one w1 w2 w3 w4 w5
		{ 5, 8, 1 }, //neuron two w1 w2 w3 w4 w5
		};

dataType SecondgetBiasBuffer[neuronamout][neuronamout + 1] = {
		{ 5, 2, 1 }, //neuron one w1 w2 w3 w4 w5
		{ 7, 6, -5 }, //neuron one w1 w2 w3 w4 w5
		};

//Shared Variables
dataType tempBiaes[neuronamout+1] = {0};
dataType learningRate = 0.01;
dataType newWeight;
dataType tempSum;




/*****************************************************************************************************/
	template<class neuronDataType, int inputs, activationFunctions activation>
	class Neuron
	{
	public:
		neuronDataType sum;
		neuronDataType actValue;
		neuronDataType input[inputs];
		neuronDataType bias[inputs+1];

		static const activationFunctions activationFunction = activation;
		Neuron()
		{
			#ifndef __SYNTHESIS__
			//std::cout << "Hello from Neuron " << std::endl;
			#endif
		};
	/*
	 * updates biases of an neuron. Amount of biases is based on number of inputs.
	 */
		void setBias(neuronDataType newbiasArray[inputs])
		{
			for (int i = 0; i <= inputs; i++)
			{
			#ifndef __SYNTHESIS__
			//	std::cout << "Neuron bias changed: " << this->bias[i] << " -> ";
			#endif

				this->bias[i] = newbiasArray[i];

			#ifndef __SYNTHESIS__
				//std::cout << this->bias[i] << std::endl;
			#endif

			}
		};

	/*
	 * Gets actual biases of neurons to an array
	*/	void getBias(neuronDataType outbiasArray[inputs])
			{
				for (int i = 0; i <= inputs; i++)
				{
					outbiasArray[i] = this->bias[i];
				}
			};


	/*
	 * Updates input values on each neuron in a layer.
	 */


		void getInputvalues(neuronDataType newInputs[inputs])
		{
			for (int i = 0; i < inputs; i++)
			{
				#ifndef __SYNTHESIS__
				//std::cout << "Neuron input Data changed: " << this->input[i] << " -> ";
				#endif

				this->input[i] = newInputs[i];

				#ifndef __SYNTHESIS__
				//std::cout << this->input[i] << std::endl;
				#endif
			};

		};
	/*
	 * Propagate function takes all inputs and sums them, then it activates "activateFunction()" and do activation
	 * operation based on activationFunction type that is passed by template arguments in layer creation.
	 */
		neuronDataType propagate()
		{
			this->sum = 0;
			for (int i = 0; i < inputs; i++)
			{
				this->sum = this->sum + input[i] * bias[i];

				#ifndef __SYNTHESIS__
				//std::cout << "Input: " << input[i] << " Bias: " << bias[i]<< std::endl;
				//std::cout << "Neuron new sum is: " << this->sum << std::endl;
				#endif
			};

			this->sum = this->sum + bias[inputs];
			activateFunction();

			return actValue;
		};
	/*
	 * Here is implemented activationFunction for neuron.
	 * You can add your own activation functions for each layer like:
	 * create name for your activation function in "activationFunctions" enum
	 * and add option to the switch statement for example:
	 * case myownfunction:
	 * 	dataType x = this->sum;
	 * 	dataType output = sin(x);
	 * 	this->sum = output;
	 * break;
	 * You will need to do the same in getderivative function
	*/
		void activateFunction()
		{

			switch (this->activationFunction)
			{

			case multiplication:
				actValue = this->sum*1; //for future add extra bias

				#ifndef __SYNTHESIS__
				//std::cout << "activationValue multiplication: " << this->sum << std::endl;
				#endif
			break;

			case hyperbolicTangent:
				actValue = tanh(this->sum);

				#ifndef __SYNTHESIS__
				//std::cout << "activationValue tanh: " << this->sum << std::endl;
				#endif
			break;

			case sigmoid:
				actValue = 1/(1+exp(-this->sum));

				#ifndef __SYNTHESIS__
				//std::cout << "activationValue sigmoid: " << this->sum << std::endl;
				#endif
			break;


			default:
				#ifndef __SYNTHESIS__
				//std::cout << "activationValue default: " << this->sum << std::endl;
				#endif
			break;
			};

		};




	};
	/*****************************************************************************************************/

	/*****************************************************************************************************/
	template<class dataType, int nbPrevLayerNeurons,
					int numberOfNeurons, activationFunctions activationFunction>
	class Layer
	{
	public:
		Neuron<dataType, nbPrevLayerNeurons, activationFunction>  neuronLayer[numberOfNeurons];
		static const activationFunctions activation = activationFunction;

		void layerPropagate(dataType inputData[nbPrevLayerNeurons], dataType outputData[numberOfNeurons])
		{
			//Podobno takie rozbijanie petli ulatwia synteze (jeszcze do weryfikacji)
			for (int i = 0; i < numberOfNeurons; i++)
			{
				this->neuronLayer[i].getInputvalues(inputData);
			};

			for (int i = 0; i < numberOfNeurons; i++)
			{
			   this->neuronLayer[i].propagate();
			};

			for (int i = 0; i < numberOfNeurons; i++)
			{
				outputData[i] = this->neuronLayer[i].actValue;
				#ifndef __SYNTHESIS__
			//	std::cout << "LayerOutputBuffer[" << i << "] -> " << outputData[i] << std::endl;
				#endif
			};
		};

		void layersGetBiases(dataType outputData[numberOfNeurons][nbPrevLayerNeurons+1])
		{
			for (int i = 0; i < numberOfNeurons; i++)
			{
				this->neuronLayer[i].getBias(outputData[i]);
			};
		};

		void layersSetBiases(dataType inputData[numberOfNeurons][nbPrevLayerNeurons+1])
		{
			for (int i = 0; i < numberOfNeurons; i++)
			{
				this->neuronLayer[i].setBias(inputData[i]);

			};
		};


	};
	/*****************************************************************************************************/

	template <class dataType>
	dataType getDerivative(dataType value, MOJNN::activationFunctions activationFunction)
	{
		dataType returnVal;
		switch (activationFunction)
					{

					case MOJNN::multiplication:



					break;

					case MOJNN::hyperbolicTangent:
						returnVal = 1/(cosh(value)*cosh(value));


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
void calculateError(dataType resultglob[arrsize], ioDataType targetglob[arrsize], dataType outputErrorDerivative[arrsize])
	{
		#ifndef __SYNTHESIS__
			dataType totalError = 0;;
		#endif

		dataType result[arrsize];
		dataType target[arrsize];


		for(int i = 0; i < arrsize; i++)
		{
			result[i] = resultglob[i];
			target[i] = (dataType)targetglob[i];
		}

		for (int i = 0; i < arrsize; i++)
		{
			#ifndef __SYNTHESIS__
				totalError = totalError +  ((target[i] - result[i])*(target[i] - result[i]))/2;
			#endif

			outputErrorDerivative[i] = result[i]-target[i];
		}

		#ifndef __SYNTHESIS__
			//	std::cout << std::endl << "Total Err: " << totalError << std::endl;
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

		for (int n = 0; n < numberOfNeurons; n++)
		{
			ostatniaWarstwa->neuronLayer[n].getBias(tempBiaes); //stare biasy aktualnego neuronu
			for (int b = 0; b <= nbPrevLayerNeurons; b++) //dodalem rownasie
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

		for (int i = 0; i <= numberOfNeurons; i++) //dodalem rownasie
		{
			newWeight = tempSum * warstwa1->neuronLayer[j].input[i];
			tempBiaes[i] = tempBiaes[i] - newWeight;
		}
		warstwa1->neuronLayer[j].setBias(tempBiaes);

	}

	BackPropagate<dataType, nbPrevLayerNeurons, numberOfNeurons, activationFunction>(outputErrorDerivative, ostatniaWarstwa);
 /* Propagacja dwu wartstwowa polega na obliczeniu nowych wag do warstwy 2 a nastepnie do warstwy 1 po to aby nie pamiętać starych wag po aktualizacji*/

};

};
