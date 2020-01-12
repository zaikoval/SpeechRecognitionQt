#include "frameprocessor.h"
#include <iostream>
#include <vector>
using namespace std;
// как передавать Sample Rate (возможно сделать дружественным)
FrameProcessor::FrameProcessor(const int &frameWidth, const float &overlap, const vector<double> &data, int sampleRate)
{
/*lets implement some logic here
 * wavdecoder.sampleRate -what amount of samples does consist in 1 second
 */

    int frameSize = int(sampleRate * frameWidth / 1000); //44100
    vector<double> frameData; //создаем вектор
    int i = 0;
    int j = 0;
    int shift = (int)(frameSize-frameSize*overlap);
    while (i < (data.size()-frameSize)) {
        j = 0;
        while (j<frameSize) {
            frameData.push_back(data.at(i+j));
            j++;
        }
        // заполнили векто
        Frame tmp = Frame(frameData);
        frameArray.push_back(tmp);
        frameData.clear();
        i += shift;
    }
}

FrameProcessor::FrameProcessor(vector<Frame> _vec): frameArray(_vec){}

vector<Frame> FrameProcessor::getFrameArray()
{
    return frameArray;
}

size_t FrameProcessor::size() const
{
    return frameArray.size();
}

Frame FrameProcessor::at(size_t i) const
{
    return frameArray.at(i);
}
