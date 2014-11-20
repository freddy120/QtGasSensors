#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "settingsdialog.h"
#include "tendencias.h"

#include <QMessageBox>
#include "util.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    settings = new SettingsDialog;
    serialPort = new QSerialPort(0);
    tendencias = new Tendencias;
    portName = "";
    ui->lineEdit_com->setText(portName);

    ui->pushButton_connect->setEnabled(true);
    ui->pushButton_disconnect->setEnabled(false);
    ui->pushButton_settings->setEnabled(true);

    initActionsConnections();

    connect(serialPort  , SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(handleError(QSerialPort::SerialPortError)));

    connect(serialPort, SIGNAL(readyRead()), this, SLOT(readData()));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::openSerialPort()
{
    SettingsDialog::Settings p = settings->settings(); //estructura de datos

    serialPort->setPortName(p.name);
    serialPort->setBaudRate(p.baudRate);
    serialPort->setDataBits(p.dataBits);
    serialPort->setParity(p.parity);
    serialPort->setStopBits(p.stopBits);
    serialPort->setFlowControl(p.flowControl);

    if (serialPort->open(QIODevice::ReadWrite)) {
            ui->pushButton_connect->setEnabled(false);
            ui->pushButton_disconnect->setEnabled(true);

            ui->pushButton_settings->setEnabled(false);

            ui->statusBar->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                       .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                                       .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
            portName = p.name;
            ui->lineEdit_com->setText(portName);
    } else {
        QMessageBox::critical(this, tr("Error"), serialPort->errorString());

        ui->statusBar->showMessage(tr("Open error"));
        portName = "";
        ui->lineEdit_com->setText(portName);
    }
}



void MainWindow::closeSerialPort()
{
    serialPort->close();
    ui->pushButton_connect->setEnabled(true);
    ui->pushButton_disconnect->setEnabled(false);
    ui->pushButton_settings->setEnabled(true);
    ui->statusBar->showMessage(tr("Disconnected"));
    portName = "";
    ui->lineEdit_com->setText(portName);
}



void MainWindow::writeData(const QByteArray &data)
{
    serialPort->write(data);
}

void MainWindow::readData()
{
    QByteArray data = serialPort->readAll();


    QString aux = QString(data);
    Stringdata = Stringdata + QString(data); // Acumula los datos

    if (aux.contains("$")){

          DecodeData();

          Stringdata = "";
          //Voltaje.clear();
          //Time.clear();
    }

}

void MainWindow::DecodeData(){


   std::string Stringvolt = Stringdata.toStdString();

   std::stringstream ss;
   ss << Stringvolt;


   std::string line;
   while(!ss.eof()){

       std::getline(ss,line);


       if (line.empty())
           continue;

       else if (line[0] == '@')
           continue;


       // DATOS
       else if (line[0] == '#'){

           std::vector<std::string> tokens = tokenize(line,' ');
           qDebug() << QString::fromStdString(tokens.at(1)) + " " + QString::fromStdString(tokens.at(2))+" " + QString::fromStdString(tokens.at(3))
                      + " " + QString::fromStdString(tokens.at(4))+" " + QString::fromStdString(tokens.at(5))+" " + QString::fromStdString(tokens.at(6));


           VW1 = std::stod(tokens[1]);
           VA1 = std::stod(tokens[2]);
           VW2 = std::stod(tokens[3]);
           VA2 = std::stod(tokens[4]);
           VW3 = std::stod(tokens[5]);
           VA3 = std::stod(tokens[6]);


           ui->lineEdit_WE1->setText(QString::fromStdString(tokens.at(1)) );
           ui->lineEdit_AUX1->setText(QString::fromStdString(tokens.at(2)) );
           ui->lineEdit_WE2->setText(QString::fromStdString(tokens.at(3)) );
           ui->lineEdit_AUX2->setText(QString::fromStdString(tokens.at(4)) );
           ui->lineEdit_WE3->setText(QString::fromStdString(tokens.at(5)) );
           ui->lineEdit_AUX3->setText(QString::fromStdString(tokens.at(6)) );




           if(tendencias->isVisible()){
               yPPm_1.push_back(VW1);
               tendencias->PlotData(yPPm_1,0);

           }




           //printValues();

       }

   }

}


void MainWindow::printValues(){

     //ui->lineEdit_WE1->setText(VW1);

}


void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serialPort->errorString());
        closeSerialPort();
    }

}
//! [8]

void MainWindow::initActionsConnections()
{
    connect(ui->pushButton_connect, SIGNAL(clicked()), this, SLOT(openSerialPort()));
    connect(ui->pushButton_disconnect, SIGNAL(clicked()), this, SLOT(closeSerialPort()));
    connect(ui->pushButton_settings, SIGNAL(clicked()), settings, SLOT(show()));
    connect(ui->actionAbout_Us,SIGNAL(triggered()),this,SLOT(aboutUs()));


    connect(ui->pushButton_tend,SIGNAL(clicked()), tendencias , SLOT(show()));

}



void MainWindow::startProceso(){

    if(serialPort->isOpen()){

    QByteArray data("A\n");

    writeData(data);

    }

}


void MainWindow::aboutUs(){

    QMessageBox::about(this, tr("About GasSensorQt v1.0"),
            tr("<p>The <b>GasSensorQt v1.0</b> IPEN "
               "Instituto Peruano de Energia Nuclear</p>"
               "<p>Author: Freddy Rodrigo Mendoza Ticona </p><p> email: freddy12120@gmail.com</p>"
               "<p>License GNU  GPL  version version 3.0</p> "));



}
