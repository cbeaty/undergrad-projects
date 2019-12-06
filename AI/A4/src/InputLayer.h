#pragma once
#include "Layer.h"

class InputLayer : public Layer
{
public: 
	InputLayer(int numInputs);
	void feedForward(vector<double>& layerInputs, vector<double>& networkOutputs);
	void backPropagate(vector<double>& errors);

private:
	int numberOfInputs;
};

