#ifndef BATTERY_H
#define BATTERY_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QPaintEvent>
#include <QTimer>
#include <QWidget>
#include <QProcess>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QProgressBar>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QLabel>



namespace Ui {
class Battery;
}

class Battery : public QWidget
{
    Q_OBJECT

public:
    explicit Battery(QWidget *parent = nullptr);
    ~Battery();
    //void paintEvent(QPaintEvent *event);
    //void update();
    //void getBatteryLevel();
    int parseBatteryLevel(const QString &output);
    void resizeEvent(QResizeEvent *event);

signals:
    void fontchanged(int changedfont);

private slots:
    void updateBatteryLevel();
private:
    Ui::Battery *ui;
    int batteryLevel; // 电量百分比
    QProgressBar *batteryProgressBar;
    QLabel *timeLabel;
    QLabel *flyabletimeLabel;

};

#endif // BATTERY_H
