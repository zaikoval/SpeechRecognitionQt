#include "dtwrecogniser.h"
#include <math.h>


double DTWRecogniser::_distance(vector<vector<double>> word1, vector<vector<double>> word2)
{
    vector<vector<double>> diffMatrix, pathMatrix(word1.size(), vector<double>(word2.size(), 0));
    for (auto& el1: word1){
        diffMatrix.push_back(vector<double>());
        for (auto& el2: word2){
            double distance = 0;
            for (int i = 0; i < el1.size(); i++){
                distance += (el1[i] - el2[i])*(el1[i] - el2[i]);
            }
            diffMatrix[diffMatrix.size()-1].push_back(sqrt(distance));
        }
    }
    pathMatrix[0][0] = diffMatrix[0][0];
    for (int i=1; i<word1.size(); i++){
        pathMatrix[i][0] = diffMatrix[i][0] + pathMatrix[i-1][0];
    }
    for (int j=1; j<word2.size(); j++){
        pathMatrix[0][j] = diffMatrix[0][j] + pathMatrix[0][j-1];
    }

    for (int i = 1; i < word1.size(); i++){
        for (int j = 1; j < word2.size(); j++){
            pathMatrix[i][j] = _min3(pathMatrix[i - 1][j - 1], pathMatrix[i][j - 1], pathMatrix[i - 1][j]) +
                    diffMatrix[i][j];
        }
    }
    vector<double> pathVector;
    int i = word1.size()-1, j = word2.size()-1, idx=0;


    do {
        if (i > 0 and j > 0) {

            if (pathMatrix[i - 1][j - 1] < pathMatrix[i - 1][j]) {
                if (pathMatrix[i - 1][j - 1] < pathMatrix[i][j - 1]) {
                    i--;
                    j--;
                } else {
                    j--;
                }

            } else {
                if (pathMatrix[i - 1][j] < pathMatrix[i][j - 1]) {
                    i--;
                } else {
                    j--;
                }
            }

        } else {
            if (0 == i) {
                j--;
            } else {
                i--;
            }
        }
        idx++;
        pathVector.push_back(pathMatrix[i][j]);
    } while (i > 0 or j > 0);
    double distance = 0;
    for (auto el: pathVector){
        distance += el;
    }
    distance /= (idx + 1);
    return distance;
}

double DTWRecogniser::_min3(double a, double b, double c)
{
    if (a < b){
        if (a < c){
            return a;
        }
        else{
            return c;
        }
    }
    else{
        if (b < c){
            return b;
        }
        else{
            return c;
        }
    }
}
