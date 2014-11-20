#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort>

class SettingsDialog;
class Tendencias;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void DecodeData();
    void printValues();

private slots:

    void openSerialPort();
    void closeSerialPort();

    void writeData(const QByteArray &data);
    void readData();

    void handleError(QSerialPort::SerialPortError error);
    void startProceso();

    void  aboutUs();

private:
    void initActionsConnections();

    Ui::MainWindow *ui;

    // NO2
    QVector<double> WE1;
    QVector<double> AUX1;

    // SO2
    QVector<double> WE2;
    QVector<double> AUX2;

    // NO
    QVector<double> WE3;
    QVector<double> AUX3;

    // H2S
    QVector<double> WE4;
    QVector<double> AUX4;

    // O3
    QVector<double> WE5;
    QVector<double> AUX5;

    // CO
    QVector<double> WE6;
    QVector<double> AUX6;


    double  VW1,VW2,VW3,VW4,VW5,VW6;
    double  VA1,VA2,VA3,VA4,VA5,VA6;


    SettingsDialog *settings;
    QSerialPort *serialPort;
    Tendencias *tendencias;
    QString portName;
    QString Data;

    QString Stringdata ;

    QVector <double> yPPm_1;

};

#endif // MAINWINDOW_H
