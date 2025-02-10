#ifndef IMU_H
#define IMU_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QColor>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QPainterPath>

#include <execinfo.h>  // backtrace
#include <cstdio>
#include <cstdlib>

#include <QLabel>
#include <QPushButton>
#include <QResizeEvent>
#include"AircraftData.h"

#include"serial.h"

namespace Ui {
class Imu;
}

class Imu : public QWidget
{
    Q_OBJECT

public:
    explicit Imu(QWidget *parent = nullptr);
    ~Imu();
    void setAngles(int16_t pitchAngle, int16_t rollAngle, int16_t yawAngle); //更新roll等
    void paintEvent(QPaintEvent *event);
    void setData(double receivelatitude,double receivelongitude,float receivegpsAltitude,float receiverelAltitude); //更新aititude等
    void setLabelsAlignment(Qt::Alignment alignment); //居中label
    void resizeEvent(QResizeEvent *event);
    void drawScale(QPainter &painter);
    void drawHorizonLine(QPainter &painter, int centerX, int centerY, int dashboardRadius, int roll);
    //void generateBackgroundPixmap(); // 生成背景

    void printStackTrace();

public slots:
    void update();
    void setImudata(const AircraftData &data);


signals:
    void dataUpdated(double pitch, double roll);

private:
    Ui::Imu *ui;
    int16_t pitch; // 俯仰角
    int16_t roll;  // 横滚角
    int16_t yaw; //偏航
    double latitude;//纬度
    double longitude;//经度
    float gpsAltitude; //GPS海拔
    float relAltitude;//ASL

    float dashboardRadius;
    float fontSize;

    bool dataReceived=false;

     int count1=0;
     int count=0;

    // int windowWidth;
    // int windowHeight;

    // // 获取中心点
    // int centerX ;
    // int centerY ;


    Serial *serial; //串口对象
    QTimer *timer;
    QLabel *latitudeLabel;  // 用来显示Latitude数值
    QLabel *longitudeLabel;  // 用来显示Latitude数值
    QLabel * gpsAltitudeLabel;  // 用来显示 gpsAltitude数值
    QLabel * relAltitudeLabel;  // 用来显示 relAltitude数值（ASL）
    QLabel *pitchLabel;  // 用来显示pitch数值
    QLabel *rollLabel;  // 用来显示roll数值
    QLabel * yawLabel;  // 用来显示yaw数值

    // QPixmap backgroundPixmap; // 预生成背景
    // QPixmap circularBackground; // 预生成背景

};

#endif // IMU_H
