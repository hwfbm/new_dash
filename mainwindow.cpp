#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,serialPort(new QSerialPort(this)),
    imuWidget(new Imu(this)),
    serial(new Serial),
    batteryWidget(new Battery(this)),
    weatherWidget(new Weather(this)),
    timeLabel(new QLabel(this)),
    statusLabel(new QLabel(this)),
    statusiconLabel(new QLabel(this))

{
    ui->setupUi(this);

    this->setStyleSheet("QMainWindow { background-color: rgba(255,255,255,0.9); }");

    // 创建定时器
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTime);  // 连接定时器的 timeout 信号到 updateTime 槽
    timer->start(1000);  // 每秒触发一次
    // 初始更新时间
    updateTime();
    setupBt();

    // 创建定时器更新status
    status_timer = new QTimer(this);
    connect(status_timer, &QTimer::timeout, this, &MainWindow::updateStatus);  // 连接定时器的 timeout 信号到 updateTime 槽
    status_timer->start(2000);  // 每2秒触发一次
    updateStatus(); //初始更新飞机状态




    label = new QLabel("0", this);
     label->resize(50, 50); // 设置大小为窗口宽度的20%，高度的10%
    label->move(100,300);
    label->setAlignment(Qt::AlignCenter);


    // 创建 QTimer
    QTimer *timer = new QTimer(this);
    //connect(timer, &QTimer::timeout, this, &MainWindow::updateNumber);
    timer->start(30);  // 每 1000 毫秒（1 秒）触发一次
     label->setStyleSheet("color: black;border:2px red;");




    // 显示地平仪视图
    //imuWidget->setGeometry(60, 190, 400, 400); // 设置位置 (x=50, y=50) 和大小 (宽=400, 高=400)
    imuWidget->show();
    // 设置电量视图
    batteryWidget->show();

    weatherWidget->show();

    timeLabel->setAlignment(Qt::AlignCenter);
    timeLabel->setStyleSheet("color: black; ");
    timeLabel->setVisible(true);  // 确保 label 是可见的
    timeLabel->show();  // 显示标签

    statusLabel->setStyleSheet("color: black;");
   // statusLabel->setAlignment(Qt::AlignCenter);
    statusiconLabel->setStyleSheet("color: black;");
    statusiconLabel->setAlignment(Qt::AlignCenter);


   // 按钮们连接信号和槽
   bool connected = connect(bt_start, &QPushButton::clicked, this, [this](){
       qDebug() << "开始起飞";
       QMessageBox::information(this, "提示", "开始起飞");
   });

   if (!connected) {
       qDebug() << "连接失败";
   }
   connect(bt_start, &QPushButton::pressed, this, [](){
       qDebug() << "按钮被按下";
   });

   connect(bt_down, &QPushButton::clicked, [this](){qDebug()<<"开始降落";
     QMessageBox::information(this, "提示", "开始降落");});
   connect(bt_A, &QPushButton::clicked, [this](){qDebug()<<"开始飞向A点";
     QMessageBox::information(this, "提示", "开始飞向A点");});
   connect(bt_B, &QPushButton::clicked, [this](){qDebug()<<"开始飞向B点";
     QMessageBox::information(this, "提示", "开始飞向B点");});
   connect(bt_C, &QPushButton::clicked, [this](){qDebug()<<"开始飞向C点";
     QMessageBox::information(this, "提示", "开始飞向C点");});


}


void MainWindow::sendData()
{
    // 生成随机数据
    //std::uniform_real_distribution<double> distribution(0.0, 180.0);
    static double pitch=0,roll=180;
    pitch++;
    roll--;
    if(pitch==180)
    {
        pitch=0;
    }
    if(roll==0)
    {
        roll=180;
    }

}






void MainWindow::handleSerialError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, "Critical Error", serialPort->errorString());
        serialPort->close();
    }


}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    // 获取窗口的宽度和高度
    int windowWidth = event->size().width();
    int windowHeight = event->size().height();
    // 设置全局缩放因子，可以基于窗口的宽度或其他标准
    // 动态调整 imuWidget 的位置和大小
    imuWidget->resize(windowWidth * 0.58, windowHeight * 0.67);  // 设置大小为窗口的30%宽度，30%高度
    imuWidget->move(windowWidth * 0.04, windowHeight * 0.15);   // 设置位置为窗口宽度的5%，高度的20%

    // 动态调整 imuWidget 的位置和大小
   weatherWidget->resize(windowWidth * 0.8, windowHeight * 0.055);  // 设置大小为窗口的30%宽度，30%高度
   weatherWidget->move(windowWidth * 0.6, windowHeight * 0.012);   // 设置位置为窗口宽度的5%，高度的20%
    // weatherWidget->resize(windowWidth * 1, windowHeight * 0.1);  // 设置大小为窗口的30%宽度，30%高度
    // weatherWidget->move(windowWidth * 0.2, windowHeight * 0.35);   // 设置位置为窗口宽度的5%，高度的20%

    // 动态调整 batteryWidget 的位置和大小
    batteryWidget->resize(windowWidth * 0.45, windowHeight * 0.055);  // 设置大小为窗口的30%宽度，30%高度
    batteryWidget->move(windowWidth * 0.04, windowHeight * 0.02);   // 设置位置为窗口宽度的5%，高度的20%
    // 动态调整 longitudeLabel 的位置和大小

    bool connected=connect(batteryWidget,&Battery::fontchanged,this,&MainWindow::updatefontsize);
    // 按钮们连接信号和槽
    if (!connected) {
        qDebug() << "字体连接失败";
    }
    bool connectedw=connect(batteryWidget,&Battery::fontchanged,weatherWidget,&Weather::updatefontsize);
    // 按钮们连接信号和槽
    if (!connectedw){
        qDebug() << "字体连接失败weather!";
    }

    timeLabel->resize(windowWidth * 0.2, windowHeight * 0.06); // 设置大小为窗口宽度的20%，高度的10%
    timeLabel->move(windowWidth * 0.38, windowHeight * 0.01);  // 设置位置为窗口宽度的45%，高度的30%

    statusiconLabel->resize(windowWidth * 0.05, windowHeight * 0.1); // 设置大小为窗口宽度的20%，高度的10%
    statusiconLabel->move(windowWidth * 0.17, windowHeight * 0.75);  // 设置位置为窗口宽度的45%，高度的30%

    statusLabel->resize(windowWidth * 0.3, windowHeight * 0.1); // 设置大小为窗口宽度的20%，高度的10%
    statusLabel->move(statusiconLabel->x() + statusiconLabel->width() + 6,statusiconLabel->y());  // 垂直居中对齐

    // 动态调整 bt_start 按钮的大小和位置
    bt_start->resize(windowWidth * 0.25, windowHeight * 0.1);  // 按钮大小为窗口宽度的30%，高度的10%
    bt_start->move(windowWidth * 0.7, windowHeight * 0.2);  // 按钮位置为窗口宽度的35%，高度的75%

    // 动态调整 bt_down 按钮的大小和位置
    bt_down->resize(windowWidth * 0.25, windowHeight * 0.1);  // 按钮大小为窗口宽度的30%，高度的10%
    bt_down->move(windowWidth * 0.7, windowHeight * 0.35);  // 按钮位置为窗口宽度的35%，高度的85%

    // 动态调整 bt_A 按钮的大小和位置
    bt_A->resize(windowWidth * 0.25, windowHeight * 0.1);  // 按钮大小为窗口宽度的30%，高度的10%
    bt_A->move(windowWidth * 0.7, windowHeight * 0.5);  // 按钮位置为窗口宽度的5%，高度的75%

    // 动态调整 bt_B 按钮的大小和位置
    bt_B->resize(windowWidth * 0.25, windowHeight * 0.1);  // 按钮大小为窗口宽度的30%，高度的10%
    bt_B->move(windowWidth * 0.7, windowHeight * 0.65);  // 按钮位置为窗口宽度的5%，高度的85%

    // 动态调整 bt_C 按钮的大小和位置
    bt_C->resize(windowWidth * 0.25, windowHeight * 0.1);  // 按钮大小为窗口宽度的30%，高度的10%
    bt_C->move(windowWidth * 0.7, windowHeight * 0.8);  // 按钮位置为窗口宽度的5%，高度的95%

    QWidget::resizeEvent(event);  // 调用基类的 resizeEvent
}


void MainWindow::updateTime() {
    // 获取当前时间
    QDateTime now = QDateTime::currentDateTime();

    // 格式化时间字符串
    QString timeString = now.toString("yyyy-MM-dd HH:mm:ss");

    // 更新 QLabel 的时间
    timeLabel->setText(timeString);
}

void MainWindow::updateStatus() {

    QString status ="飞行器状态良好！";
    statusLabel->setText(status);
    QMovie *movie = new QMovie();

    if (status == "飞行器状态良好！") {
        movie->setFileName(":/good-review.gif");
    } else if (status == "飞行器状态异常！") {
        movie->setFileName(":/bad-review.gif");
    }
    // 确保 QLabel 启用自动缩放内容
    statusiconLabel->setScaledContents(true);
    statusiconLabel->setMovie(movie);
    movie->start();
}


void MainWindow::setButtonStyle(QPushButton* button)
{
    button->setStyleSheet(
        "QPushButton {"
        "  font-size: 15px;"
        "  background-color: rgba(255,255,255,0);"
        "  color: black;"
        "  border: 2px solid green;"
        "  border-radius: 10px;"
        "}"
        "QPushButton:pressed {"
        "  border: 2px solid blue;"
        "}"
        );
}

void MainWindow::setupBt()
{
    // 创建按钮
    bt_start = new QPushButton("一键起飞", this);
    bt_down = new QPushButton("一键降落", this);
    bt_A = new QPushButton("飞向A点", this);
    bt_B = new QPushButton("飞向B点", this);
    bt_C = new QPushButton("飞向C点", this);

    // 调用 setButtonStyle() 设置样式
    setButtonStyle(bt_start);
    setButtonStyle(bt_down);
    setButtonStyle(bt_A);
    setButtonStyle(bt_B);
    setButtonStyle(bt_C);

    // 可以设置按钮的其它属性，比如布局、位置等
    bt_start->setGeometry(100, 100, 150, 50);
    bt_down->setGeometry(100, 160, 150, 50);
    bt_A->setGeometry(100, 220, 150, 50);
    bt_B->setGeometry(100, 280, 150, 50);
    bt_C->setGeometry(100, 340, 150, 50);
}

void MainWindow::updatefontsize(int changedfont) //字体大小和最小窗口同步
{
    int globalScaleFactor=changedfont;
    qDebug()<<"globalScaleFactor size:"<<globalScaleFactor;
    QFont labelFont =  timeLabel->font(); // 获取当前字体
    labelFont.setPointSize(globalScaleFactor);

    timeLabel->setFont(labelFont);  // 应用字体
    QFont labelFont1 =  statusLabel->font(); // 获取当前字体
    labelFont1.setPointSize(globalScaleFactor+10);
    statusLabel->setFont(labelFont1);
}



MainWindow::~MainWindow()
{
    serialPort->close(); // 关闭串口
    delete ui;
}
