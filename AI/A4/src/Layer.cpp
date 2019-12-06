#include "Layer.h"

double Layer::learningRate = 0.5;

Layer::Layer()
{
	nextLayer = NULL;
	previousLayer = NULL;
}
//--
Layer::Layer(int numberOfInputs, int numberOfOutputs)
{
	for (int i = 0; i < numberOfOutputs; i++)
	{
		Neuron newNeuron(numberOfInputs);
		neurons.push_back(newNeuron);
	}

	nextLayer = NULL;
	previousLayer = NULL;
}
//--
void Layer::feedForward(vector<double>& layerInputs, vector<double>& networkOutputs)
{
	vector<double> neuronOutputs;

	setLayerInputs(layerInputs);

	for (size_t neuronIndex = 0; neuronIndex < neurons.size(); neuronIndex++)
	{
		neurons[neuronIndex].activate(layerInputs);
		neuronOutputs.push_back(neurons[neuronIndex].getActivationValue());
	}

	setLayerOutputs(neuronOutputs);
}
//--
void Layer::moveForward(vector<double>& layerInputs, vector<double>& predictedOutputs)
{
	vector<double> neuronOutputs;

	for (size_t neuronIndex = 0; neuronIndex < neurons.size(); neuronIndex++)
	{
		neurons[neuronIndex].activate(layerInputs);
		neuronOutputs.push_back(neurons[neuronIndex].getActivationValue());
	}

	if (getNextLayer() != NULL)
	{
		getNextLayer()->moveForward(neuronOutputs, predictedOutputs);
	}
	else 
	{
		predictedOutputs = neuronOutputs;
	}
}
//--
void Layer::backPropagate(vector<double>& errors)
{
	vector<double> newErrors(getLayerInputs().size());
	for (size_t i = 0; i < getLayerInputs().size(); i++)
	{
		newErrors[i] = 0.0;
	}

	vector<double> inputs = getLayerInputs();
	inputs.insert(inputs.begin(), 1.0);

	for (size_t neuronIndex = 0; neuronIndex < neurons.size(); neuronIndex++)
	{
		neurons[neuronIndex].calculateError(errors[neuronIndex]);

		vector<double> weights = neurons[neuronIndex].getWeights();

		for (size_t weightIndex = 1; weightIndex < weights.size(); weightIndex++)
		{
			newErrors[weightIndex - 1] += (neurons[neuronIndex].getError() * weights[weightIndex]);
		}

		for (size_t weightIndex = 0; weightIndex < weights.size(); weightIndex++)
		{
			weights[weightIndex] = weights[weightIndex] + (getLearningRate() * neurons[neuronIndex].getError() * inputs[weightIndex]);
		}

		neurons[neuronIndex].setWeights(weights);
	}

	getPreviousLayer()->backPropagate(newErrors);
}
//--
void Layer::setLayerInputs(vector<double>& inputs)
{
	layerInputs.clear();
	layerInputs.insert(layerInputs.end(), inputs.begin(), inputs.end());
}
//--
vector<double> Layer::getLayerInputs()
{
	return layerInputs;
}
//--
void Layer::setLayerOutputs(vector<double>& outputs)
{
	layerOutputs.clear();
	layerOutputs.insert(layerOutputs.end(), outputs.begin(), outputs.end());
}
//--
vector<double> Layer::getLayerOutputs()
{
	return layerOutputs;
}
//--
void Layer::setNextLayer(Layer* nl)
{
	nextLayer = nl;
	nextLayer->setPreviousLayer(this);
}
//--
void Layer::setPreviousLayer(Layer* pl)
{
	previousLayer = pl;
}
//--
Layer* Layer::getNextLayer()
{
	return nextLayer;
}
//--
Layer* Layer::getPreviousLayer()
{
	return previousLayer;
}
//--
double Layer::getLearningRate()
{
	return learningRate;
}
//--
void Layer::setLearningRate(double lr)
{
	learningRate = lr;
}