#include "battery.h"
#include "ui_battery.h"

Battery::Battery(QWidget *parent)
    : QWidget(parent),
    batteryProgressBar(new QProgressBar(this)),
    ui(new Ui::Battery)
{
    ui->setupUi(this);
    // 定时器定时刷新
    // this->setStyleSheet("QWidget { background-color: lightblue; }");
    // // 创建一个 QLabel
    // QLabel *label= new QLabel("这是一个带有背景色的窗口",this);
    // label->setGeometry(0, 0, this->width(), this->height()); // 设置位置 (x=50, y=50) 和大小 (宽=400, 高=400)
    // label->setAlignment(Qt::AlignCenter);
    this->batteryLevel=batteryLevel;
    batteryProgressBar->setTextVisible(false);  // 不显示文本
   // batteryProgressBar->setFormat("%p%");  // 显示百分比格式
    batteryProgressBar->setStyleSheet(
        "QProgressBar {"
        "    border: 2px solid #bbb;"
        "    border-radius: 5px;"
        "    background-color: #f3f3f3;"
        "}"
        "QProgressBar::chunk {"
        "    background-color: #4CAF50;"  // 设置进度条的颜色
        "    border-radius: 3px;"
        "}"
        );
    timeLabel = new QLabel(this);
    timeLabel->setStyleSheet("color: black;");
    flyabletimeLabel = new QLabel(this);
    flyabletimeLabel->setStyleSheet("color: black;");
    flyabletimeLabel->setAlignment(Qt::AlignCenter);  // 确保文本在 QLabel 中居中

    QTimer *bt_time = new QTimer();
     connect(bt_time, &QTimer::timeout, this, &Battery::updateBatteryLevel);
    bt_time->start(500); // 每5秒刷新一次电量
}
void Battery::updateBatteryLevel() {
    // 使用QProcess获取电池电量
    QProcess process;
    process.start("pmset", QStringList() << "-g" << "batt");
    process.waitForFinished();

    // 获取输出并解析电池电量
    QString output = process.readAllStandardOutput();
    int batteryLevel = parseBatteryLevel(output);

    // 更新进度条
    batteryProgressBar->setValue(batteryLevel);

    // 更新显示剩余电量时间的标签
    QString remainingTime = QString(" %1%").arg(batteryLevel);
    timeLabel->setText(remainingTime);

    // 更新可飞时间的标签
    //QString remainingTime = QString("电量: %1%").arg(batteryLevel);
    flyabletimeLabel->setText("1min38s");

}
// 解析pmset命令输出的电池电量
// 解析pmset命令输出的电池电量


int Battery::parseBatteryLevel(const QString &output) {
    // 使用 QRegularExpression 替代 QRegExp
    QRegularExpression regex("(\\d+)%");  // 匹配电量百分比
    //QRegularExpression 提供了更现代且灵活的正则表达式功能
    QRegularExpressionMatch match = regex.match(output);//QRegularExpressionMatch：用于存储匹配结果，可以通过 captured() 方法获取匹配的内容

    if (match.hasMatch()) {
        return match.captured(1).toInt();  // 返回匹配到的第一个捕获组（即电池电量）
    }

    return 0; // 默认返回 0
}

// int Battery::getBatteryLevel() {
//     QProcess process;
//     process.start("pmset -g batt"); // macOS 下的电池状态命令
//     process.waitForFinished();

//     QString output = process.readAllStandardOutput();
//     QRegularExpression regex("\\d+%"); // 匹配电量百分比
//     QRegularExpressionMatch match = regex.match(output);

//     if (match.hasMatch()) {
//         QString level = match.captured(0).remove('%');
//         return level.toInt();
//     }
//     return -1; // 获取失败
// }

// void Battery::paintEvent(QPaintEvent *event)
// {
//     QProgressBar *batteryProgressBar = new QProgressBar(this);
//     //batteryProgressBar->setGeometry(10, 10, 200, 30);  // 设置位置和大小
//     //batteryProgressBar->setRange(0, 100);  // 设置最小值和最大值为 100
//     batteryProgressBar->setTextVisible(true);  // 显示文本
//     batteryProgressBar->setFormat("%p%");  // 显示百分比格式
//     batteryProgressBar->setValue(batteryLevel);  // 更新电池电量
// }






// void Battery::updateBatteryLevel() {
//     int level = getBatteryLevel();
//     if (level >= 0) {
//         batteryLevel = level;
//         update(); // 刷新界面
//     }
// }
// void Battery::update() {
// }

void Battery::resizeEvent(QResizeEvent *event)
{
    // 获取当前窗口的宽度和高度
    int width = event->size().width();
    int height = event->size().height();
    // 计算字体大小，设定为窗口宽度的一个比例（例如 2%）
        int fontSize = width * 0.038;  //根据需求调整比例
        QFont labelFont = flyabletimeLabel->font(); // 获取当前字体
        qDebug()<<"fontSize:"<<fontSize;
         emit fontchanged(fontSize); //发送字体改变信号

        labelFont.setPointSize(fontSize);  // 设置新的字体大小
        flyabletimeLabel->setFont(labelFont);  // 应用字体

        labelFont = timeLabel->font();
        labelFont.setPointSize(fontSize);
        timeLabel->setFont(labelFont);

    // 计算共用的高度（让 flyabletimeLabel 和 batteryProgressBar 高度一致）
    int commonHeight = height * 0.7;  // 比如设置为高度的 70%

    // 调整 flyabletimeLabel 的大小和位置，设置宽度为窗口的 20%，高度为共用高度
    flyabletimeLabel->resize(width * 0.15, commonHeight);  // 宽度是窗口的 20%，高度是共用高度
    flyabletimeLabel->move(0, 0);  // 放置在左上角

    // 调整 batteryProgressBar 的大小和位置
    batteryProgressBar->resize(width * 0.4, commonHeight);  // 宽度是窗口的 64%，高度是共用高度
    batteryProgressBar->move(flyabletimeLabel->x() + flyabletimeLabel->width() + 6, flyabletimeLabel->y());  // 在 flyabletimeLabel 右侧并且高度对齐

    // 调整 timeLabel 的大小和位置，使其与 batteryProgressBar 对齐
    timeLabel->resize(width * 0.15, commonHeight);  // 宽度是窗口的 30%，高度是窗口的 50%
    // timeLabel->move(batteryProgressBar->x() + batteryProgressBar->width() + 10,
    //                 batteryProgressBar->y() + (batteryProgressBar->height() - timeLabel->height()) / 2);  // 垂直居中对齐
    timeLabel->move(batteryProgressBar->x() + batteryProgressBar->width() + 6,
                     batteryProgressBar->y());  // 垂直居中对齐

    QWidget::resizeEvent(event);  // 调用父类的 resizeEvent
}

// void Battery::resizeEvent(QResizeEvent *event)
// {
//     // 获取当前窗口宽度和高度
//     int width = event->size().width();
//     int height = event->size().height();

//     // 调整 flyabletimeLabel 的大小和位置
//     flyabletimeLabel->resize(width * 0.2, height * 0.5);  // 大小为窗口宽度的20%，高度的40%
//     flyabletimeLabel->move(0, 0);

//     // 调整 batteryProgressBar 的大小和位置
//     batteryProgressBar->resize(width * 0.64, height * 0.7);  // 大小为窗口宽度的64%，高度的70%
//     batteryProgressBar->move(flyabletimeLabel->x() + flyabletimeLabel->width() + 10, flyabletimeLabel->y());

//     // 调整 timeLabel 的大小和位置
//     timeLabel->resize(width * 0.3, height * 0.5);  // 大小为窗口宽度的30%，高度的50%
//     timeLabel->move(batteryProgressBar->x() + batteryProgressBar->width() + 10, batteryProgressBar->y() + (batteryProgressBar->height() - timeLabel->height()) / 2);
//     // 调整 flyabletimeLabel 和 batteryProgressBar 的 y 坐标相同，使它们在垂直方向上对齐

//     QWidget::resizeEvent(event);  // 调用父类的 resizeEvent
// }




Battery::~Battery()
{
    delete ui;
}
