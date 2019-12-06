#pragma once
#include <vector>
#include "Layer.h"

using namespace std;

class NeuralNetwork
{
public:
	NeuralNetwork(vector<int>& architecture, vector<vector<double>>& trainingData, vector<vector<double>>& labelData, double lr, int nti);
	~NeuralNetwork();
	vector<double> predict(vector<double>& input);

private:
	Layer* firstLayer;
	double learningRate;
	int numberOfTrainingIterations;

	void train(vector<vector<double>>& trainingData, vector<vector<double>>& labelData);
};
