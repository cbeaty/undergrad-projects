#include "OutputLayer.h"
#include <iostream>

using namespace std;

OutputLayer::OutputLayer(int numberOfInputs, int numberOfOutputs)
	: Layer(numberOfInputs, numberOfOutputs)
{
	//do nothing
}
//--
void OutputLayer::feedForward(vector<double>& layerInputs, vector<double>& networkOutputs)
{
	Layer::feedForward(layerInputs, networkOutputs);

	vector<double> neuronOutputs = getLayerOutputs();
	vector<double> errors;

	for (size_t i = 0; i < neuronOutputs.size(); i++)
	{
		errors.push_back(networkOutputs[i] - neuronOutputs[i]);
	}

	backPropagate(errors);
}
