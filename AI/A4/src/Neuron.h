#pragma once
#include <vector>
#include <cmath>

using namespace std;

class Neuron
{
public:
	Neuron(int numberOfInputs);

	void activate(vector<double>& neuronInputs);
	double getActivationValue();

	vector<double> getWeights();
	void setWeights(vector<double>& newWeights);
	
	void calculateError(double forwardError);
	double getError();

private:
	vector<double> weights;
	double activationValue;
	double error;

	double getRandomWeight();
	double sigmoid(double value);
	double sigmoidDerivative();
	void multiplyVectors(vector<double>& vec1, vector<double>& vec2, vector<double>& results);
	double sumVector(vector<double>& vec);
};