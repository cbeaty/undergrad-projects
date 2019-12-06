#pragma once
#include "Layer.h"
#include "Neuron.h"
#include <vector>

using namespace std;

class OutputLayer : public Layer
{
public:
	OutputLayer(int numberOfInputs, int numberOfOutputs);	
	void feedForward(vector<double>& layerInputs, vector<double>& networkOutputs);
};

