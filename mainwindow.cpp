#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <typeinfo>
#include <algorithm>
#include "wavdecoder.h"
#include "mfccprocessor.h"
#include "frameprocessor.h"
#include "wordsplitter.h"
#include "dtwrecogniser.h"
#include <fstream>
#include <QDir>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ifstream fin;
    QDir dir("/Users/zaikoval/Documents/GitHub/SpeachRecognitionQt/binSamples/");
    if (dir.exists()){
        dir.setFilter(QDir::Files);
        dir.setSorting(QDir::Name);
        QFileInfoList list = dir.entryInfoList();
        for (int i = 0; i < list.size(); ++i)
        {
            QFileInfo fileInfo = list.at(i);
            fin.open("/Users/zaikoval/Documents/GitHub/SpeachRecognitionQt/binSamples/" + fileInfo.fileName().toStdString(), ios::binary);
            if (fin.good()){
                vector<vector<double>> word;
                while(!fin.eof()){
                    vector<double> frame;
                    frame.resize(MEL_COEFS);
                    fin.read((char*)frame.data(), MEL_COEFS*sizeof (double));
                    word.push_back(frame);
                }
                word.erase(--word.end());
                library.insert(make_pair(fileInfo.fileName().toStdString(), word));
            }
            fin.close();
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    buffer.setBuffer(&array);
    buffer.open(QBuffer::WriteOnly | QIODevice::Truncate);
    QAudioFormat format;
    // set up the format you want, eg.
    format.setSampleRate(44100);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/PCM");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
    auto default_deviceName = info.deviceName();


    if(!default_deviceName.isEmpty())
            {
                auto preferred_format = info.preferredFormat();
                QString codec = preferred_format.codec();
                int sampleRate = preferred_format.sampleRate();
                int sampleSize = preferred_format.sampleSize();
                int channelCount = preferred_format.channelCount();
                int sampleType = preferred_format.sampleType();
                int byteOrder =  preferred_format.byteOrder();
                qDebug() << "codec:" << codec.toLatin1() << "sampleRate :" << sampleRate << "sampleSize:" << sampleSize << "channel Count:" << channelCount << "sample type:" <<sampleType
                    << "byteOrder:" << byteOrder;
            }

    if (!info.isFormatSupported(format)) {
        qDebug()<<"default format not supported try to use nearest";
        format = info.nearestFormat(format);
        QString codec = format.codec();
        int sampleRate = format.sampleRate();
        int sampleSize = format.sampleSize();
        int channelCount = format.channelCount();
        int sampleType = format.sampleType();
        int byteOrder =  format.byteOrder();
        qDebug() << "codec:" << codec.toLatin1() << "sampleRate :" << sampleRate << "sampleSize:" << sampleSize << "channel Count:" << channelCount << "sample type:" <<sampleType
            << "byteOrder:" << byteOrder;

    }

    audio = new QAudioInput(format, this);
    audio->start(&buffer);
}

void MainWindow::on_pushButton_2_clicked()
{
    audio->stop();
    buffer.close();
    delete audio;
    buffarr.resize(array.size() / 2);
    std::memcpy(buffarr.data(), array.data_ptr(), array.length()); //buffarr ненормализованные значения
    std::cout<<"cool"<<std::endl;
    data.clear();
    int16_t  max_val = 0, min_val = 0;
    for(auto it = buffarr.begin(); it != buffarr.end(); it++){
        if (*it < min_val){
            min_val = *it;
        }
        if (*it > max_val){
            max_val = *it;
        }
    }
    int16_t norm_coef = std::max(max_val, min_val);
    for (auto e: buffarr){
        data.push_back(static_cast<double>(e)/norm_coef);
    }

    qDebug() << data.size();
    FrameProcessor fPro(10, 0.5, data, 44100);
    WordSplitter WSplit(fPro, 500);
    auto words = WSplit.getWords(40,40,-1);
    qDebug()<<"Количество распознанных слов"<<words.size();
    QString results;
    //для всех слов mel coeffs
    ui->label->setText("Количество распознаных слов: " + QString::number(words.size()));
    string detectedWord;
    double min_distance = 0;
    double tmp_distance = 0;
    for (auto word: words){
        MFCCProcessor tmp(word, 85, 6000, MEL_COEFS, 44100);
        min_distance = 1e100;
        for (auto el: library){
            tmp_distance = DTWRecogniser::_distance(tmp.getMFCC(), el.second);
            if (tmp_distance < min_distance){
                min_distance = tmp_distance;
                detectedWord = el.first;
            }
        }
        results = results + QString::fromStdString(detectedWord) + '\n';
        ui->label_2->setText(results);
    }
}
