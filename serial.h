#ifndef SERIAL_H
#define SERIAL_H
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <QtMath>
#include <QString>
#include <QSettings>
#include"AircraftData.h"



class Serial: public QObject
{
    Q_OBJECT

public:

    explicit Serial(QObject *parent = nullptr);
    ~Serial();


    //QList<Data> parseDataBuffer();
    AircraftData parseAircraftData(const QByteArray &data);
private:
    QByteArray buffer;
    QSerialPort *serialPort;
    //AircraftData aircraft;


signals:
    void dataUpdated(const AircraftData &data); //更新imu信号
    //void gpsTimeudeUpdated(const QString& Time);  //更新时间

    //void dataUpdated(double latitude);  // 定义latitude信号、
    void dataReceived(const QByteArray &data);//给imu


public slots:
    void onDataReceived();


};

#endif // SERIAL_H
