#include "weather.h"

Weather::Weather(QWidget *parent)
    : QWidget(parent),
    networkManager(new QNetworkAccessManager(this)),
    apiKey("7435590723d6d0fcbb0ea1e5a9594165"),  // 替换为你自己的 API 密钥
    city("深圳")          // 替换为你想查询的城市
{

    weatherIconLabel = new QLabel(this);
    temperatureLabel = new QLabel(this);
    humidityLabel = new QLabel(this);
    windLabel = new QLabel(this);
    windPowerLabel = new QLabel(this);
    weatherDescriptionLabel = new QLabel(this);

    setLabelsAlignment(Qt::AlignCenter);  // 将所有的 QLabel 文本设置为居中

     // weatherIconLabel->setStyleSheet("color: black;" "    border: 2px solid #bbb;");
     // temperatureLabel->setStyleSheet("color: black;" "    border: 2px solid #bbb;");
     // humidityLabel->setStyleSheet("color: black;" "    border: 2px solid #bbb;");
     // windLabel->setStyleSheet("color: black;" "    border: 2px solid #bbb;");
     // //weatherIconLabel->setStyleSheet("color: black;");
     // weatherDescriptionLabel->setStyleSheet("color: black;" "    border: 2px solid #bbb;");
     // windPowerLabel->setStyleSheet("color: black;" "    border: 2px solid #bbb;");
     weatherIconLabel->setStyleSheet("color: black;" );
     temperatureLabel->setStyleSheet("color: black;" );
     humidityLabel->setStyleSheet("color: black;" );
     windLabel->setStyleSheet("color: black;" );
     //weatherIconLabel->setStyleSheet("color: black;");
     weatherDescriptionLabel->setStyleSheet("color: black;");
     windPowerLabel->setStyleSheet("color: black;" );
    // this->setStyleSheet("QWidget { background-color: lightblue; }");

    //setFixedSize(300, 300);  // 设置天气小组件的固定大小，之后可以根据窗口大小进行动态调整
    //确保你的 QNetworkAccessManager (networkManager) 是正确初始化并且已经连接了 finished 信号。例如，在类的构造函数中初始化 networkManager
    connect(networkManager, &QNetworkAccessManager::finished,this, &Weather::onWeatherDataReceived);
    // 每分钟获取一次天气数据
    // QTimer *timer = new QTimer(this);
    // connect(timer, &QTimer::timeout, this, &Weather::fetchWeatherData);
    // timer->start(540000);

    fetchWeatherData();
}

void Weather::fetchWeatherData()
{
    // 创建请求 URL
    QUrl url("http://apis.juhe.cn/simpleWeather/query");

    // 使用 URL 参数
    QUrlQuery query;
    query.addQueryItem("city", city);       // 传入查询的城市
    query.addQueryItem("key", apiKey);      // 传入 API Key
    url.setQuery(query);

    // 创建请求
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");  // 设置请求头
    // 打印发送的 URL
            qDebug() << "Sending request to: " << request.url().toString();
    // 发起 GET 请求
   // networkManager->get(request);
}


void Weather::onWeatherDataReceived(QNetworkReply *reply)
{
    qDebug() << "connect！";
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Weather API error:" << reply->errorString();
        reply->deleteLater();
        return;
    }

    QByteArray response = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
    QJsonObject weatherData = jsonDoc.object();

    // 输出收到的原始 JSON 数据
    qDebug() << "Received Weather Data:" << QString(response);

    if (weatherData.contains("result")) {
        // 输出解析后的数据
        QJsonObject realtime = weatherData["result"].toObject()["realtime"].toObject();
        QString temperature = realtime["temperature"].toString();    // 当前温度
        QString humidity = realtime["humidity"].toString();                // 湿度
        QString windDirect = realtime["direct"].toString();         // 风向
        QString windPower = realtime["power"].toString();           // 风力
        wid = realtime["wid"].toString();                   // 天气状况代码

        temperatureLabel->setText(QString("%1°C").arg(temperature));
        humidityLabel->setText(QString("湿 ～:%1%").arg(humidity));
        windLabel->setText(QString("%1").arg(windDirect));
        // QString t="111";
        // QString q="221";
        windPowerLabel->setText(QString("%1风").arg(windPower));
        weatherDescriptionLabel->setText(QString("%1").arg(getWeatherInfoByWid(wid)));




        qDebug() << "温度:" << temperature << "°C";
        qDebug() << "湿度:" << humidity << "%";
        qDebug() << "风向:" << windDirect;
        qDebug() << "风力:" << windPower;
        qDebug() << "天气状况:" << getWeatherInfoByWid(wid);

        // 设置天气图标（示例：你可以替换为实际图标的 URL）
        // QPixmap weatherIcon(QString("http://openweathermap.org/img/wn/%1@2x.png").arg(wid));
        // weatherIconLabel->setPixmap(weatherIcon.scaled(40, 40, Qt::KeepAspectRatio));
        // 设置天气图标,根据天气状况改变
        QString weatherstatus=getWeatherInfoByWid(wid);
        qDebug()<<"weatherstatus:"<<weatherstatus;
        updateWeatherIcon(weatherstatus);
        //updateWeatherIcon("雷阵雨");
        // 强制刷新 UI
        QCoreApplication::processEvents();
        //updateWeatherUI(weatherData["result"].toObject());
    } else {
        qDebug() << "Error: No result found!";
    }

    reply->deleteLater();
}
// void Weather::onWeatherDataReceived(QNetworkReply *reply)
// {
//     if (reply->error() != QNetworkReply::NoError) {
//         qDebug() << "Weather API error:" << reply->errorString();
//         reply->deleteLater();
//         return;
//     }

//     QByteArray response = reply->readAll();
//     QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
//     QJsonObject weatherData = jsonDoc.object();

//     if (weatherData.contains("result")) {
//         updateWeatherUI(weatherData["result"].toObject());
//     } else {
//         qDebug() << "Error: No result found!";
//     }

//     reply->deleteLater();
// }


// void Weather::updateWeatherUI(const QJsonObject &weatherData)
// {
//     // // 获取当前实时天气
//     // QJsonObject realtime = weatherData["result"].toObject()["realtime"].toObject();
//     // QString temperature = realtime["temperature"].toString();    // 当前温度
//     // QString humidity = realtime["humidity"].toString();                // 湿度
//     // QString windDirect = realtime["direct"].toString();         // 风向
//     // QString windPower = realtime["power"].toString();           // 风力
//     // QString wid = realtime["wid"].toString();                   // 天气状况代码
//     // // 获取天气图标的天气描述
//     // QString weatherDescription = getWeatherInfoByWid(wid);

//     // 更新天气信息
//     temperatureLabel->setText(QString("温度: %1°C").arg(temperature));
//     humidityLabel->setText(QString("湿度: %1%").arg(humidity));
//     windLabel->setText(QString("风向: %1").arg(windDirect));
//     windPowerLabel->setText(QString("风力: %1").arg(windPower));
//     // 更新天气状况
//     //weatherDescriptionLabel->setText(weatherDescription);
//     weatherDescriptionLabel->setText(QString("天气状况: %1").arg(getWeatherInfoByWid(wid)));
//     // 设置天气图标（示例：你可以替换为实际图标的 URL）
//     // QPixmap weatherIcon(QString("http://openweathermap.org/img/wn/%1@2x.png").arg(wid));
//     // weatherIconLabel->setPixmap(weatherIcon.scaled(40, 40, Qt::KeepAspectRatio));


// }

QString Weather::getWeatherInfoByWid(const QString &wid)
{
    // 根据wid值返回对应的天气信息
    if (wid == "00") return "晴";
    if (wid == "01") return "多云";
    if (wid == "02") return "阴";
    if (wid == "03") return "阵雨";
    if (wid == "04") return "雷阵雨";
    if (wid == "05") return "雷阵雨伴有冰雹";
    if (wid == "06") return "雨夹雪";
    if (wid == "07") return "小雨";
    if (wid == "08") return "中雨";
    if (wid == "09") return "大雨";
    if (wid == "10") return "暴雨";
    if (wid == "11") return "大暴雨";
    if (wid == "12") return "特大暴雨";
    if (wid == "13") return "阵雪";
    if (wid == "14") return "小雪";
    if (wid == "15") return "中雪";
    if (wid == "16") return "大雪";
    if (wid == "17") return "暴雪";
    if (wid == "18") return "雾";
    if (wid == "19") return "冻雨";
    if (wid == "20") return "沙尘暴";
    if (wid == "21") return "小到中雨";
    if (wid == "22") return "中到大雨";
    if (wid == "23") return "大到暴雨";
    if (wid == "24") return "暴雨到大暴雨";
    if (wid == "25") return "大暴雨到特大暴雨";
    if (wid == "26") return "小到中雪";
    if (wid == "27") return "中到大雪";
    if (wid == "28") return "大到暴雪";
    if (wid == "29") return "浮尘";
    if (wid == "30") return "扬沙";
    if (wid == "31") return "强沙尘暴";
    if (wid == "53") return "霾";

    return "未知";
}
void Weather::resizeEvent(QResizeEvent *event)
{
    // 获取新的窗口大小
    int width = event->size().width();
    int height = event->size().height();
    int commonHeight = height * 1;  // 比如设置为高度的 70%

    // 根据窗口的大小动态调整控件的位置和大小
    weatherIconLabel->resize(width * 0.06,commonHeight);
    weatherIconLabel->move(0, 0);  // 放置在左上角


    temperatureLabel->resize(width * 0.08, commonHeight);
    temperatureLabel->move(weatherIconLabel->x() + weatherIconLabel->width(), weatherIconLabel->y());  // 在图标右边显示

    humidityLabel->resize(width * 0.08, commonHeight);
    humidityLabel->move(temperatureLabel->x() + temperatureLabel->width() , temperatureLabel->y());  // 在温度下方显示

    windLabel->resize(width * 0.08, commonHeight);
    windLabel->move(humidityLabel->x() + humidityLabel->width(), humidityLabel->y());  // 在湿度下方显示

    windPowerLabel->resize(width * 0.08, commonHeight);
    windPowerLabel->move(windLabel->x() + windLabel->width(), windLabel->y());  // 在风速下方显示

    weatherDescriptionLabel->resize(width * 0.08,commonHeight);
    weatherDescriptionLabel->move(windPowerLabel->x() + windPowerLabel->width(), windPowerLabel->y());  // 在风速下方显示

    QWidget::resizeEvent(event);  // 调用基类的 resizeEvent
}

void Weather::updatefontsize(int changedfont) //字体大小和最小窗口同步
{
    int globalScaleFactor=changedfont;
    qDebug()<<"globalweatherScaleFactor:"<<globalScaleFactor;
    QFont labelFont =  temperatureLabel->font(); // 获取当前字体
    labelFont.setPointSize(globalScaleFactor);

    temperatureLabel->setFont(labelFont);  // 应用字体
    humidityLabel->setFont(labelFont);  // 应用字体
    windLabel->setFont(labelFont);  // 应用字体
    windPowerLabel->setFont(labelFont);  // 应用字体
    weatherDescriptionLabel->setFont(labelFont);  // 应用字体

}

void Weather::updateWeatherIcon(const QString &wid)
{
    qDebug() << "wid:" << wid;
    QMovie *movie = new QMovie();

    if (wid == "晴") {
        movie->setFileName(":/sun.gif");
    } else if (wid == "多云") {
        movie->setFileName(":/clouds.gif");
    } else if (wid == "阴") {
        movie->setFileName(":/cloudy.gif");
    } else if (wid=="雨") {
        movie->setFileName(":/sun_rain.gif");
    } else if (wid == "雷阵雨") {
        movie->setFileName(":/storm.gif");
    } else if (wid=="雪") {
        movie->setFileName(":/snow.gif");
    } else if (wid == "雾") {
        movie->setFileName(":/icons/fog.gif");
    } else if (wid == "霾") {
        movie->setFileName(":/icons/haze.gif");
    } else {
        movie->setFileName(":/icons/default.gif");
    }

    // 确保 QLabel 启用自动缩放内容
    weatherIconLabel->setScaledContents(true);
    //
    //weatherIconLabel->setPixmap(icon.scaled(weatherIconLabel->size(), Qt::KeepAspectRatio));

    //weatherIconLabel->setSmoothTransformation(true);
    //weatherIconLabel->resize(movie->currentFrameRect().size());


    weatherIconLabel->setMovie(movie);
    movie->start();
}


// void Weather::updateWeatherIcon(const QString &wid)
// {
//     // 使用getWeatherInfoByWid函数获取天气描述
//     QString weatherDescription = getWeatherInfoByWid(wid);
//     QPixmap iconPixmap;

//     // 根据天气描述选择合适的图标
//     if (weatherDescription == "晴") {
//         iconPixmap.load(":/icons/sunny.png");
//     } else if (weatherDescription == "多云") {
//         iconPixmap.load(":/icons/cloudy.png");
//     } else if (weatherDescription == "阴") {
//         iconPixmap.load(":/icons/overcast.png");
//     } else if (weatherDescription == "阵雨" || weatherDescription == "小雨" || weatherDescription == "中雨" || weatherDescription == "大雨" || weatherDescription == "暴雨") {
//         iconPixmap.load(":/sun_rain.gif");
//     } else if (weatherDescription == "雷阵雨") {
//         iconPixmap.load(":/storm.gif");
//     } else if (weatherDescription == "小雪" || weatherDescription == "中雪" || weatherDescription == "大雪") {
//         iconPixmap.load(":/snow.gif");
//     } else if (weatherDescription == "雾") {
//         iconPixmap.load(":/icons/fog.png");
//     } else if (weatherDescription == "霾") {
//         iconPixmap.load(":/icons/haze.png");
//     } else {
//         iconPixmap.load(":/icons/default.png");  // 默认图标
//     }

//     // 将图标设置到天气描述的标签上
//     weatherDescriptionLabel->setPixmap(iconPixmap);
// }


void Weather::setLabelsAlignment(Qt::Alignment alignment)
{
    temperatureLabel->setAlignment(alignment);
    humidityLabel->setAlignment(alignment);
    windLabel->setAlignment(alignment);
    windPowerLabel->setAlignment(alignment);
    weatherDescriptionLabel->setAlignment(alignment);

}

Weather::~Weather()
{
    delete networkManager;
}
