#ifndef SERIALSIMULATOR_H
#define SERIALSIMULATOR_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QDebug>
#include <QObject>
#include <random>


class SerialSimulator: public QObject
{
    Q_OBJECT
public:
  explicit SerialSimulator(QObject *parent = nullptr);
    ~SerialSimulator();

signals:
  void dataGenerated(const QString &data); // 声明信号

public slots:
    void generateData();

private:
    QSerialPort *serial;
    QTimer *timer;
     std::mt19937 randomEngine; // 随机数引擎
};

#endif // SERIALSIMULATOR_H
