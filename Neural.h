#include <hls_math.h>
#include <iostream>
/*
 * activation functions
 */

enum activationFunctions{
	multiplication, // derivative: x
	hyperbolicTangent, // derivative: 1/pow(cosh(x),2)
	sigmoid, // derivative: (1/(1+exp(-x))) * (1-(1/(1+exp(-x))))
};


/*****************************************************************************************************/
template<class neuronDataType, int inputs, activationFunctions activation>
class Neuron
{
public:
	neuronDataType sum = 0;
	neuronDataType input[inputs];
	neuronDataType bias[inputs];
	activationFunctions activationFunction = activation;
	Neuron()
	{
		#ifndef __SYNTHESIS__
		std::cout << "Hello from Neuron " << std::endl;
		#endif
	};
/*
 * updates biases of an neuron. Amount of biases is based on number of inputs.
 */
	void setBias(neuronDataType newbiasArray[inputs])
	{
		for (int i = 0; i < inputs; i++)
		{
		#ifndef __SYNTHESIS__
			std::cout << "Neuron bias changed: " << this->bias[i] << " -> ";
		#endif

			this->bias[i] = newbiasArray[i];

		#ifndef __SYNTHESIS__
			std::cout << this->bias[i] << std::endl;
		#endif

		}
	};

/*
 * Gets actual biases of neurons to an array
*/	void getBias(neuronDataType outbiasArray[inputs])
		{
			for (int i = 0; i < inputs; i++)
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
			std::cout << "Neuron input Data changed: " << this->input[i] << " -> ";
			#endif

			this->input[i] = newInputs[i];

			#ifndef __SYNTHESIS__
			std::cout << this->input[i] << std::endl;
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
			std::cout << "Input: " << input[i] << " Bias: " << bias[i]<< std::endl;
			std::cout << "Neuron new sum is: " << this->sum << std::endl;
			#endif
		};

		activateFunction();

		return this->sum;
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
			this->sum = this->sum*1; //for future add extra bias

			#ifndef __SYNTHESIS__
			std::cout << "activationValue multiplication: " << this->sum << std::endl;
			#endif
		break;

		case hyperbolicTangent:
					this->sum = tanh(this->sum);

			#ifndef __SYNTHESIS__
			std::cout << "activationValue tanh: " << this->sum << std::endl;
			#endif
		break;

		case sigmoid:
			this->sum = 1/(1+exp(-this->sum));

			#ifndef __SYNTHESIS__
			std::cout << "activationValue sigmoid: " << this->sum << std::endl;
			#endif
		break;


		default:
			#ifndef __SYNTHESIS__
			std::cout << "activationValue default: " << this->sum << std::endl;
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
	activationFunctions activation = activationFunction;
	void layerGetInputValues(dataType inputData[nbPrevLayerNeurons])
	{

		for (int i = 0; i < numberOfNeurons; i++)
		{
			this->neuronLayer[i].getInputvalues(inputData);
		};

	};

	void layerPropagate(dataType outputData[numberOfNeurons])
	{
		for (int i = 0; i < numberOfNeurons; i++)
		{
		   this->neuronLayer[i].propagate();
		};

		for (int i = 0; i < numberOfNeurons; i++)
		{
			outputData[i] = this->neuronLayer[i].sum;
			#ifndef __SYNTHESIS__
			std::cout << "LayerOutputBuffer[" << i << "] -> " << outputData[i] << std::endl;
			#endif
		};
	};

	void layersGetBiases(dataType outputData[numberOfNeurons][nbPrevLayerNeurons])
	{
		for (int i = 0; i < numberOfNeurons; i++)
		{
			this->neuronLayer[i].getBias(outputData[i]);
		};
	};

	void layersSetBiases(dataType inputData[numberOfNeurons][nbPrevLayerNeurons])
	{
		for (int i = 0; i < numberOfNeurons; i++)
		{
				this->neuronLayer[i].setBias(inputData[i]);

		};
	};


};
/*****************************************************************************************************/



