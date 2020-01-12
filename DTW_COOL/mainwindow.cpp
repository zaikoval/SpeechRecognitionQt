#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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


//    if(!default_deviceName.isEmpty())
//            {
//                auto preferred_format = info.preferredFormat();
//                QString codec = preferred_format.codec();
//                int sampleRate = preferred_format.sampleRate();
//                int sampleSize = preferred_format.sampleSize();
//                int channelCount = preferred_format.channelCount();
//                int sampleType = preferred_format.sampleType();
//                int byteOrder =  preferred_format.byteOrder();
//                qDebug() << "codec:" << codec.toLatin1() << "sampleRate :" << sampleRate << "sampleSize:" << sampleSize << "channel Count:" << channelCount << "sample type:" <<sampleType
//                    << "byteOrder:" << byteOrder;
//            }

    if (!info.isFormatSupported(format)) {
        qDebug()<<"default format not supported try to use nearest";
        format = info.nearestFormat(format);
    }

    audio = new QAudioInput(format, this);
    audio->start(&buffer);
}

void MainWindow::on_pushButton_2_clicked()
{
    audio->stop();
    buffer.close();
    delete audio;
    buffer.open(QBuffer::ReadOnly);
//    auto bytes = buffer.data();
    buffer.close();
    std::cout<<"cool"<<std::endl;

}
