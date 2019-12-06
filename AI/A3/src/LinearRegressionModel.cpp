#include "LinearRegressionModel.h"
#include <iostream>

using namespace std;

LinearRegressionModel::LinearRegressionModel(vector<vector<double>> &features, vector<double> &labels, double learningRate)
{
    //Makes sure the user actually inputs data
    if (features.empty() || labels.empty())
    {
        throw "Inputs are empty";
    }
    //Makes sure there are the same number of features and labels
    if (features.size() != labels.size())
    {
        throw "Size of features doesn't equal size of labels";
    }
    //Used to make sure there are the same number of features (x1's and x2's for example)
    size_t size = features.at(0).size();
    for (size_t i = 0; i < features.size(); i++)
    {
        if (features.at(i).size() != size)
        {
            throw "Sizes of features are not all the same";
        }
    }
    //Can't use a learning rate less than or equal to zero
    if (learningRate <= 0)
    {
        throw "Bad learning rate (needs to be positive)";
    }
    //Initializes the weights to be one greater than the number of features (x1's and x2's for example)
    //Needs to one larger because x0 is always one, and so we need an extra for w0.
    w = vector<double>(features.at(0).size() + 1, 0);
    //Goes through the gradient descent to calculate the weights from the input data
    gradientDescent(features, labels, learningRate);
}

double LinearRegressionModel::predict(vector<double> &inputFeatures)
{
    //Makes sure that the input features have the same size as the features (which is the weights minus one)
    if (inputFeatures.size() != w.size() - 1)
    {
        throw "Number of input features does not match weights";
    }
    //Because we already have the weights calculated, we can just run it through the minimal cost function
    //to get the value
    return getHypothesisFunction(inputFeatures);
}

double LinearRegressionModel::getHypothesisFunction(vector<double> x)
{
    double retVal = 0;
    //Goes through the all the xi's and sums them up
    for (size_t i = 0; i < x.size(); i++)
    {
        retVal += w.at(i + 1) * x.at(i); //w.at(i + 1) because it is a size larger, the w0 is added later
    }
    return retVal + w.at(0); //Add the w0 to the sum already and return
}

void LinearRegressionModel::gradientDescent(vector<vector<double>> &features, vector<double> &labels, double learningRate)
{
    //This boolean value is kept true in the loop until the threshold is met
    bool keepErMovin = true;
    while (keepErMovin)
    {
        //Set it to false, because we set it to true when the threshold is not met
        keepErMovin = false;
        double sum = 0.0;     //Used in the gradient descent equation (GDE)
        vector<double> delta; //Store the temporary value that gets subtracted by the weight in the GDE
        //Because the weights vector is one size larger, this loop gets the w0 value.
        for (size_t i = 0; i < features.size(); i++)
        {
            double h = getHypothesisFunction(features.at(i)); //Calculates the hypothesis function
            sum += (h - labels.at(i));                        //This is only (h - lables) because x0 is always 1
        }
        delta.push_back((learningRate / features.size()) * sum);
        sum = 0.0; //Need to reset after each row of features
        //The loop that calculates the rest of the weights. Starts at one because we already found w0
        for (size_t i = 1; i < w.size(); i++)
        {
            for (size_t j = 0; j < features.size(); j++)
            {
                double h = getHypothesisFunction(features.at(j));     //Calculates the hypothesis function for each row
                sum += (h - labels.at(j)) * features.at(j).at(i - 1); //Gets the sum for each row
            }
            delta.push_back((learningRate / features.size()) * sum);
            sum = 0.0;
        }
        //This for loop resets the weights and checks for convergence
        for (size_t i = 0; i < w.size(); i++)
        {
            w.at(i) = w.at(i) - delta.at(i);
            if (delta.at(i) > 0.0001 || delta.at(i) < -0.0001)
            {
                keepErMovin = true;
            }
        }
    }
}