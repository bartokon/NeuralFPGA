#include <iostream>
#include <math.h>

#define inputsize 2
#define neuronamout 2
#define outputsize 2

typedef float dataType;
//typedef float dataType;
namespace MOJNN
{

/*
 * activation functions
 */



enum activationFunctions {
	multiplication, // derivative: x
	hyperbolicTangent, // derivative: 1/pow(cosh(x),2)
	sigmoid, // derivative: (1/(1+exp(-x))) * (1-(1/(1+exp(-x))))
};

dataType FirstgetBiasBuffer[neuronamout][inputsize + 1] = {
		{ 0.15, 0.20, 0.35 }, //neuron one w1 w2 w3 w4 w5
		{ 0.25, 0.30, 0.35 }, //neuron two w1 w2 w3 w4 w5
		};

dataType SecondgetBiasBuffer[neuronamout][neuronamout + 1] = {
		{ 0.40, 0.45, 0.60 }, //neuron one w1 w2 w3 w4 w5
		{ 0.50, 0.55, 0.60 }, //neuron one w1 w2 w3 w4 w5
		};






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
	 *
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
};
