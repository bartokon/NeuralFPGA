#include <math.h>
#include <ap_fixed.h>

enum activationFunctions{
	multiplication,
	hyperbolicTangent,
	sigmoid,
};


/*****************************************************************************************************/
template<class neuronDataType, int inputs, int layerNumber, activationFunctions activation>
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

	void activateFunction()
	{

		switch (this->activationFunction)
		{

		case multiplication:
			this->sum = this->sum*0.5; //for future add extra bias

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
template<class dataType, int numberOfNeurons, int layerNumber,
		int nbPrevLayerNeurons, activationFunctions activationFunction>
class Layer
{
public:
	Layer()
	{
		Neuron<dataType, nbPrevLayerNeurons, layerNumber, activationFunction> neuArray[numberOfNeurons];
	};

};
/*****************************************************************************************************/


