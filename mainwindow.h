#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <random>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QSizePolicy>
#include <QSerialPort>
#include <QLabel>
#include <QToolButton>
#include <QToolBar>
#include <QPushButton>
#include <QRadioButton>
#include <QResizeEvent>
#include <QDateTime>
#include <QMovie>

#include"battery.h"
#include "imu.h"
#include "weather.h"
#include"serial.h"
//#include"AircraftData.h"



//#include"serialsimulator.h"




QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void resizeEvent(QResizeEvent *event);
    void setButtonStyle(QPushButton* button);//按钮样式
    void setupBt();//设置按钮


   int globalScaleFactor=0;  // 记录最小widget的字体大小

// signals:
//     void dataUpdated(double pitch, double roll);

private slots:
   void updateNumber() {
       count++;
       label->setText(QString::number(count));
       qDebug()<<"count:"<<count;       // 更新 QLabel 显示的数字
   }

    void sendData(); //模拟写数据
    //void readSerialData(); // 读取串口数据
    void handleSerialError(QSerialPort::SerialPortError error); // 处理串口错误
    void updateTime();
    void updateStatus();
    void updatefontsize(int changedfont); //字体大小和最小窗口同步

    //void updateImu(const AircraftData &data);
    // void setLatitude(double latitude); //设置纬度
    // void setLongitude(double longitude);//设置经度
    // void setGpsAltitude(float gpsAltitude);//设置GPS海拔高度
    // void setRelAltitude(float relAltitude); //设置ASL高度
    //void setTime(const QString &Time); //设置时间


private:
    int count=0;
    Ui::MainWindow *ui;
    QSerialPort *serialPort;
   // SerialSimulator* serialSimulator;
    Imu *imuWidget; // 地平仪视图
    Weather*weatherWidget;
    std::mt19937 randomEngine; // 随机数引擎

    QTimer *timer;  // 定时器，用于每秒更新时间
    QTimer *status_timer;  // 定时器，用于每秒更新status
    Serial *serial; //我定义的串口对象
    // 创建电池（Battery）视图
    Battery *batteryWidget;
    // QLabel *latitudeLabel;  // 用来显示Latitude数值
    // QLabel *longitudeLabel;  // 用来显示Latitude数值
    // QLabel * gpsAltitudeLabel;  // 用来显示 gpsAltitude数值
    // QLabel * relAltitudeLabel;  // 用来显示 relAltitude数值（ASL）
    QLabel * timeLabel;  // 用来显示time

    QLabel * statusLabel;  // 用来显示飞机状态
     QLabel * statusiconLabel;  // 用来显示飞机状态
    //QToolBar *toolBar = addToolBar("Main Toolbar"); //按钮栏
    QPushButton * bt_start;
   QPushButton *bt_down; //降落按钮
    //QRadioButton radio;
    QPushButton *bt_A;
    QPushButton *bt_B;
    QPushButton *bt_C;
    QLabel *label;


};
#endif // MAINWINDOW_H
