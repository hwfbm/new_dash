#ifndef WEATHER_H
#define WEATHER_H
#include <QWidget>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QPixmap>
#include<QTimer>
#include <QPaintEvent>
#include<QUrlQuery>
#include<QString>
#include <QMovie>       // 用于加载和播放GIF动画

#include"battery.h"

class Weather: public QWidget
{
    Q_OBJECT

public:
    explicit Weather(QWidget *parent = nullptr);
    ~Weather();
    void resizeEvent(QResizeEvent *event);
    void updateWeatherIcon(const QString &wid);
    void setLabelsAlignment(Qt::Alignment alignment); //居中

public slots:
    void updatefontsize(int changedfont); //字体大小和最小窗口同步
private slots:
    void onWeatherDataReceived(QNetworkReply *reply);


private:

    QLabel *weatherIconLabel;
    QLabel *temperatureLabel;
    QLabel *humidityLabel;
    QLabel *windLabel;
    QLabel *windPowerLabel;
    QLabel *weatherDescriptionLabel;//天气状况
    QNetworkAccessManager *networkManager;
    QString apiKey;
    QString city;

    QString wid;
    void fetchWeatherData();
    //void updateWeatherUI(const QJsonObject &weatherData);
    QString getWeatherInfoByWid(const QString &wid);  // 根据wid代码获取天气信息


};

#endif // WEATHER_H
