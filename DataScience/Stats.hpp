//#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <algorithm>

using namespace std;

#define Invalid_Or_Error_Return_Value -99.99

struct CallResult
{
    bool bSuccess;
    double result;
    char message[100];
};

double getRandomDouble()
{
    return 10.0 * ((double)rand() / RAND_MAX);
}

// create rxc data frame having all double data
vector<vector<double>> CreateDataFrame(int r, int c)
{
    vector<vector<double>> ret;
    if(r < 1 || c < 1) return ret;
    for(size_t row=0; row<r; row++)
    {
        vector<double> v1;
        for(size_t col=0; col < c; col++)
        {
            v1.push_back(getRandomDouble());
        }
        ret.push_back(v1);
    }

    return ret;
}

vector<vector<double>> matrixTranspose(vector<vector<double>> inputMatrix)
{
    vector<vector<double>> ret;
    if(inputMatrix.size() < 1) return ret;
    if(inputMatrix[0].size() < 1) return ret;

    for(size_t col=0; col<inputMatrix[0].size(); col++)
    {
        vector<double> v1;
        for(size_t row=0; row<inputMatrix.size(); row++)
        {
            v1.push_back(inputMatrix[row][col]);
        }
        ret.push_back(v1);
    }

    return ret;
}
vector<vector<double>> matrixMultiplication(vector<vector<double>> A, vector<vector<double>> B)
{
    vector<vector<double>> ret;
    if(A.size() < 1 || B.size() < 1) return ret;
    if(A[0].size() < 1 || B[0].size() < 1) return ret;
    if(A[0].size() != B.size()) return ret;

    for(size_t row=0; row<A.size(); row++)
    {
        vector<double> v1;
        for(size_t col=0; col<B[0].size(); col++)
        {
            double sum = 0.0;
            for(size_t k=0; k<A[0].size(); k++)
                sum += A[row][k] * B[k][col];
            v1.push_back(sum);
        }
        ret.push_back(v1);
    }

    return ret;
}
double GetFeatureStat(vector<vector<double>> inputDF, int IndexColumn, int featureColumnIndex, double (*function_name)(vector<double>))
{
    //double InvalidOrErrorResult = -99.99;
    if(inputDF.size() < 1 || featureColumnIndex < 0) return Invalid_Or_Error_Return_Value;
    if(inputDF[0].size() < 1) return Invalid_Or_Error_Return_Value;
    if(inputDF[0].size() < featureColumnIndex) return Invalid_Or_Error_Return_Value;
    if(function_name == nullptr) return Invalid_Or_Error_Return_Value;

    vector<double> inputToFunctionPtr;
    for(size_t row=0; row<inputDF.size(); row++)
        inputToFunctionPtr.push_back(inputDF[row][featureColumnIndex]);
    return function_name(inputToFunctionPtr);
}

vector<vector<double>> CreateFeatureAttributes(vector<vector<double>> inputDF, int IndexColumn, int opColIndex, double (*function_name)(double, double))
{
    if(inputDF.size() < 1 || opColIndex < 0) return inputDF;
    if(inputDF[0].size() < IndexColumn) return inputDF;
    if(inputDF[0].size() < opColIndex) return inputDF;

    inputDF[0].resize(inputDF[0].size() + 1);
    double y1, y2;
    for(size_t row=1; row<inputDF.size(); row++)
    {
        y1 = inputDF[row-1][opColIndex]; y2 = inputDF[row][opColIndex];
        inputDF[row].resize(inputDF[row].size() + 1);
        inputDF[row][inputDF[row].size()-1] = function_name(y1, y2);
    }

    return inputDF;
}

double GetPercentageChange(double first, double last)
{
    return (double)(100.00 * (last-first)/(first));
}

double GetAverage(vector<double> values)
{
    if(values.size() < 1) return Invalid_Or_Error_Return_Value;

    double ret = 0.0;
    for (size_t i = 0; i < values.size(); i++)
    {
        ret += (double)values[i];
    }
    return ret / (double)(values.size());
}

double GetSum(vector<double> values)
{
    if(values.size() < 1) return Invalid_Or_Error_Return_Value;

    double ret = 0.0;
    for (size_t i = 0; i < values.size(); i++)
    {
        ret += (double)values[i];
    }
    return ret;
}

double GetMin(vector<double> values)
{
    if(values.size() < 1) return Invalid_Or_Error_Return_Value;

    double ret = 0.0;
    for (size_t i = 0; i < values.size(); i++)
        if((double)values[i] < ret) ret = (double)values[i];
    return ret;
}

double GetMax(vector<double> values)
{
    if(values.size() < 1) return Invalid_Or_Error_Return_Value;

    double ret = 0.0;
    for (size_t i = 0; i < values.size(); i++)
        if(ret < (double)values[i]) ret = (double)values[i];
    return ret;
}

double GetMedian(vector<double> values)
{
    if(values.size() < 1) return Invalid_Or_Error_Return_Value;

    sort(values.begin(), values.end());
    int ss = values.size();
    if(ss % 2 == 1) return values[ss/2];
    else return (values[ss/2] + values[ss/2 - 1]) / 2.0;    
}

double GetStandardDeviation(vector<double> values) 
{ 
    if (values.empty()) return 0.0; 
    double mean = std::accumulate(values.begin(), values.end(), 0.0) / values.size(); 
    double sq_sum = std::accumulate( values.begin(), values.end(), 0.0, [mean](double acc, double x) { return acc + (x - mean) * (x - mean); } ); 
    return std::sqrt(sq_sum / values.size());
}
