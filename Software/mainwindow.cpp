#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "qaxobject.h"
#include "qdebug.h"

#include <QMessageBox>
#include <QObject>
#include <QPixmap>
#include <QtDebug>
#include <QJsonDocument>
#include <QApplication>
#include <QString>
#include <QList>
#include <QtMath>
#include <QFileDialog>
#include <QMessageBox>
#include <QDataStream>
#define SCALE_FACTOR 100

int count = 0;
bool state;
float ecgValue;
int BPM;

QString chuoi;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,count(0.0),
    i(0),z(0.0)
{


    ui->setupUi(this);

    QPixmap IU("E:\\QT_testplot\\logoBME.png");
    ui->logoIUlabel->setPixmap(IU.scaled(100,100,Qt::KeepAspectRatio));
    QPixmap BME("E:\\QT_testplot\\logoIU.png");
    ui->logoBMElabel->setPixmap(BME.scaled(100,100,Qt::KeepAspectRatio));
    QPixmap heart("E:\\QT_testplot\\heartbeat.png");
    ui->heartrhythmlabel->setPixmap(heart.scaled(40,40,Qt::KeepAspectRatio));

    timer = new QTimer();
    //image of user
    img = new QPixmap();
    //Network manager and reply initialize
    netManager = new QNetworkAccessManager();
    //Save button
    saveButton = new QPushButton();
    //PORT initialize
    COMPORT = new QSerialPort();
    //REFERENCE TO CSV PATH
    QString filePath = "E:\\QT_testplot\\Patient";
    qDebug() << "Trying to open file at path:" << filePath;
    //DATE TIME CONFIGURATION
    datetime = QDateTime::currentDateTime();
    timestamp = datetime.toString("ddd MMMM d yy h:m:s ap");
    ui->DateTimeLineEdit->setText(datetime.toString("ddd MMMM d yy h:m:s ap"));

    QList<QSerialPortInfo> ports =info.availablePorts();
    QList<QString> stringPorts;

    for(int i=0; i<ports.size(); i++)
    {
        stringPorts.append(ports.at(i).portName());
    }
    ui->COM->addItems(stringPorts);

    //SIGNAL & SLOTS
    connect(ui->StartButton,&QPushButton::clicked,this,&MainWindow::on_StartButton_clicked);
    connect(ui->StopButton,&QPushButton::clicked,this,&MainWindow::on_StopButton_clicked);
    connect(ui->ClearButton,&QPushButton::clicked,this,&MainWindow::on_ClearButton_clicked);

    if(COMPORT->isOpen())
    {
        qDebug()<<"Serial port is connected.";

    }
    else
    {
        qDebug()<<"Choose COM PORT for monitoring: ";
        qDebug() << COMPORT->error();
    }

    //set up qcustom to plot
    ui->customplot->addGraph();
    ui->customplot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    ui->customplot->graph(0)->setLineStyle(QCPGraph::lsLine);


    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    QSharedPointer<QCPAxisTicker> count(new QCPAxisTicker);
    timeTicker->setTimeFormat("%h:%m:%s");
    ui->customplot->xAxis->setTicker(timeTicker);
    //ui->customplot->axisRect()->setupFullAxesBox();
    ui->customplot->yAxis->setRange(0, 1000);

    /* User interactions Drag and Zoom are allowed only on X axis, Y is fixed manually by UI control */
    ui->customplot->setInteraction (QCP::iRangeDrag, true);
    //ui->plot->setInteraction (QCP::iRangeZoom, true);
    ui->customplot->setInteraction (QCP::iSelectPlottables, true);
    ui->customplot->setInteraction (QCP::iSelectLegend, true);
    ui->customplot->axisRect()->setRangeDrag (Qt::Horizontal);
    ui->customplot->axisRect()->setRangeZoom (Qt::Horizontal);

    connect(ui->customplot->xAxis,SIGNAL(rangeChanged(QCPRange)),ui->customplot->xAxis2,SLOT(setRange(QCPRange)));
    connect(ui->customplot->yAxis,SIGNAL(rangeChanged(QCPRange)),ui->customplot->yAxis2,SLOT(setRange(QCPRange)));

    connect(saveButton,SIGNAL(clicked()),this,SLOT(on_SaveButton_clicked()));
}

MainWindow::~MainWindow()
{
    if(COMPORT->isOpen())
    {
        COMPORT->close();
    }
    delete ui;
}


/*
 * ECG Signal processing and plotting real-time data
*/

void MainWindow::Read_Data()
{
   QByteArray  data_to_plot;
   QString data_receive;

   if(state == true){
     if(COMPORT->isOpen()  && COMPORT->bytesAvailable()){

            data_to_plot +=COMPORT->readAll();
            data_receive = data_to_plot;
            tachchuoi(data_receive);

        }

    }
}

void MainWindow::on_StartButton_clicked()
{
    //show available PORT name
    QString portName = ui->COM->currentText();
    COMPORT->setPortName(portName);
    COMPORT->setBaudRate(QSerialPort::Baud9600);
    COMPORT->setParity(QSerialPort::Parity::NoParity);
    COMPORT->setDataBits(QSerialPort::DataBits::Data8);
    COMPORT->setStopBits(QSerialPort::StopBits::OneStop);
    COMPORT->setFlowControl(QSerialPort::FlowControl::NoFlowControl);


    if(COMPORT->open(QIODevice::ReadWrite))
    {
        connect(COMPORT,&QSerialPort::readyRead,this,&MainWindow::Read_Data);
        connect(timer,SIGNAL(timeout()),this,SLOT(Read_Data()));
        timer->start(5000); // repeatedly update plot

        state=true;
        ui->StartButton->setText("STARTING");
        qDebug()<<"Serial port opened.";
    }else
    {
        qDebug()<<"Failed to open serialport:"<<COMPORT->errorString();
    }
 }



void MainWindow::on_StopButton_clicked()
{


    if(COMPORT->isOpen()){
        COMPORT->close();
    }
        qDebug()<<"COMPORT is closed";
        state = false;

        ui->StopButton->setText("PAUSED");

        // qDebug()<<"x: "<<x<<"y: "<<y;

        //ui->customplot->graph(0)->data()->clear();
        ui->customplot->graph(0)->setData(x,y);
        ui->customplot->replot();
        ui->customplot->update();

}

void MainWindow::on_ClearButton_clicked()
{
    ui->StartButton->setText("START");
    ui->StopButton->setText("STOP");

    x.clear();
    y.clear();

    ui->customplot->graph(0)->setData(x,y);
    ui->customplot->replot();
    ui->customplot->update();

    clearValues();

}

void MainWindow::tachchuoi(QString data)
{
    stringcat = data;
    chuoi1;
    int a,moc;
    a = 1;
    qDebug()<< a;

        if(a==1)
         {
            for(int i=0;i<stringcat.length();i++)
            {
                if(stringcat.at(i) == ",")
                {
                    moc = i;
                    i=stringcat.length();
                }
             }
         }
        chuoi1 = stringcat;
        chuoi1.remove(moc, stringcat.length());
        stringcat.remove(0,moc + 1);//Tach gia tri thanh truot 1 ra chuoi1
        stringcat.remove(stringcat.length()-2,stringcat.length());

        z=chuoi1.toFloat();
       //qDebug()<<"Data:"<<chuoi1;

        qDebug()<<"BPM: "<<stringcat;
        qDebug()<<"Data received: "<<chuoi1;


        x.append(count);
        y.append(z);
        count++;

        // Adjust x-axis range to keep the last N data points visible
        int n_visible_points = 100; // Adjust this value as needed
        double min_x = x.last() - n_visible_points;
        double max_x = x.last();


        ui->customplot->graph(0)->addData(x,y,true);
        ui->customplot->xAxis->setRange(min_x, max_x);
        ui->customplot->graph(0)->setData(x,y);
        ui->customplot->graph(0)->rescaleValueAxis(false,true);
        ui->customplot->replot();
        ui->customplot->update();

        ui->pulse_LCD->display(stringcat);


}


/*
 * Network for cloud database
 *
*/
void MainWindow::on_UserName_push_clicked()
{
    auto username = QInputDialog::getText(this,"Username","Enter your Username");
    if(!username.isEmpty())
    {
        clearValues();
        QNetworkRequest req{QUrl(QString("https://api.github.com/users/%1").arg(username))};
        QNetworkRequest repoReq{QUrl(QString("https://api.github.com/users/%1/repos").arg(username))};
        netReply = netManager->get(req);
        connect(netReply,&QNetworkReply::readyRead,this,&MainWindow::d_readData);
        connect(netReply,&QNetworkReply::finished,this,&MainWindow::d_finishedReading);
    }
}

//Read data custom plot
void MainWindow::d_readData()
{
    dataBuffer.append(netReply->readAll());
}

void MainWindow::d_finishedReading()
{
    if( !netReply || netReply->error() != QNetworkReply::NoError)
    {
        qDebug()<<"Error: "<<netReply->errorString();
        QMessageBox::warning(this,"Error",QString("Request[Error]: %1"));
        return;
    }
    else
    {
        //CONVERT DATA  FROM A JSON DOC  TO JSON OBJECT
        QJsonObject  userJsonInfo = QJsonDocument::fromJson(dataBuffer).object();

        //SET USERNAME - LOGIN NAME
        login = userJsonInfo.value("login").toString();
        ui->UserName_lineEdit->setText(login);

        //SET DISPLAY NAME - PATIENT NAME
        name = userJsonInfo.value("name").toString();
        ui->Name_lineEdit->setText(name);
        //SET LOCATION - LOCATION OF PATIENT
        Location = userJsonInfo.value("location").toString();
        ui->Location_lineEdit->setText(Location);

        //SET USER ID - ID OF PATIENT
        UserID = userJsonInfo.value("id").toInt();
        ui->UserID_lineEdit->setText(QString::number(UserID));

        //SET PICTURE
        auto picLink = userJsonInfo.value("avatar_url").toString();
        QNetworkRequest link{QUrl(picLink)}; // create object to request a url to database
        netReply = netManager ->get(link); // perform HTTP GET to retrieve data from database
        connect(netReply,&QNetworkReply::finished,this,&MainWindow::setUserImage);
        dataBuffer.clear();
    }
}


void MainWindow::setUserImage()
{
    img->loadFromData(netReply->readAll());
    QPixmap temp = img->scaled(ui->pic_label->size());
    ui->pic_label->setPixmap(temp);
}

void MainWindow::on_SaveButton_clicked()
{

    QString filePath = QFileDialog::getSaveFileName(this,
            tr("Save Patient Information"),"E:\\QT_testplot\\Patient",
            tr("(*.csv);;All Files(*)"));

    QString filename("E:\\QT_testplot\\ECG.png");
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        qDebug()<<file.errorString();
    }else{
        ui->customplot->savePng(filename);

        QFile* savedImage = new QFile("ECG.png");
        savedImage->open(QIODevice::ReadOnly);
        QByteArray csv = savedImage->readAll();
        encoded = QString(csv.toBase64());
    }
    if(filePath.isEmpty())
        return;
    else
    {
        QFile CSVFile(filePath);
        if(!CSVFile.open(QIODevice::ReadWrite | QIODevice::Append)){
            qDebug() << "Failed to open the file for saving.";
            return;
        }
        else
        {
            QTextStream Stream(&CSVFile);
            Stream<<login<<","<<UserID<<","<<name<<","<<Location<<","<<timestamp<<","<<stringcat<<","<<encoded<<"\n";
            qDebug()<<"Successfully save to: "<<filePath;
        }
        CSVFile.close();
        }
}


//finish reading custom plot

void MainWindow::clearValues()
{
    ui->UserName_lineEdit->clear();
    ui->Name_lineEdit->clear();
    ui->Location_lineEdit->clear();
    ui->UserID_lineEdit->clear();
    ui->pic_label->clear();
}











