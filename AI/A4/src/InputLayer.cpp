#include "InputLayer.h"
#include <iostream>

using namespace std;

//--
InputLayer::InputLayer(int numInputs)
	:Layer()
{
	numberOfInputs = numInputs;
}
//--
void InputLayer::feedForward(vector<double>& layerInputs, vector<double>& networkOutputs)
{
	if ((size_t)numberOfInputs == layerInputs.size())
	{
		setLayerInputs(layerInputs);
		setLayerOutputs(layerInputs);

		getNextLayer()->feedForward(layerInputs, networkOutputs);
	}
	else
	{
		string ex = "Incorrect number of input layers";
		throw ex;
	}
}
//--
void InputLayer::backPropagate(vector<double>& errors)
{
	//do nothing for back prop on input layer
}