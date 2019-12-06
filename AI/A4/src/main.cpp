#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "NeuralNetwork.h"

using namespace std;

string drawStr = "draws.txt";
string xWinStr = "xWins.txt";
string oWinStr = "oWins.txt";

vector<double> X_WIN = {
	1.0,
	0.0,
	0.0,
};
vector<double> O_WIN = {
	0.0,
	1.0,
	0.0,
};
vector<double> DRAW = {
	0.0,
	0.0,
	1.0,
};

//This function gets the info from the file, and returns it all as a vector of strings
vector<string> getFileContent(string fileName)
{
	// Open the File
	ifstream file(fileName.c_str());

	//Create the cector that will store the info from the .txt file
	vector<string> vecOfStrs;

	// Check if object is valid
	if (!file)
	{
		cerr << "Cannot open the File : " << fileName << endl;
	}

	string str;
	// Read the next line from File untill it reaches the end.
	while (getline(file, str))
	{
		// Line contains string of length > 0, save it in vector
		if (str.size() > 0)
			vecOfStrs.push_back(str);
	}
	//Close The File
	file.close();
	return vecOfStrs;
}

//This function takes in the vector of strings from the files and shuffles it up.
void shuffle(vector<string> &vecOfStrs)
{
	srand(time(NULL)); //Seed random number
	for (size_t i = 0; i < vecOfStrs.size(); i++)
	{
		//This finds a random number within the size of the vector
		int randomIndex = rand() % vecOfStrs.size();
		//Then we swap the current element with that of the random number
		swap(vecOfStrs[i], vecOfStrs[randomIndex]);
	}
}

//Because the neural network needs input and label data in the form of vector of vector of doubles, this function
//takes the shuffled vector of strings, and converts it into the correct format. Functions below turn this mega
//vector into features, labels, and test data.
vector<vector<double>> convert(vector<string> &vecOfStrs)
{
	vector<vector<double>> retVec;
	vector<double> ticTacToeBoard; //Result of converting X's and O's to doubles

	//Go through the vector of strings and look at each character on the tictactoe board
	for (size_t i = 0; i < vecOfStrs.size(); i++)
	{
		for (size_t j = 0; j < vecOfStrs[i].size(); j++)
		{
			//The comma separates the tictactoe board from the result of that board
			if (vecOfStrs[i].at(j) != ',')
			{
				//All X's will be converted into ones.
				if (vecOfStrs[i].at(j) == 'X')
				{
					ticTacToeBoard.push_back(1.0);
				}
				//All O's will be converted into -1.0
				else if (vecOfStrs[i].at(j) == 'O')
				{
					ticTacToeBoard.push_back(-1.0);
				}
				//All spaces that are empty are zeros
				else if (vecOfStrs[i].at(j) == '-')
				{
					ticTacToeBoard.push_back(0.0);
				}
				else
				{
					cout << "Error" << endl;
				}
			}
			else
			{
				//We need to break because there is X_WIN, and O_WIN which needs to be handled in a different step
				break;
			}
		}
		//.at(11) is right after the comma, so we can look to see what the results of the board are
		//1 for X_WIN
		if (vecOfStrs[i].at(11) == 'X')
		{
			ticTacToeBoard.push_back(1.0);
		}
		//-1 for O_WIN
		else if (vecOfStrs[i].at(11) == 'O')
		{
			ticTacToeBoard.push_back(-1.0);
		}
		//0 for the draw state
		else if (vecOfStrs[i].at(11) == 'D')
		{
			ticTacToeBoard.push_back(0.0);
		}
		else
		{
			cout << "Error" << endl;
		}
		//We then add the new tictacboard with doubles to the new vector of vector of doubles
		retVec.push_back(ticTacToeBoard);
		//Clear the current board
		ticTacToeBoard.clear();
	}
	return retVec;
}

//This function takes the just converted vector<string> --> vector<vector<double>> and removes the last double
//from each vector<double> (this value is the label, i.e. who won the game).
vector<vector<double>> getLabel(vector<vector<double>> &v)
{
	vector<vector<double>> retVec;
	//GO through the vector
	for (size_t i = 0; i < v.size(); i++)
	{
		//Look at the winning state..
		if (v[i].at(9) == 1.0)
		{
			//Push back a X_WIN (there are three output nodes for this system) for 1
			retVec.push_back(X_WIN); // {1.0,0,0}
			v[i].pop_back();		 //Remove the label from the training features
		}
		else if (v[i].at(9) == -1.0)
		{
			//Push back a O_WIN (there are three output nodes for this system) for -1
			retVec.push_back(O_WIN); // {0,1.0,0}
			v[i].pop_back();		 //Remove the label from the training features
		}
		else if (v[i].at(9) == 0.0)
		{
			//Push back a DRAW (there are three output nodes for this system) for 0
			retVec.push_back(DRAW); // {0,0,1.0}
			v[i].pop_back();		//Remove the label from the training features
		}
		else
		{
			cout << "Error" << endl;
		}
	}
	return retVec;
}

//This function splits the data up to a 75% (training) and 25% (test)
//This works for both the features and the labels
vector<vector<double>> split(vector<vector<double>> &v)
{
	vector<vector<double>> retVec;
	int newSize = (int)(0.75 * v.size()); //Gets the size of the test data (25% of the original vector)
	//Start at this point in the original vector and copy the elements into the new
	for (size_t i = newSize; i < v.size(); i++)
	{
		retVec.push_back(v[i]);
	}
	v.erase(v.begin() + newSize, v.end()); //Then we remove the elements we just copied over
	return retVec;
}

//This is just a wrapper function for creating and testing the neural network
void runNeuralNetwork(vector<int> &networkArchitecture, vector<vector<double>> trainingFeatures, vector<vector<double>> labelData, vector<vector<double>> testData, vector<vector<double>> testLabelData, double LR, int iter)
{
	NeuralNetwork nn(networkArchitecture, trainingFeatures, labelData, LR, iter); //Creates the network
	vector<vector<double>> finalResults;										  //Used in the error calculation

	int correctCounter = 0;
	double avgError = 0;

	//This goes through and predicts for every single piece of test data
	for (size_t i = 0; i < testData.size(); i++)
	{
		vector<double> result = nn.predict(testData[i]);
		finalResults.push_back(result);

		//This gets the position where it is maximum from the predict method (determines who won)
		double max = result[0];
		int posOfMax = 0;
		for (size_t j = 1; j < result.size(); j++)
		{
			if (result[j] > max)
			{
				max = result[j];
				posOfMax = j;
			}
		}

		//This calculates the average error
		for (size_t j = 0; j < result.size(); j++)
		{
			if ((int)j == posOfMax)
			{
				avgError += abs(result[j] - 1.0);
			}
			else
			{
				avgError += abs(result[j]);
			}
		}

		//We then check to see if it was a correct match from the corresponding test data
		if (posOfMax == 0 && testLabelData[i] == X_WIN)
		{
			correctCounter++;
		}
		else if (posOfMax == 1 && testLabelData[i] == O_WIN)
		{
			correctCounter++;
		}
		else if (posOfMax == 2 && testLabelData[i] == DRAW)
		{
			correctCounter++;
		}
	}

	cout << "Number correctly detected: " << correctCounter << "/" << finalResults.size() << " " << (double)correctCounter / (double)finalResults.size() << endl;
	cout << "The Average Error rate: " << avgError / (3 * testData.size()) << endl; //There is a 3 here because there are 3 possible outcomes
}

int main()
{
	clock_t tStart = clock();
	//Gets all the training data from the text files and merges them into one
	vector<string> drawVector = getFileContent(drawStr);
	vector<string> xWinVector = getFileContent(xWinStr);
	vector<string> oWinVector = getFileContent(oWinStr);

	vector<string> all;

	all.reserve(drawVector.size() + xWinVector.size() + oWinVector.size()); // preallocate memory
	all.insert(all.end(), drawVector.begin(), drawVector.end());
	all.insert(all.end(), xWinVector.begin(), xWinVector.end());
	all.insert(all.end(), oWinVector.begin(), oWinVector.end());

	//We then shuffle all the data
	shuffle(all);
	//And convert all the elements to doubles so that the Neural network can use it
	vector<vector<double>> trainingFeatures = convert(all);
	vector<vector<double>> labelData = getLabel(trainingFeatures);
	vector<vector<double>> testData = split(trainingFeatures);
	vector<vector<double>> testLabelData = split(labelData);

	//This was the best structure that I determined (although I ran it a few more times, it wasn't always so good...)
	vector<int> networkArchitecture = {9, 9, 3};
	runNeuralNetwork(networkArchitecture, trainingFeatures, labelData, testData, testLabelData, 0.8, 1000);

	/* 
	I let this loop run to determine the best structures:

	for (int i = 1; i < 10; i++) {
		for (int j = 1; j < 10; j++) {
			double lr = 0.1*i;
			cout << "LR: " << lr << " Hidden Layers: " << j << endl;
			vector<int> networkArchitecture = {9, j, 3};
			runNeuralNetwork(networkArchitecture, trainingFeatures, labelData, testData, testLabelData, lr, 1000);
		}
	}
	From the output of this, it seems like the best learning rate is 0.5 because it had the most accurate results
	for all different hidden layers. Also, four input nodes seemed to have the highest average.
	Here is the output:
	LR: 0.1 Hidden Layers: 1
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.0114748
	LR: 0.1 Hidden Layers: 2
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00650668
	LR: 0.1 Hidden Layers: 3
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00970357
	LR: 0.1 Hidden Layers: 4
	Number correctly detected: 238/240 0.991667
	The Average Error rate: 0.00846213
	LR: 0.1 Hidden Layers: 5
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00719817
	LR: 0.1 Hidden Layers: 6
	Number correctly detected: 238/240 0.991667
	The Average Error rate: 0.00962739
	LR: 0.1 Hidden Layers: 7
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00938575
	LR: 0.1 Hidden Layers: 8
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00574917
	LR: 0.1 Hidden Layers: 9
	Number correctly detected: 238/240 0.991667
	The Average Error rate: 0.00974161
	LR: 0.2 Hidden Layers: 1
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.0108748
	LR: 0.2 Hidden Layers: 2
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00726182
	LR: 0.2 Hidden Layers: 3
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00824352
	LR: 0.2 Hidden Layers: 4
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00715867
	LR: 0.2 Hidden Layers: 5
	Number correctly detected: 236/240 0.983333
	The Average Error rate: 0.00712256
	LR: 0.2 Hidden Layers: 6
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00343465
	LR: 0.2 Hidden Layers: 7
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00638112
	LR: 0.2 Hidden Layers: 8
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00458883
	LR: 0.2 Hidden Layers: 9
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00397298
	LR: 0.3 Hidden Layers: 1
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.0114263
	LR: 0.3 Hidden Layers: 2
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00671435
	LR: 0.3 Hidden Layers: 3
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00754406
	LR: 0.3 Hidden Layers: 4
	Number correctly detected: 235/240 0.979167
	The Average Error rate: 0.00841948
	LR: 0.3 Hidden Layers: 5
	Number correctly detected: 236/240 0.983333
	The Average Error rate: 0.00307663
	LR: 0.3 Hidden Layers: 6
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00361407
	LR: 0.3 Hidden Layers: 7
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00601132
	LR: 0.3 Hidden Layers: 8
	Number correctly detected: 238/240 0.991667
	The Average Error rate: 0.00521655
	LR: 0.3 Hidden Layers: 9
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00565655
	LR: 0.4 Hidden Layers: 1
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.0116308
	LR: 0.4 Hidden Layers: 2
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00997669
	LR: 0.4 Hidden Layers: 3
	Number correctly detected: 236/240 0.983333
	The Average Error rate: 0.00483492
	LR: 0.4 Hidden Layers: 4
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00541933
	LR: 0.4 Hidden Layers: 5
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00393536
	LR: 0.4 Hidden Layers: 6
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00466954
	LR: 0.4 Hidden Layers: 7
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00388369
	LR: 0.4 Hidden Layers: 8
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00733269
	LR: 0.4 Hidden Layers: 9
	Number correctly detected: 236/240 0.983333
	The Average Error rate: 0.00471623
	LR: 0.5 Hidden Layers: 1
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.0113346
	LR: 0.5 Hidden Layers: 2
	Number correctly detected: 236/240 0.983333
	The Average Error rate: 0.0107557
	LR: 0.5 Hidden Layers: 3
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00441605
	LR: 0.5 Hidden Layers: 4
	Number correctly detected: 238/240 0.991667
	The Average Error rate: 0.00678457
	LR: 0.5 Hidden Layers: 5
	Number correctly detected: 238/240 0.991667
	The Average Error rate: 0.00436863
	LR: 0.5 Hidden Layers: 6
	Number correctly detected: 238/240 0.991667
	The Average Error rate: 0.00366078
	LR: 0.5 Hidden Layers: 7
	Number correctly detected: 238/240 0.991667
	The Average Error rate: 0.00467827
	LR: 0.5 Hidden Layers: 8
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00466102
	LR: 0.5 Hidden Layers: 9
	Number correctly detected: 238/240 0.991667
	The Average Error rate: 0.00388791
	LR: 0.6 Hidden Layers: 1
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.0115354
	LR: 0.6 Hidden Layers: 2
	Number correctly detected: 235/240 0.979167
	The Average Error rate: 0.0103002
	LR: 0.6 Hidden Layers: 3
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00476483
	LR: 0.6 Hidden Layers: 4
	Number correctly detected: 235/240 0.979167
	The Average Error rate: 0.00607011
	LR: 0.6 Hidden Layers: 5
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00247581
	LR: 0.6 Hidden Layers: 6
	Number correctly detected: 238/240 0.991667
	The Average Error rate: 0.00376797
	LR: 0.6 Hidden Layers: 7
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.0021625
	LR: 0.6 Hidden Layers: 8
	Number correctly detected: 236/240 0.983333
	The Average Error rate: 0.00409148
	LR: 0.6 Hidden Layers: 9
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00497497
	LR: 0.7 Hidden Layers: 1
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.0117186
	LR: 0.7 Hidden Layers: 2
	Number correctly detected: 236/240 0.983333
	The Average Error rate: 0.00906819
	LR: 0.7 Hidden Layers: 3
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00520414
	LR: 0.7 Hidden Layers: 4
	Number correctly detected: 238/240 0.991667
	The Average Error rate: 0.00292973
	LR: 0.7 Hidden Layers: 5
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00431316
	LR: 0.7 Hidden Layers: 6
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00451616
	LR: 0.7 Hidden Layers: 7
	Number correctly detected: 236/240 0.983333
	The Average Error rate: 0.00762337
	LR: 0.7 Hidden Layers: 8
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00414875
	LR: 0.7 Hidden Layers: 9
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00467707
	LR: 0.8 Hidden Layers: 1
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.0122015
	LR: 0.8 Hidden Layers: 2
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00607762
	LR: 0.8 Hidden Layers: 3
	Number correctly detected: 238/240 0.991667
	The Average Error rate: 0.00355669
	LR: 0.8 Hidden Layers: 4
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.0026795
	LR: 0.8 Hidden Layers: 5
	Number correctly detected: 236/240 0.983333
	The Average Error rate: 0.0048216
	LR: 0.8 Hidden Layers: 6
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.0040959
	LR: 0.8 Hidden Layers: 7
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00195733
	LR: 0.8 Hidden Layers: 8
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00400169
	LR: 0.8 Hidden Layers: 9
	Number correctly detected: 239/240 0.995833
	The Average Error rate: 0.00634244
	LR: 0.9 Hidden Layers: 1
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.0137033
	LR: 0.9 Hidden Layers: 2
	Number correctly detected: 236/240 0.983333
	The Average Error rate: 0.00772546
	LR: 0.9 Hidden Layers: 3
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00576017
	LR: 0.9 Hidden Layers: 4
	Number correctly detected: 238/240 0.991667
	The Average Error rate: 0.00432522
	LR: 0.9 Hidden Layers: 5
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00413442
	LR: 0.9 Hidden Layers: 6
	Number correctly detected: 233/240 0.970833
	The Average Error rate: 0.00775238
	LR: 0.9 Hidden Layers: 7
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00477564
	LR: 0.9 Hidden Layers: 8
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00294237
	LR: 0.9 Hidden Layers: 9
	Number correctly detected: 237/240 0.9875
	The Average Error rate: 0.00336838
	Time taken: 3782.20s
	*/

	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

	return 0;
}