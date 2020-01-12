#include <iostream>
#include "wavdecoder.h"
#include "mfccprocessor.h"
#include "frameprocessor.h"
#include "wordsplitter.h"
#include "fstream"
#include "dtwrecogniser.h"

using namespace std;

int main()
{
    WavDecoder Decoder("/Users/zaikoval/Documents/GitHub/speech-recognition-oop/Samples/1-10.wav");

    cout<<Decoder.getData().size()<<endl;

    FrameProcessor fPro(10, 0.5, Decoder.getData(), 44100);
    cout<< fPro.size()<<endl;
    cout<< fPro.getFrameArray()[5].getData().size()<<endl;
    WordSplitter WSplit(fPro, 500);
    cout << WSplit.getWords(20, 20, -1).size() <<endl;
    auto words = WSplit.getWords(20, 20, -1);
//    MFCCProcessor mPro0(words[0], 300, 8000, 13, 44100);//1
//    MFCCProcessor mPro1(words[1], 300, 8000, 13, 44100);//1
//    MFCCProcessor mPro2(words[2], 300, 8000, 13, 44100);//2
//    MFCCProcessor mPro3(words[3], 300, 8000, 13, 44100);//2
//    MFCCProcessor mPro4(words[4], 300, 8000, 13, 44100);//4
//    MFCCProcessor mPro5(words[5], 300, 8000, 13, 44100);//4
//    cout << DTWRecogniser::_distance(mPro0.getMFCC(), mPro1.getMFCC()) <<"    "<< DTWRecogniser::_distance(mPro4.getMFCC(), mPro0.getMFCC()) <<"    1-1,    4-1"<<endl;
//    cout << DTWRecogniser::_distance(mPro2.getMFCC(), mPro3.getMFCC()) <<"    "<<DTWRecogniser::_distance(mPro2.getMFCC(), mPro4.getMFCC())<<"    2-2,    2-4"<<endl;
//    cout << DTWRecogniser::_distance(mPro4.getMFCC(), mPro5.getMFCC()) <<"4-4"<<endl;
    cout<<"HELLO"<<endl;
    return 0;
}
//создает объект класса WordSplitter моментально

//разбираемся с фукнцией получения слов
