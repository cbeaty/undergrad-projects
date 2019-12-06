#include "HiddenLayer.h"
#include <iostream>

using namespace std;

HiddenLayer::HiddenLayer(int numberOfInputs, int numberOfOutputs)
	: Layer(numberOfInputs, numberOfOutputs)
{
	//do nothing
}
//--
void HiddenLayer::feedForward(vector<double>& layerInputs, vector<double>& networkOutputs)
{
	Layer::feedForward(layerInputs, networkOutputs);

	vector<double> nextLayerInputs = getLayerOutputs();

	getNextLayer()->feedForward(nextLayerInputs, networkOutputs);
}
