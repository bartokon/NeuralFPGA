#ifndef _iostream_
#define _iostream_
#include <iostream>
#endif

#ifndef _math_h_
#define _math_h_
#include <math.h>
#endif

#include "TopSynthFunction.h"
#include <stdint.h>

namespace MOJNN
{



enum activationFunctions {
	multiplication, // derivative: x
	relu,
	sigmoid, // derivative: (1/(1+exp(-x))) * (1-(1/(1+exp(-x))))
};

//Shared Variables
dataType tempBiaes[20+1] = {0}; //Max amout of neurons +1
dataType learningRate = 0.01;
dataType newWeight;
static dataType propagateSum;


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

		};
	/*
	 * updates biases of an neuron. Amount of biases is based on number of inputs.
	 */
		void setBias(neuronDataType newbiasArray[inputs])
		{
			for (int i = 0; i <= inputs; i++)
			{
				this->bias[i] = newbiasArray[i];
			}
		};

	/*
	 * Gets actual biases of neurons to an array
	*/
		void getBias(neuronDataType outbiasArray[inputs])
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

			case relu:
				if (this->sum < 0)
				{
					actValue = 0;
				}
				else
				{
					actValue = this->sum*1; //for future add extra bias
				}

			break;

			case sigmoid:
				actValue = 1/(1+exp(-this->sum));
			break;


			default:
				#ifndef __SYNTHESIS__
				std::cout << "ERROR activationValue default: " << this->sum << std::endl;
				#endif
			break;
			};

		};




	};

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
		dataType returnVal = 0.0;
		switch (activationFunction)
					{

					case MOJNN::multiplication:



					break;

					case MOJNN::relu:
						if (value > 0)
						{
							returnVal = 1;
						}
						else
						{
							returnVal = 0;
						}



					break;

					case MOJNN::sigmoid:
						returnVal = value*(1-value);

					break;


					default:
						#ifndef __SYNTHESIS__
						std::cout << "activationValue default" << std::endl;
						#endif
					break;
					};

		return returnVal;
	};


//Dobre sprawdzone
template<
	class outputLayerDataType, int outputLayerNumberOfInputs, int outputLayerNumberOfNeurons, MOJNN::activationFunctions outputLayerActivationFunction>
	void BackPropagate(dataType target[outputLayerNumberOfNeurons],
			MOJNN::Layer <dataType, outputLayerNumberOfInputs, outputLayerNumberOfNeurons, outputLayerActivationFunction> *outputLayer)
	{
label0:;

		dataType outputErrorDerivative[outputLayerNumberOfNeurons];
		propagateSum = 0;
		dataType tempSum = 0;

		#ifndef __SYNTHESIS__
			dataType totalError = 0;;
		#endif
		for (int n = 0; n < outputLayerNumberOfNeurons; n++)
			{
					#ifndef __SYNTHESIS__
						totalError = totalError +  ((target[n] - outputLayer->neuronLayer[n].actValue)*(target[n] - outputLayer->neuronLayer[n].actValue))/2;
					#endif
					outputErrorDerivative[n] = outputLayer->neuronLayer[n].actValue-target[n];
			}
		#ifndef __SYNTHESIS__
						//std::cout<<"Total Loss: " << totalError << std::endl;
		#endif

		for (int n = 0; n < outputLayerNumberOfNeurons; n++)
		{
			tempSum = outputErrorDerivative[n] * getDerivative<dataType>(outputLayer->neuronLayer[n].actValue, outputLayer->activation);
			for (int b = 0; b < outputLayerNumberOfInputs; b++)
			{
				propagateSum = propagateSum + tempSum * outputLayer->neuronLayer[n].bias[b];
				outputLayer->neuronLayer[n].bias[b] = outputLayer->neuronLayer[n].bias[b] - (learningRate * tempSum) * outputLayer->neuronLayer[n].input[b];
			}
			outputLayer->neuronLayer[n].bias[outputLayerNumberOfInputs] = outputLayer->neuronLayer[n].bias[outputLayerNumberOfInputs] - (learningRate*tempSum);
		}

	};

template<class inputLayerDataType, int inputLayerNumberOfInputs, int inputLayerNumberOfNeurons, MOJNN::activationFunctions inputLayerActivationFunction>
void BackPropagate(MOJNN::Layer <inputLayerDataType, inputLayerNumberOfInputs, inputLayerNumberOfNeurons, inputLayerActivationFunction> *inputLayer)
	{
	label1:;

		dataType tempSum = 0;
		for(int n = 0; n < inputLayerNumberOfNeurons; n++)
		{
			tempSum = tempSum * getDerivative(inputLayer->neuronLayer[n].actValue, inputLayer->activation);
			for(int b = 0; b < inputLayerNumberOfInputs; b++)
			{
				propagateSum = propagateSum + tempSum * inputLayer->neuronLayer[n].bias[b];
				inputLayer->neuronLayer[n].bias[b] = inputLayer->neuronLayer[n].bias[b] - (learningRate * propagateSum) * inputLayer->neuronLayer[n].input[b];
			}

			inputLayer->neuronLayer[n].bias[inputLayerNumberOfInputs] = inputLayer->neuronLayer[n].bias[inputLayerNumberOfInputs] - (learningRate * propagateSum); //Bias update
			std::cout << "Dupa";
		}

	};




/* The state array must be initialized to not be all zero in the first four words */
uint32_t xorwow()
{
	static uint32_t a = 1024, b = 64, c = 128, d = 512;
	static uint32_t counter = 1;

	/* Algorithm "xorwow" from p. 5 of Marsaglia, "Xorshift RNGs" */
	uint32_t t = d;

	uint32_t const s = a;
	d = c;
	c = b;
	b = s;

	t ^= t >> 2;
	t ^= t << 1;
	t ^= s ^ (s << 4);
	a = t;

	counter += 362437;
	return (t + counter);
}

template <class dataType, int rows, int columns>
void randomBias(dataType inputArray[rows][columns])
{
	for(int row = 0; row < rows; row ++)
		{
			for(int column = 0; column < columns; column++)
			{
				dataType temp;
				do
				{
					temp = (dataType)xorwow();
				}
				while (temp == 0);
				temp = temp/4294967296;
				std::cout << "Temp is: " << temp << std::endl;
				inputArray[row][column] = temp;
			}
		}
};

};
