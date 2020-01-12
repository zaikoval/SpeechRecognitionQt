#ifndef DTWRECOGNISER_H
#define DTWRECOGNISER_H

#include <vector>

using namespace std;

class DTWRecogniser
{
public:
    DTWRecogniser() = delete;
    static double _distance(vector<vector<double>>, vector<vector<double>>);
private:

    static double _min3(double, double, double);
};

#endif // DTWRECOGNISER_H
