#include <iostream>
#include "LinearRegressionModel.h"

using namespace std;

int main()
{
    try
    {
        vector<vector<double>> features = {{1.0, 1.0}, {2.0, 2.0}, {3.0, 3.0}};
        vector<double> labels = {3.0, 2.0, 1.0};

        LinearRegressionModel model(features, labels, .1);

        vector<double> unknownInput = {0.0, 4.0};

        double predictedValue = model.predict(unknownInput); //should be about 2.0

        cout << "The predicted value is " << predictedValue << endl;
    }
    catch (const char *e)
    {
        cout << e;
    };
    try
    {
        vector<vector<double>> features = {{1.0, 2.0}, {3.0, 3.0}, {4.0, 4.0}};
        vector<double> labels = {3.0, 1.0, 0.0};

        LinearRegressionModel model(features, labels, .1); //2.9

        vector<double> unknownInput = {1.0, 1.0};

        double predictedValue = model.predict(unknownInput);

        cout << "The predicted value is " << predictedValue << endl;
    }
    catch (const char *e)
    {
        cout << e;
    };
    try
    {
        vector<vector<double>> features = {{6.2}, {2.8}, {8.3}, {1.5}, {2.0}, {3.7}, {4.4}, {9.4}, {6.9}};
        vector<double> labels = {19.0, 9.0, 40.0, 7.0, 20.0, 17.0, 27.0, 44.0, 30.0};

        LinearRegressionModel model(features, labels, .01); //-13.1 with a learning rate of .01

        vector<double> unknownInput = {-4.0};

        double predictedValue = model.predict(unknownInput);

        cout << "The predicted value is " << predictedValue << endl;
    }
    catch (const char *e)
    {
        cout << e;
    };
    return 0;
}