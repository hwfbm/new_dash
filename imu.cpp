#include "imu.h"
#include "ui_imu.h"

Imu::Imu(QWidget *parent)
    : QWidget(parent),
    latitudeLabel(new  QLabel(this)),
    longitudeLabel(new  QLabel(this)),
    gpsAltitudeLabel(new  QLabel(this)),
    relAltitudeLabel(new  QLabel(this)),
    pitchLabel(new  QLabel(this)),
    rollLabel(new  QLabel(this)),
    yawLabel(new  QLabel(this)),
    serial(new Serial),
    ui(new Ui::Imu)
{
    ui->setupUi(this);
    //setAttribute(Qt::WA_OpaquePaintEvent);


    setLabelsAlignment(Qt::AlignCenter);  // 将所有的 QLabel 文本设置为居中

    latitudeLabel->setStyleSheet("QLabel { font-size: 15px; color: rgba(0,0,0,0.8); }");
    longitudeLabel->setStyleSheet("QLabel { font-size: 15px;  color: rgba(0,0,0,0.8);  }");
    gpsAltitudeLabel->setStyleSheet("QLabel { font-size: 15px;  color: rgba(0,0,0,0.8);  }");
    relAltitudeLabel->setStyleSheet("QLabel { font-size: 15px;  color: rgba(0,0,0,0.8);  }");

    pitchLabel->setStyleSheet("QLabel { font-size: 15px; color: rgba(0,0,0,0.8); }");
    rollLabel->setStyleSheet("QLabel { font-size: 15px;  color: rgba(0,0,0,0.8);  }");
    yawLabel->setStyleSheet("QLabel { font-size: 15px;  color: rgba(0,0,0,0.8);  }");



    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Imu::update); //刷新视图
    timer->start(1000); // 每30ms刷新一次



    //connect(serial, &Serial::dataUpdated, this, &Imu::setAngles);  //获取roll等更新imu

    //connect(serial, &Serial::dataUpdated, this, &Imu::setImudata); //连接信号更新imu数据





connect(serial, &Serial::dataUpdated, this, [this](const AircraftData &data) {
        //dataReceived=true;
        qDebug() << "Signal received, updating IMU data";
        setImudata(data);  // 调用 setImudata 来更新数据
    });
}

void Imu::setAngles(int16_t pitchAngle, int16_t rollAngle, int16_t yawAngle) {
    pitch = pitchAngle;
    roll = rollAngle;
    yaw = yawAngle;
    qDebug() << "更新 IMU: pitch=" << pitch << ", roll=" << roll<< ", yaw=" << yaw;
    pitchLabel->setText(QString("俯仰: %1").arg(pitch));
    rollLabel->setText(QString("横滚: %1").arg(roll));
    yawLabel->setText(QString("偏航: %1 ").arg(yaw));

    update();
}
void Imu::setData(double receivelatitude,double receivelongitude,float receivegpsAltitude,float receiverelAltitude) {
    // QFont bt_font;  //按钮字体
    // bt_font.setPointSize(10); //字体大小
    // latitudeLabel->setFont(bt_font);
    // longitudeLabel->setFont(bt_font);
    // gpsAltitudeLabel->setFont(bt_font);
    // relAltitudeLabel->setFont(bt_font);

    latitudeLabel->setText(QString("纬度: %1").arg(receivelatitude));
    longitudeLabel->setText(QString("经度: %1").arg(receivelongitude));
    gpsAltitudeLabel->setText(QString("海拔: %1 米").arg(receivegpsAltitude));
    relAltitudeLabel->setText(QString("ASL: %1 米").arg(receiverelAltitude));

    // latitudeLabel->setParent(this);  // 确保它是主窗口的子控件
    // longitudeLabel->raise();
    // gpsAltitudeLabel->raise();
    // relAltitudeLabel->raise();
    latitudeLabel->show();
    longitudeLabel->show();
    gpsAltitudeLabel->show();
    relAltitudeLabel->show();
    update();
}


void Imu::update()
{
    // 视图刷新
    //int count=0;
    int i=count1++;
    qDebug() << "update被调用～"<<i;
    QWidget::update();
}

 void Imu::setImudata(const AircraftData &data)
{    //dataReceived = true;
     setAngles(data.pitch, data.roll,data.yaw); // 设置俯仰角和横滚角
    setData(data.latitude,data.longitude,data.gpsAltitude,data.relAltitude); //接收经纬度什么的

}

void Imu::resizeEvent(QResizeEvent *event)
{
    // 获取窗口的宽度和高度
    int windowWidth = event->size().width();
    int windowHeight = event->size().height();


    // 动态调整 latitudeLabel 的位置和大小
    latitudeLabel->resize(windowWidth * 0.2, windowHeight * 0.12); // 设置大小为窗口宽度的20%，高度的10%
    latitudeLabel->move(windowWidth * 0.79, windowHeight * 0.15);  // 设置位置为窗口宽度的45%，高度的20%


    // 动态调整 pitchLabel 的位置和大小
    pitchLabel->resize(windowWidth * 0.2, windowHeight * 0.12); // 设置大小为窗口宽度的20%，高度的10%
    pitchLabel->move(windowWidth * 0.03, windowHeight * 0.35);  // 设置位置为窗口宽度的45%，高度的20%

    // 动态调整 rollLabel 的位置和大小
    rollLabel->resize(windowWidth * 0.2, windowHeight * 0.12); // 设置大小为窗口宽度的20%，高度的10%
    rollLabel->move(windowWidth * 0.03, windowHeight * 0.55);  // 设置位置为窗口宽度的45%，高度的20%

    // 动态调整 yawLabel 的位置和大小
    yawLabel->resize(windowWidth * 0.2, windowHeight * 0.12); // 设置大小为窗口宽度的20%，高度的10%
    yawLabel->move(windowWidth * 0.03, windowHeight * 0.75);  // 设置位置为窗口宽度的45%，高度的20%

    // 动态调整 longitudeLabel 的位置和大小
    longitudeLabel->resize(windowWidth * 0.2, windowHeight * 0.12); // 设置大小为窗口宽度的20%，高度的10%
    longitudeLabel->move(windowWidth * 0.79, windowHeight * 0.45);  // 设置位置为窗口宽度的45%，高度的30%


    // 动态调整 gpsAltitudeLabel 的位置和大小
     gpsAltitudeLabel->resize(windowWidth * 0.2, windowHeight * 0.12); // 设置大小为窗口宽度的20%，高度的10%
     gpsAltitudeLabel->move(windowWidth * 0.79, windowHeight * 0.75);  // 设置位置为窗口宽度的45%，高度的30%


    // 动态调整 relAltitudeLabel 的位置和大小
     relAltitudeLabel->resize(windowWidth * 0.2, windowHeight * 0.12); // 设置大小为窗口宽度的20%，高度的10%
     relAltitudeLabel->move(windowWidth * 0.03, windowHeight * 0.15);  // 设置位置为窗口宽度的45%，高度的30%


     // 动态调整仪表盘的半径
    // dashboardRadius = qMin(windowWidth, windowHeight) / 2.5; // 选择最小的一边作为仪表盘半径

     // 调整字体大小
     fontSize = windowWidth / 20;  // 可以根据窗口宽度调整字体大小

    QWidget::resizeEvent(event);  // 调用基类的 resizeEvent
}


void Imu::printStackTrace()
{
    void *array[10];
    size_t size = backtrace(array, 10);
    char **symbols = backtrace_symbols(array, size);

    if (symbols != nullptr)
    {
        for (size_t i = 0; i < size; i++)
        {
            qDebug() << symbols[i];  // 输出调用栈
        }
        free(symbols);
    }
}


void Imu::paintEvent(QPaintEvent *event)
{      Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 获取窗口的宽度和高度
    int windowWidth = width();
    int windowHeight = height();

    // 获取中心点
    int centerX = windowWidth / 2;
    int centerY = windowHeight / 2;

    // 设置仪表盘半径
    dashboardRadius = qMin(windowWidth, windowHeight) / 3; // 选择最小的一边作为仪表盘半径



    // 创建 QPixmap 作为背景
    QPixmap backgroundPixmap(2 * dashboardRadius, 2 * dashboardRadius);
    backgroundPixmap.fill(Qt::transparent); // 填充透明背景

    QPainter backgroundPainter(&backgroundPixmap);
    backgroundPainter.setRenderHint(QPainter::Antialiasing);


    // // 计算俯仰角的偏移量
    // int pitchOffset = pitch * dashboardRadius / 90; // pitch 角度转换为像素偏移

    // // **绘制蓝色背景（天空）**
    // backgroundPainter.fillRect(0, 0, 2 * dashboardRadius, dashboardRadius + pitchOffset, QColor(61, 137, 237));

    // // **绘制绿色背景（地面）**
    // backgroundPainter.fillRect(0, dashboardRadius + pitchOffset, 2 * dashboardRadius, dashboardRadius - pitchOffset, QColor(127, 255, 0));
    // **计算俯仰角的偏移量**
    int pitchOffset = pitch * dashboardRadius / 90; // pitch 角度转换为像素偏移

    // **绘制蓝色背景（天空）**
    QPolygon skyPolygon;
    skyPolygon << QPoint(0, 0)
               << QPoint(2 * dashboardRadius, 0)
               << QPoint(2 * dashboardRadius, dashboardRadius + pitchOffset)
               << QPoint(0, dashboardRadius + pitchOffset);
    backgroundPainter.setBrush(QColor(50, 117, 247));
    backgroundPainter.setPen(Qt::NoPen);
    backgroundPainter.drawPolygon(skyPolygon);

    // **绘制绿色背景（地面）**
    QPolygon groundPolygon;
    groundPolygon << QPoint(0, dashboardRadius + pitchOffset)
                  << QPoint(2 * dashboardRadius, dashboardRadius + pitchOffset)
                  << QPoint(2 * dashboardRadius, 2 * dashboardRadius)
                  << QPoint(0, 2 * dashboardRadius);
    backgroundPainter.setBrush(QColor(110, 214, 0));
    backgroundPainter.setPen(Qt::NoPen);
    backgroundPainter.drawPolygon(groundPolygon);



    // **旋转背景（随 roll 旋转）**
    QPixmap rotatedBackground(backgroundPixmap.size());
    rotatedBackground.fill(Qt::transparent);
    QPainter rotatePainter(&rotatedBackground);
    rotatePainter.setRenderHint(QPainter::Antialiasing);
    rotatePainter.translate(dashboardRadius, dashboardRadius);
    rotatePainter.rotate(-roll);
    rotatePainter.drawPixmap(-dashboardRadius, -dashboardRadius, backgroundPixmap);
    rotatePainter.end();

    // **裁剪为圆形**
    QPixmap circularBackground(dashboardRadius * 2, dashboardRadius * 2);
    circularBackground.fill(Qt::transparent);

    QPainter circularPainter(&circularBackground);
    circularPainter.setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    path.addEllipse(0, 0, dashboardRadius * 2, dashboardRadius * 2);
    circularPainter.setClipPath(path);
    circularPainter.drawPixmap(0, 0, rotatedBackground);
    circularPainter.end();

    // **绘制最终背景**
    painter.drawPixmap(centerX - dashboardRadius, centerY - dashboardRadius, circularBackground);

    // **绘制外部仪表盘圆环**
    painter.setPen(QPen(Qt::black, 3));
    painter.drawEllipse(QPointF(centerX, centerY), dashboardRadius, dashboardRadius);

    // **绘制水平指示线**
    drawHorizonLine(painter, centerX, centerY, dashboardRadius, roll);

    // 绘制刻度
    drawScale(painter);

    // **绘制指针**
    painter.translate(centerX, centerY);
    painter.setPen(QPen(Qt::red, 7));
    painter.drawLine(0, -dashboardRadius, 0, -dashboardRadius + 20);

    // // **绘制罗盘**
    // int compassRadius = dashboardRadius / 1.5;
    // painter.setPen(QPen(Qt::red, 4));
    // painter.drawEllipse(QPointF(0, 0), compassRadius, compassRadius);

    // painter.rotate(yaw);
    // painter.setPen(QPen(Qt::yellow, 4));
    // painter.drawLine(0, -compassRadius, 0, -compassRadius + 20);
    // painter.resetTransform();









    // // 设置字体大小
    // QFont font = painter.font();
    // font.setPointSize(fontSize);  // 根据窗口宽度动态设置字体大小
    // font.setBold(true);           // 设置字体为粗体
    // painter.setFont(font);

    // // 绘制文本
    // painter.setPen(QPen(Qt::red, 4));
    // painter.drawText(rect(), Qt::AlignBottom | Qt::AlignLeft,
    //                  QString("Pitch: %1°\nRoll: %2°\nYaw: %3°").arg(pitch).arg(roll).arg(yaw));
}




//my
// void Imu::paintEvent(QPaintEvent *event)
// {
//     Q_UNUSED(event);

//     QPainter painter(this);
//     painter.setRenderHint(QPainter::Antialiasing);

//     // 获取窗口的宽度和高度
//     int windowWidth=windowWidth = width();
//     int windowHeight=windowHeight = height();

//     // 获取中心点
//     int centerX = windowWidth / 2;
//     int centerY = windowHeight / 2;

//     // 设置仪表盘半径
//     dashboardRadius = qMin(windowWidth, windowHeight) / 3; // 选择最小的一边作为仪表盘半径



//     // 创建 QPixmap 作为背景
//     QPixmap backgroundPixmap(2 * dashboardRadius, 2 * dashboardRadius);
//     backgroundPixmap.fill(Qt::transparent); // 填充透明背景
//     //generateBackgroundPixmap();





//     QPainter backgroundPainter(&backgroundPixmap);
//     backgroundPainter.setRenderHint(QPainter::Antialiasing);


//     // // 计算俯仰角的偏移量
//     // int pitchOffset = pitch * dashboardRadius / 90; // pitch 角度转换为像素偏移

//     // // **绘制蓝色背景（天空）**
//     // backgroundPainter.fillRect(0, 0, 2 * dashboardRadius, dashboardRadius + pitchOffset, QColor(61, 137, 237));

//     // // **绘制绿色背景（地面）**
//     // backgroundPainter.fillRect(0, dashboardRadius + pitchOffset, 2 * dashboardRadius, dashboardRadius - pitchOffset, QColor(127, 255, 0));
//     // **计算俯仰角的偏移量**
//     int pitchOffset = pitch * dashboardRadius / 90; // pitch 角度转换为像素偏移

//     // **绘制蓝色背景（天空）**
//     QPolygon skyPolygon;
//     skyPolygon << QPoint(0, 0)
//                << QPoint(2 * dashboardRadius, 0)
//                << QPoint(2 * dashboardRadius, dashboardRadius + pitchOffset)
//                << QPoint(0, dashboardRadius + pitchOffset);
//     backgroundPainter.setBrush(QColor(50, 117, 247));
//     backgroundPainter.setPen(Qt::NoPen);
//     backgroundPainter.drawPolygon(skyPolygon);

//     // **绘制绿色背景（地面）**
//     QPolygon groundPolygon;
//     groundPolygon << QPoint(0, dashboardRadius + pitchOffset)
//                   << QPoint(2 * dashboardRadius, dashboardRadius + pitchOffset)
//                   << QPoint(2 * dashboardRadius, 2 * dashboardRadius)
//                   << QPoint(0, 2 * dashboardRadius);
//     backgroundPainter.setBrush(QColor(110, 214, 0));
//     backgroundPainter.setPen(Qt::NoPen);
//     backgroundPainter.drawPolygon(groundPolygon);

//     painter.save();
//     painter.translate(centerX, centerY);
//     painter.rotate(-roll);
//     painter.drawPixmap(-dashboardRadius, -dashboardRadius, backgroundPixmap);
//     painter.restore();


//     // **旋转背景（随 roll 旋转）**
//     QPixmap rotatedBackground(backgroundPixmap.size());
//     rotatedBackground.fill(Qt::transparent);
//     QPainter rotatePainter(&rotatedBackground);
//     rotatePainter.setRenderHint(QPainter::Antialiasing);
//     rotatePainter.translate(dashboardRadius, dashboardRadius);
//     rotatePainter.rotate(-roll);
//     rotatePainter.drawPixmap(-dashboardRadius, -dashboardRadius, backgroundPixmap);
//     rotatePainter.end();

//     // **裁剪为圆形**
//     QPixmap circularBackground(dashboardRadius * 2, dashboardRadius * 2);
//     circularBackground.fill(Qt::transparent);

//     QPainter circularPainter(&circularBackground);
//     circularPainter.setRenderHint(QPainter::Antialiasing);

//     QPainterPath path;
//     path.addEllipse(0, 0, dashboardRadius * 2, dashboardRadius * 2);
//     circularPainter.setClipPath(path);
//     circularPainter.drawPixmap(0, 0, rotatedBackground);
//     circularPainter.end();

//    // **绘制最终背景**
//     painter.drawPixmap(centerX - dashboardRadius, centerY - dashboardRadius, circularBackground);

//     // **绘制外部仪表盘圆环**
//     painter.setPen(QPen(Qt::black, 3));
//     painter.drawEllipse(QPointF(centerX, centerY), dashboardRadius, dashboardRadius);

//     // **绘制水平指示线**
//     drawHorizonLine(painter, centerX, centerY, dashboardRadius, roll);

//     // 绘制刻度
//     drawScale(painter);

//     // **绘制指针**
//     painter.translate(centerX, centerY);
//     painter.setPen(QPen(Qt::red, 7));
//     painter.drawLine(0, -dashboardRadius, 0, -dashboardRadius + 20);

//     // // **绘制罗盘**
//     // int compassRadius = dashboardRadius / 1.5;
//     // painter.setPen(QPen(Qt::red, 4));
//     // painter.drawEllipse(QPointF(0, 0), compassRadius, compassRadius);

//     // painter.rotate(yaw);
//     // painter.setPen(QPen(Qt::yellow, 4));
//     // painter.drawLine(0, -compassRadius, 0, -compassRadius + 20);
//     // painter.resetTransform();

// }


// void Imu::generateBackgroundPixmap() {
//     int size = qMin(width(), height()) / 3 * 2;
//     backgroundPixmap = QPixmap(size, size);
//     backgroundPixmap.fill(Qt::transparent);

//     QPainter painter(&backgroundPixmap);
//     painter.setRenderHint(QPainter::Antialiasing);

//     // 画固定的圆环
//     painter.setPen(QPen(Qt::black, 3));
//     painter.drawEllipse(QPointF(size / 2, size / 2), size / 2, size / 2);


//     // **裁剪为圆形**
//     QPixmap circularBackground(dashboardRadius * 2, dashboardRadius * 2);
//     circularBackground.fill(Qt::transparent);

//     QPainter circularPainter(&circularBackground);
//     circularPainter.setRenderHint(QPainter::Antialiasing);

//     QPainterPath path;
//     path.addEllipse(0, 0, dashboardRadius * 2, dashboardRadius * 2);
//     circularPainter.setClipPath(path);
//     circularPainter.drawPixmap(0, 0, rotatedBackground);
//     circularPainter.end();

//    // **绘制最终背景**
   // painter.drawPixmap(centerX - dashboardRadius, centerY - dashboardRadius, circularBackground);
// }




void Imu::drawScale(QPainter &painter)
{
    painter.save();  // 保存当前绘制状态
    painter.translate(width() / 2, height() / 2);  // 以窗口中心为旋转中心
    painter.rotate(-roll);  // 旋转刻度，使其随 roll 倾斜

    // 1️⃣ 绘制水平方向刻度（随 roll 旋转）
    int numTicks = 4;
    int scaleRadius = dashboardRadius - 20;

    for (int i = -numTicks; i <= numTicks; ++i) {
        int angle = i * 15;
        int tickLength = (i % 2 == 0) ? dashboardRadius / 15 : dashboardRadius / 25;

        int x1 = scaleRadius * sin(qDegreesToRadians(angle));
        int y1 = -scaleRadius * cos(qDegreesToRadians(angle));

        int x2 = (scaleRadius + tickLength) * sin(qDegreesToRadians(angle));
        int y2 = -(scaleRadius + tickLength) * cos(qDegreesToRadians(angle));

        painter.setPen(QPen(Qt::white, 2));
        painter.drawLine(QPointF(x1, y1), QPointF(x2, y2));
    }

    // 2️⃣ 绘制垂直刻度（随 pitch 变化，约束在仪表盘范围内）
    int verticalNumTicks = 6;
    int verticalSpacing = dashboardRadius / 6;
    int tickMaxLength = dashboardRadius / 6;
    int tickMinLength = dashboardRadius / 10;
    int textOffset = dashboardRadius / 5;  // 文字偏移，使其不重叠刻度

    int pitchOffset = (pitch * dashboardRadius) / 90;

    for (int i = -verticalNumTicks; i <= verticalNumTicks; ++i) {
        int tickY = i * verticalSpacing - pitchOffset;

        // 限制刻度范围在仪表盘内部
        if (abs(tickY) > dashboardRadius - 35) continue;

        int tickLength = (i % 2 == 0) ? tickMaxLength : tickMinLength;

        // // 根据刻度位置决定正负号，上方为正，下方为负
        // int tickValue = (i > 0) ? i * 5 : i * 5;

        // painter.setPen(QPen(Qt::yellow, 2));
        // painter.drawLine(QPointF(tickLength, tickY), QPointF(-tickLength, tickY));
        // **调整 tickValue，使上方为正，下方为负**
        int tickValue = i * 5;

        painter.setPen(QPen(Qt::yellow, 2));
        painter.drawLine(QPointF(tickLength, tickY), QPointF(-tickLength, tickY));
        // 在刻度两端绘制数字（避免重叠刻度）
        if (i % 2 == 0 && i != 0) {  // 只在偶数刻度上绘制
            painter.setPen(Qt::white);
            QFont font = painter.font();
            font.setPointSize(12);
            painter.setFont(font);

            QString tickText = QString::number(tickValue);
            painter.drawText(QPointF(tickLength + 5, tickY + 5), tickText);
            painter.drawText(QPointF(-tickLength - textOffset, tickY + 5), tickText);
        }
    }

    painter.restore();  // 恢复绘制状态，避免影响其他元素
}





// **绘制飞机水平位置线（地平线指示线）**
void Imu::drawHorizonLine(QPainter &painter, int centerX, int centerY, int dashboardRadius, int roll)
{
    painter.save(); // 保存当前 painter 状态（git）
    painter.translate(centerX, centerY); // 移动坐标到仪表盘中心
   // painter.rotate(-roll); // 绕中心点旋转 Roll 角度（左偏为正，右偏为负）

    // **绘制水平指示线(git)**
    int lineLength = dashboardRadius * 1.5; // 线的长度
    int lineWidth = 3; // 线的宽度
    painter.setPen(QPen(Qt::red, lineWidth));
    painter.drawLine(QPointF(-lineLength / 2, 0), QPointF(lineLength / 2, 0));

    painter.restore(); // 恢复 painter 状态
}

void Imu::setLabelsAlignment(Qt::Alignment alignment)
{
    latitudeLabel->setAlignment(alignment);
    longitudeLabel->setAlignment(alignment);
    gpsAltitudeLabel->setAlignment(alignment);
    relAltitudeLabel->setAlignment(alignment);
    pitchLabel->setAlignment(alignment);
    rollLabel->setAlignment(alignment);
    yawLabel->setAlignment(alignment);
    // 根据需求继续添加更多的 QLabel
}

Imu::~Imu()
{
    delete ui;
     qDebug() << "imu析构！";
}
