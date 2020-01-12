#include "mainwindow.h"
#include <iostream>
#include "wavdecoder.h"
#include "mfccprocessor.h"
#include "frameprocessor.h"
#include "wordsplitter.h"
#include "fstream"
#include "dtwrecogniser.h"
#include <QApplication>
#include <QDir>
#include <utility>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    WavDecoder Decoder("/Users/zaikoval/Documents/GitHub/SpeachRecognitionQt/Samples/124.wav");

//    cout<<Decoder.getData().size()<<endl;

//    FrameProcessor fPro(10, 0.5, Decoder.getData(), 44100);
//    cout<< fPro.size()<<endl;
//    cout<< fPro.getFrameArray()[5].getData().size()<<endl;
//    WordSplitter WSplit(fPro, 500);
//    cout << WSplit.getWords(20, 20, -1).size() <<endl;
//    auto words = WSplit.getWords(20, 20, -1);
//    MFCCProcessor mPro0(words[0], 300, 8000, 13, 44100);//1
//    MFCCProcessor mPro1(words[1], 300, 8000, 13, 44100);//1
//    MFCCProcessor mPro2(words[2], 300, 8000, 13, 44100);//2
//    MFCCProcessor mPro3(words[3], 300, 8000, 13, 44100);//2
//    MFCCProcessor mPro4(words[4], 300, 8000, 13, 44100);//4
//    MFCCProcessor mPro5(words[5], 300, 8000, 13, 44100);//4
//    cout << DTWRecogniser::_distance(mPro0.getMFCC(), mPro1.getMFCC()) <<"    "<< DTWRecogniser::_distance(mPro4.getMFCC(), mPro0.getMFCC()) <<"    1-1,    4-1"<<endl;
//    cout << DTWRecogniser::_distance(mPro2.getMFCC(), mPro3.getMFCC()) <<"    "<<DTWRecogniser::_distance(mPro2.getMFCC(), mPro4.getMFCC())<<"    2-2,    2-4"<<endl;
//    cout << DTWRecogniser::_distance(mPro4.getMFCC(), mPro5.getMFCC()) <<" 4-4"<<endl;
//        QBuffer buffer;
//        QAudioInput *audio;
//        buffer.open(QBuffer::WriteOnly);
//        QAudioFormat format;
//        // set up the format you want, eg.
//        format.setSampleRate(8000);
//        format.setChannelCount(1);
//        format.setSampleSize(16);
//        format.setCodec("audio/PCM");
//        format.setByteOrder(QAudioFormat::LittleEndian);
//        format.setSampleType(QAudioFormat::UnSignedInt);

//        QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
//        if (!info.isFormatSupported(format)) {
//            qDebug()<<"default format not supported try to use nearest";
//            format = info.nearestFormat(format);
//        }

//        audio = new QAudioInput(format);
//        QTimer* timer = new QTimer;
//        connect(timer, SIGNAL(timeout()), SLOT(stopReco()));
//        timer->start(5000);
//        audio->start(&buffer);




//    WavDecoder Decoder("/Users/zaikoval/Documents/GitHub/SpeachRecognitionQt/Samples/liba.wav");
//    FrameProcessor fPro(10, 0.5, Decoder.getData(), 44100);
//    WordSplitter wSplit(fPro, 500);
//    auto words = wSplit.getWords(40, 40, -1);
//    cout<<"a";
//    ofstream fout;
//    int i = 0;
//    for (auto el:  words){
//        MFCCProcessor mPro(el, 85, 6000, MEL_COEFS, 44100);
//        auto kek = mPro.getMFCC();
//        i++;
//        fout.open("/Users/zaikoval/Documents/GitHub/SpeachRecognitionQt/binSamples/" + QString::number(i).toStdString(), ios::binary);
//        if (fout.good()){
//            for(auto j: kek){
//                fout.write((char*)j.data(), j.size()*sizeof(double));
//            }
//        }
//        fout.close();
//    }





//        cout<<"HELLO"<<endl;
        return a.exec();
}
