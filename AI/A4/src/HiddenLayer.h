#pragma once
#include "Layer.h"
#include "Neuron.h"
#include <vector>

using namespace std;

class HiddenLayer : public Layer
{
public:
	HiddenLayer(int numberOfInputs, int numberOfOutputs);	
	void feedForward(vector<double>& layerInputs, vector<double>& networkOutputs);
};

