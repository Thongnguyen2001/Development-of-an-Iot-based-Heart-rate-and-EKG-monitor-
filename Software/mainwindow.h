#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <Qstring>
#include <qvector.h>
#include <QDateTime>
#include <QDialog>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QtNetwork>
#include <QtGUI>
#include <QtCore>
#include <QString>
#include <QTimer>
#include <QTextStream>
#include <QFile>
#include <QDatetime>

class QLabel;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void clearValues();
    void tachchuoi(QString data);
private slots:

    void Read_Data( );

    void on_StartButton_clicked();

    void on_StopButton_clicked();

    void on_UserName_push_clicked();

    void d_readData();

    void d_finishedReading();

    void setUserImage();

    void on_ClearButton_clicked();

    void on_SaveButton_clicked();

private:
    //int CalculateHeartRate(float z);

    QString login;
    QString name;
    QString Location;
    int UserID;
    QString stringcat;
    QString chuoi1;
    QDateTime datetime;
    QString timestamp;
    QString encoded;
    Ui::MainWindow *ui;
    QSerialPort* COMPORT;
    //QString Data_From_SerialPort;

    QSerialPortInfo info;

    bool IS_Data_Received = false;
    float z;
    QLabel *label;
    double count;
    int i;
    QPushButton *saveButton;
    QVector<double>x,y;
    QTimer *timer;
    QString filePath;
    //Network access database built with github
    QNetworkAccessManager *netManager;//manage network requests and replies
    QNetworkReply *netReply;//handle replies get from the API
    QNetworkReply *repoReply; // handle replies get from firebase database
    QByteArray dataBuffer;
    QPixmap *img; // contain the image (profile pic)
};
#endif // MAINWINDOW_H
