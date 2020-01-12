#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAudioInput>
#include <QBuffer>
#include <QtDebug>
#include <vector>
#include <mfccprocessor.h>
#define MEL_COEFS 13


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QAudioInput *audio;
    QByteArray array;
    QBuffer buffer;
    std::vector<int16_t> buffarr;
    std::vector<double> data;
    map<string, vector<vector<double>>> library;

};
#endif // MAINWINDOW_H
