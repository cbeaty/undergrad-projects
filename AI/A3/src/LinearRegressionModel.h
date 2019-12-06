#pragma once
#include <vector>

using namespace std;

class LinearRegressionModel
{

public:
    LinearRegressionModel(vector<vector<double>> &features, vector<double> &labels, double learningRate);
    double predict(vector<double> &inputFeatures);

private:
    vector<double> w; //Vector of the weights
    double getHypothesisFunction(vector<double> x);
    void gradientDescent(vector<vector<double>> &features, vector<double> &labels, double learningRate);
};
