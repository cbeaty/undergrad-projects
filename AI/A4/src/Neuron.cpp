#include "Neuron.h"
#include <iostream>
#include <string>

using namespace std;

Neuron::Neuron(int numberOfInputs)
{
	for (int i = 0; i < numberOfInputs + 1; i++)
	{
		double randWeight = getRandomWeight();
		weights.push_back(randWeight);
	}
}
//--
void Neuron::activate(vector<double>& neuronInputs)
{
	vector<double> inputs; 
	vector<double> resultOfMultiplying;
	
	inputs.push_back(1.0);
	inputs.insert(inputs.end(), neuronInputs.begin(), neuronInputs.end());

	multiplyVectors(inputs, weights, resultOfMultiplying);
	double sumOfProducts = sumVector(resultOfMultiplying);
	
	activationValue = sigmoid(sumOfProducts);
}
//--
double Neuron::getActivationValue()
{
	return activationValue;
}
//--
vector<double> Neuron::getWeights()
{
	return weights;
}
//--
void Neuron::setWeights(vector<double>& newWeights)
{
	weights.clear();
	weights.insert(weights.begin(), newWeights.begin(), newWeights.end());
}
//--
void Neuron::calculateError(double forwardError)
{
	error = forwardError * sigmoidDerivative();
}
//--
double Neuron::getError()
{
	return error;
}
//--
void Neuron::multiplyVectors(vector<double>& vec1, vector<double>& vec2, vector<double>& results)
{
	if (vec1.size() == vec2.size() && results.size() == 0)
	{
		for (size_t i = 0; i < vec1.size(); i++)
		{
			results.push_back(vec1[i] * vec2[i]);
		}
	}
	else 
	{
		string ex = "multiplyVectors(): vectors not the same size OR results not empty";
		cout << ex << endl;
		throw ex;
	}
}
//--
double Neuron::sumVector(vector<double>& vec)
{
	double sum = 0.0;

	for (size_t i = 0; i < vec.size(); i++)
	{
		sum += vec[i];
	}

	return sum;
}
//--
double Neuron::sigmoid(double value)
{
	return 1.0 / (1.0 + exp(-value));
}
//--
double Neuron::sigmoidDerivative()
{
	double value = getActivationValue();
	return value * (1.0 - value);
}
//--
double Neuron::getRandomWeight()
{
    double randDouble = double(rand()) / double(RAND_MAX);
    return -1.0 + (2 * randDouble);
}