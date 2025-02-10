#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{


    QApplication a(argc, argv);
    float globalScaleFactor = 1.0;  // 默认为1，表示没有缩放

    MainWindow w;

    w.resize(1080, 600);  // 设置主窗口大小为屏幕分辨率

    // // 创建地平仪（Imu）视图
    // Imu *imuWidget = new Imu(&w);
    // imuWidget->setStyleSheet("background-color: lightblue;"); // 设置背景颜色
    // imuWidget->setGeometry(60, 300, 400, 400); // 设置位置 (x=50, y=50) 和大小 (宽=400, 高=400)

    // 创建电池（Battery）视图
    // Battery *batteryWidget = new Battery(&w);
    // batteryWidget->setStyleSheet("background-color: lightblue;"); // 设置背景颜色
    // batteryWidget->setGeometry(60, 60, 170, 60); // 设置位置 (x=500, y=100) 和大小 (宽=300, 高=600)

    // 显示主窗口
    w.show();

    return a.exec();

}
