#include "serialsimulator.h"
// 初始化随机数引擎
SerialSimulator::SerialSimulator(QObject *parent)
    : QObject(parent), serial(new QSerialPort(this)), timer(new QTimer(this)), randomEngine(std::random_device{}())
{
    // 配置虚拟串口
    serial->setPortName("/dev/tty.usbserial-14310"); // 设置虚拟串口名称（Windows 示例）
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);


    if (!serial->open(QIODevice:: ReadWrite)) {
        qDebug() << "无法打开发送端串口！：" << serial->errorString();
    }
    // 模拟发送数据
    connect(timer, &QTimer::timeout, this,&SerialSimulator::generateData);
    timer->start(100); // 每100ms发送一次数据
}


void SerialSimulator::generateData() {
    // 生成随机数据
    std::uniform_real_distribution<double> distribution(-180.0, 180.0);
    double pitch = distribution(randomEngine);
    double roll = distribution(randomEngine);

    // 构造数据字符串
   // QString data = QString("pitch:%1,roll:%2\n").arg(pitch).arg(roll); // 添加换行符
  //  qDebug() << "Generated data:" << data;
    QString data="test";
    // 写入串口
    serial->write(data.toUtf8());
}

SerialSimulator::~SerialSimulator()
{
    if (serial->isOpen())
        serial->close();
}
