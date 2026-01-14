#include <iostream>
//#include <vector>
//#include <random>
//#include <iomanip>
//#include <algorithm>
#include "Stats.hpp"

using namespace std;

int main()
{

    cout << "\nApplication starting..." << endl;
    int row=6, col=10;
    vector<vector<double>> dataFrame3x4 = CreateDataFrame(row, col);
    cout << "\n( " << row << " x " << col << " ) dataframe with double values:\n";
    for (size_t row = 0; row < dataFrame3x4.size(); row++)
    {
        for(size_t col = 0; col < dataFrame3x4[row].size(); col++)
        {
            if(col == 0) cout << "{ ";
            cout << dataFrame3x4[row][col];
            if(col < dataFrame3x4[row].size() -1) cout << ", ";
            else cout << " }";
        }
        cout << "\n";
    }

    // percent change
    vector<vector<double>> dataFrame2 =  CreateFeatureAttributes(dataFrame3x4, 0, col-1, GetPercentageChange);
    col = col + 1;
    cout << "\n( " << row << " x " << col << " ) dataframe with double values:\n";
    for (size_t row = 0; row < dataFrame2.size(); row++)
    {
        for(size_t col = 0; col < dataFrame2[row].size(); col++)
        {
            if(col == 0) cout << "{ ";
            cout << dataFrame2[row][col];
            if(col < dataFrame2[row].size() -1) cout << ", ";
            else cout << " }";
        }
        cout << "\n";
    }

    // GetFeatureStat(..): Average , Min, Max, Median, Sum
    int featureColIndex = 1;
    cout << "\nGetFeatureStat(Average)..Column index: " << featureColIndex << "): " << GetFeatureStat(dataFrame3x4, 0, featureColIndex, GetAverage) << endl;
    cout << "\nGetFeatureStat(Min)..Column index: " << featureColIndex << "): " << GetFeatureStat(dataFrame3x4, 0, featureColIndex, GetMin) << endl;
    cout << "\nGetFeatureStat(Max)..Column index: " << featureColIndex << "): " << GetFeatureStat(dataFrame3x4, 0, featureColIndex, GetMax) << endl;
    cout << "\nGetFeatureStat(Median)..Column index: " << featureColIndex << "): " << GetFeatureStat(dataFrame3x4, 0, featureColIndex, GetMedian) << endl;
    cout << "\nGetFeatureStat(Sum)..Column index: " << featureColIndex << "): " << GetFeatureStat(dataFrame3x4, 0, featureColIndex, GetSum) << endl;
    cout << "\nGetFeatureStat(Standard Deviation)..Column index: " << featureColIndex << "): " << GetFeatureStat(dataFrame3x4, 0, featureColIndex, GetStandardDeviation) << endl;

    cout << "\nTest: Matrix Transpose:\n";
    vector<vector<double>> inputMatrix = CreateDataFrame(3, 4);
    vector<vector<double>> transposedMatrix = matrixTranspose(inputMatrix);
    cout << "\nInput Matrix:\n";
    for (size_t row = 0; row < inputMatrix.size(); row++)
    {
        for(size_t col = 0; col < inputMatrix[row].size(); col++)
        {
            if(col == 0) cout << "{ ";
            cout << inputMatrix[row][col];
            if(col < inputMatrix[row].size() -1) cout << ", ";
            else cout << " }";
        }
        cout << "\n";
    }
    cout << "\nTransposed Matrix:\n";
    for (size_t row = 0; row < transposedMatrix.size(); row++)
    {
        for(size_t col = 0; col < transposedMatrix[row].size(); col++)
        {
            if(col == 0) cout << "{ ";
            cout << transposedMatrix[row][col];
            if(col < transposedMatrix[row].size() -1) cout << ", ";
            else cout << " }";
        }
        cout << "\n";
    }

    cout << "\nTest: Matrix Multiplication:\n";    
    vector<vector<double>> matrixC = matrixMultiplication(inputMatrix, transposedMatrix);
    
    cout << "\nMatrix C (A * T of A):\n";
    for (size_t row = 0; row < matrixC.size(); row++)
    {
        for(size_t col = 0; col < matrixC[row].size(); col++)
        {
            if(col == 0) cout << "{ ";
            cout << matrixC[row][col];
            if(col < matrixC[row].size() -1) cout << ", ";
            else cout << " }";
        }
        cout << "\n";
    }

    cout << "\nApplication closing. Press any key..." << endl; getchar();

    return 0;
}

//user1@T3500-A:~/Projs/CCpp/test1$ g++ -std=c++23 Stats.cpp -o Stats.exe
//user1@T3500-A:~/Projs/CCpp/test1$ ./Stats.exe
// PS C:\Projs\AI-ML\Cpp\DataScience> g++ -std=c++23 test1.cpp -o test1.exe -mconsole
