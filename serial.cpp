#include "serial.h"

Serial::Serial(QObject *parent)
 : QObject{parent}
{

    serialPort=new QSerialPort();
        //配置接收端串口
    serialPort->setPortName("/dev/tty.usbserial-14140"); // 替换为接收端的虚拟串口名
    // QString portName = QSettings("config.ini", QSettings::IniFormat).value("/dev/tty.usbserial-14140", "/dev/ttyUSB0").toString();
    // serialPort->setPortName(portName);
    serialPort->setBaudRate(QSerialPort::Baud115200);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);
        //serialPort->open(QIODevice::ReadWrite);


    if (!serialPort->open(QIODevice:: ReadWrite)) {
        qDebug() << "无法打开发送端串口！：" << serialPort->errorString();
    }else {
        qDebug() << "Serial port opened successfully!";
        connect(serialPort, &QSerialPort::readyRead, this, &Serial::onDataReceived);
    }
}




// AircraftData Serial::parseAircraftData(const QByteArray &data)
// {
//     AircraftData aircraft;

//     if (data.size() < 34 || static_cast<unsigned char>(data[0]) != 0xEE ||
//         static_cast<unsigned char>(data[1]) != 0x81 ||
//         static_cast<unsigned char>(data[2]) != 0x22) {
//         qWarning() << "Invalid data frame!";
//         return aircraft;
//     }

//     // 横滚角（单位：0.1° -> 转换为度）
//     aircraft.roll = static_cast<qint16>(static_cast<unsigned char>(data[4]) | (static_cast<unsigned char>(data[5]) << 8)) * 0.1;

//     // 俯仰角（单位：0.1° -> 转换为度）
//     aircraft.pitch = static_cast<qint16>(static_cast<unsigned char>(data[6]) | (static_cast<unsigned char>(data[7]) << 8)) * 0.1;

//     // 航向角（单位：0.1° -> 转换为度）
//     aircraft.yaw = static_cast<qint16>(static_cast<unsigned char>(data[8]) | (static_cast<unsigned char>(data[9]) << 8)) * 0.1;

//     // 纬度（单位：实际值 * 10000000）
//     aircraft.latitude = (static_cast<qint32>(static_cast<unsigned char>(data[10]) |
//                                              (static_cast<unsigned char>(data[11]) << 8) |
//                                              (static_cast<unsigned char>(data[12]) << 16) |
//                                              (static_cast<unsigned char>(data[13]) << 24))) / 10000000.0;

//     // 经度（单位：实际值 * 10000000）
//     aircraft.longitude = (static_cast<qint32>(static_cast<unsigned char>(data[14]) |
//                                               (static_cast<unsigned char>(data[15]) << 8) |
//                                               (static_cast<unsigned char>(data[16]) << 16) |
//                                               (static_cast<unsigned char>(data[17]) << 24))) / 10000000.0;

//     // GPS高度（单位：分米 -> 转换为米）
//     aircraft.gpsAltitude = static_cast<qint16>(static_cast<unsigned char>(data[18]) | (static_cast<unsigned char>(data[19]) << 8)) / 10.0;

//     // 相对高度（单位：分米 -> 转换为米）
//     aircraft.relAltitude = static_cast<qint16>(static_cast<unsigned char>(data[20]) | (static_cast<unsigned char>(data[21]) << 8)) / 10.0;

//     // GPS时间（年、月、日、时、分、秒）
//     aircraft.gpsTime[0] = static_cast<unsigned char>(data[22]); // 年
//     aircraft.gpsTime[1] = static_cast<unsigned char>(data[23]); // 月
//     aircraft.gpsTime[2] = static_cast<unsigned char>(data[24]); // 日
//     aircraft.gpsTime[3] = static_cast<unsigned char>(data[25]); // 时
//     aircraft.gpsTime[4] = static_cast<unsigned char>(data[26]); // 分
//     aircraft.gpsTime[5] = static_cast<unsigned char>(data[27]); // 秒

//     // 东向速度（单位：cm/s -> 转换为 m/s）
//     aircraft.eastSpeed = static_cast<qint16>(static_cast<unsigned char>(data[28]) | (static_cast<unsigned char>(data[29]) << 8)) / 100.0;

//     // 北向速度（单位：cm/s -> 转换为 m/s）
//     aircraft.northSpeed = static_cast<qint16>(static_cast<unsigned char>(data[30]) | (static_cast<unsigned char>(data[31]) << 8)) / 100.0;

//     // 天向速度（单位：cm/s -> 转换为 m/s）
//     aircraft.upSpeed = static_cast<qint16>(static_cast<unsigned char>(data[32]) | (static_cast<unsigned char>(data[33]) << 8)) / 100.0;

//     return aircraft;
// }


AircraftData Serial::parseAircraftData(const QByteArray &data) {
    AircraftData aircraft;
    qDebug() << "看看buffer里有没有缓存:" << buffer.toHex().toUpper();


    // 数据头校验（确保帧头正确）
    if (data.size() < 34 || static_cast<unsigned char>(data[0]) != 0xEE ||
        static_cast<unsigned char>(data[1]) != 0x81 ||
        static_cast<unsigned char>(data[2]) != 0x22) {
        qWarning() << "Invalid data frame!";
        return aircraft;
    }

    // 横滚角（单位：0.1° -> 转换为度）
    qDebug() << "横滚 bytes: "
             << QString::number(static_cast<unsigned char>(data[4]), 16)
             << QString::number(static_cast<unsigned char>(data[3]), 16);
    aircraft.roll = static_cast<qint16 >(
                        (static_cast<unsigned char>(data[4]) << 8) |
                        static_cast<unsigned char>(data[3])) * 0.1;

    // aircraft.roll = static_cast<qint16>(static_cast<unsigned char>(data[3])) * 0.1;

    //qDebug() << "Parsed roll:" << aircraft.roll;
    qDebug() << "横滚字节数:" << sizeof(aircraft.roll);
    qDebug() << "横滚数:" << aircraft.roll;
    //qDebug() << "data[4]:" << QString::number(static_cast<unsigned char>(data[4]), 16)<< "data[5]:"<<QString::number(static_cast<unsigned char>(data[5]), 16);



    // 俯仰角（单位：0.1° -> 转换为度）
    //aircraft.pitch = static_cast<qint16>(static_cast<unsigned char>(data[5])) * 0.1;
    qDebug() << "俯仰bytes: "
             << QString::number(static_cast<unsigned char>(data[6]), 16)
             << QString::number(static_cast<unsigned char>(data[5]), 16);
    aircraft.pitch = static_cast<qint16>(
                         (static_cast<unsigned char>(data[6]) << 8) |
                         static_cast<unsigned char>(data[5])) * 0.1;

    qDebug() << "俯仰字节数:" << sizeof(aircraft.pitch);




    // 航向角（单位：0.1° -> 转换为度）
    qDebug() << "偏航bytes: "
             << QString::number(static_cast<unsigned char>(data[8]), 16)
             << QString::number(static_cast<unsigned char>(data[7]), 16);
    aircraft.yaw = static_cast<qint16>(
                       (static_cast<unsigned char>(data[8]) << 8) |
                       static_cast<unsigned char>(data[7])) * 0.1;
    //aircraft.yaw = static_cast<qint16>(static_cast<unsigned char>(data[7])) * 0.1;
    qDebug() << "偏航字节数:" << sizeof(aircraft.yaw);

    // qDebug() << "偏航 bytes: "
    //          << QString::number(static_cast<unsigned char>(data[7]), 16)
    //          << QString::number(static_cast<unsigned char>(data[8]), 16);


    // 纬度（实际值 * 10000000）
    aircraft.latitude = static_cast<qint32>(
                            (static_cast<unsigned char>(data[12]) << 24) |
                            (static_cast<unsigned char>(data[11]) << 16) |
                            (static_cast<unsigned char>(data[10]) << 8) |
                            static_cast<unsigned char>(data[9])) / 10000000.0;
    // 发射信号更新latitude
    //emit latitudeUpdated(aircraft.latitude); //使用信号传latitude数据，注意aircraft.latitude是double



    // 经度（实际值 * 10000000）
    aircraft.longitude = static_cast<qint32>(
                             (static_cast<unsigned char>(data[16]) << 24) |
                             (static_cast<unsigned char>(data[15]) << 16) |
                             (static_cast<unsigned char>(data[14]) << 8) |
                             static_cast<unsigned char>(data[13])) / 10000000.0;

    // 发射信号更新longitude
    //emit longitudeUpdated(aircraft.longitude); //使用信号传longitude数据，注意aircraft.longitude是double


    // GPS高度（单位：分米 -> 转换为米）
    aircraft.gpsAltitude = static_cast<qint16>(
                               (static_cast<unsigned char>(data[18]) << 8) |
                               static_cast<unsigned char>(data[17])) /   10.0;
    qDebug() << "data[17]:" << QString::number(static_cast<unsigned char>(data[17]), 16);
    qDebug() << "data[18]:" << QString::number(static_cast<unsigned char>(data[18]), 16);
    if (aircraft.gpsAltitude < 0) {
        qDebug() << "GPS不正常？,海拔小于0， check the data!";
    }
    // 发射信号更新gpsAltitude
    //emit gpsAltitudeUpdated(aircraft.gpsAltitude); //使用信号传lgpsAltitude数据，注意aircraft.gpsAltitude是float

    // 相对高度（单位：分米 -> 转换为米）
    aircraft.relAltitude = static_cast<qint16>(
                               (static_cast<unsigned char>(data[20]) << 8) |
                               static_cast<unsigned char>(data[19])) / 10.0;
    // 发射信号更新relAltitude
    //emit relAltitudeUpdated(aircraft.relAltitude); //使用信号传relAltitude数据，注意aircraft.relAltitude是float



    //GPS时间
    aircraft.gpsTime.year = static_cast<int>(data[21]);
    aircraft.gpsTime.month = static_cast<int>(data[22]);
    aircraft.gpsTime.day = static_cast<int>(data[23]);
    aircraft.gpsTime.hour = static_cast<int>(data[24]);
    aircraft.gpsTime.minute = static_cast<int>(data[25]);
    aircraft.gpsTime.second = static_cast<int>(data[26]);

    // 输出解析的时间信息
    qDebug() << "时间: " << QString("%1-%2-%3 %4:%5:%6").arg(aircraft.gpsTime.year + 2000) .arg(aircraft.gpsTime.month, 2, 10, QChar('0'))  .arg(aircraft.gpsTime.day, 2, 10, QChar('0')) .arg(aircraft.gpsTime.hour, 2, 10, QChar('0')) .arg(aircraft.gpsTime.minute, 2, 10, QChar('0')) .arg(aircraft.gpsTime.second, 2, 10, QChar('0'));
    // //用来更新时间标签
    // QString Time =QString("%1-%2-%3 %4:%5:%6").arg(aircraft.gpsTime.year + 2000) .arg(aircraft.gpsTime.month, 2, 10, QChar('0'))  .arg(aircraft.gpsTime.day, 2, 10, QChar('0')) .arg(aircraft.gpsTime.hour, 2, 10, QChar('0')) .arg(aircraft.gpsTime.minute, 2, 10, QChar('0')) .arg(aircraft.gpsTime.second, 2, 10, QChar('0'));

    // qDebug() << "时间发送: " << Time;  // 输出发送的时间
    // emit gpsTimeudeUpdated(Time); //是QString类型





    // 东向速度、北向速度、天向速度（单位：cm/s -> 转换为 m/s）
    aircraft.eastSpeed = static_cast<qint16>(
                             (static_cast<unsigned char>(data[28]) << 8) |
                             static_cast<unsigned char>(data[27])) / 100.0;

    aircraft.northSpeed = static_cast<qint16>(
                              (static_cast<unsigned char>(data[30]) << 8) |
                              static_cast<unsigned char>(data[29])) / 100.0;

    aircraft.upSpeed = static_cast<qint16>(
                           (static_cast<unsigned char>(data[32]) << 8) |
                           static_cast<unsigned char>(data[31])) / 100.0;

    return aircraft;


}





// void Serial::onDataReceived() {
//     QByteArray data = serialPort->readAll();

//     // 缓存数据
//     DataBuf.append(data);

//     // 确保完整数据帧
//     while (DataBuf.size() >= 34) {
//         if (static_cast<unsigned char>(DataBuf[0]) != 0xEE || static_cast<unsigned char>(DataBuf[1]) != 0x81 ||
//             static_cast<unsigned char>(DataBuf[2]) != 0x22) {
//             // 丢弃无效数据
//             DataBuf.remove(0, 1);
//             continue;
//         }

//         // 提取一帧数据
//         QByteArray frame = DataBuf.left(34);
//        DataBuf.remove(0, 34);

//         // 解析数据
//         AircraftData aircraft = parseAircraftData(frame);
//        unsigned char checksum = 0;
//        for (int i = 0; i < 33; ++i) {
//            checksum += static_cast<unsigned char>(data[i]);
//        }
//        if (checksum != static_cast<unsigned char>(data[33])) {
//            qWarning() << "Checksum error!";
//            return aircraft;
//        }


//         // 更新地平仪
//         emit dataUpdated(aircraft);
//     }
// }
// void Serial::onDataReceived() {
//     QByteArray data = serialPort->readAll();
//     buffer.append(data);

//     while (buffer.size() >= 34) {
//         if (static_cast<unsigned char>(buffer[0]) != 0xEE || static_cast<unsigned char>(buffer[1]) != 0x81 ||
//             static_cast<unsigned char>(buffer[2]) != 0x22) {
//             buffer.remove(0, 1);
//             continue;
//         }

//         QByteArray frame = buffer.left(34);
//         buffer.remove(0, 34);

//         AircraftData aircraft = parseAircraftData(frame);
//         emit dataUpdated(aircraft);
//     }
//     qDebug() << "Received data:" << data;
// }


// void Serial::onDataReceived() {
//     QByteArray data = serialPort->readAll();
//     buffer.append(data);

//     qDebug() << "Received raw data size:" << data.size();
//     if (data.isEmpty()) {
//         qWarning() << "Received empty data!";
//         return; // 提前返回，避免后续操作
//     }

//     // 格式化显示接收到的原始数据
//     QString formattedData;
//     for (int i = 0; i < data.size(); ++i) {
//         formattedData += QString("%1 ").arg(static_cast<unsigned char>(data[i]), 2, 16, QChar('0')).toUpper();
//         if ((i + 1) % 16 == 0) { // 每 16 个字节换行
//             formattedData += "\n";
//         }
//     }
//     qDebug() << "Raw Data (Hex):\n" << formattedData;

//     // 处理缓冲区数据
//     while (buffer.size() >= 34) {
//         // 检查帧头
//         if (static_cast<unsigned char>(buffer[0]) != 0xEE || static_cast<unsigned char>(buffer[1]) != 0x81 ||
//             static_cast<unsigned char>(buffer[2]) != 0x22) {
//             qWarning() << "Invalid frame header detected. Removing first byte.";
//             buffer.remove(0, 1);
//             continue;
//         }

//         // 提取完整帧
//         QByteArray frame = buffer.left(34);
//         buffer.remove(0, 34);

//         // // 格式化显示完整帧
//         QString formattedFrame;
//         for (int i = 0; i < frame.size(); ++i) {
//             formattedFrame += QString("%1 ").arg(static_cast<unsigned char>(frame[i]), 2, 16, QChar('0')).toUpper();
//             if ((i + 1) % 16 == 0) {
//                 formattedFrame += "\n";
//             }
//         }
//         qDebug() << "Processed frame (Hex):\n" << formattedFrame;

//         // 解析数据
//         AircraftData aircraft = parseAircraftData(frame);

//         // 格式化显示解析后的数据
//         // qDebug().noquote() << "=========================================";
//         // qDebug().noquote() << "Parsed Aircraft Data:";
//         // qDebug().noquote() << QString("  Roll: %1° | Pitch: %2° | Yaw: %3°")
//         //                           .arg(aircraft.roll, 0, 'f', 2)
//         //                           .arg(aircraft.pitch, 0, 'f', 2)
//         //                           .arg(aircraft.yaw, 0, 'f', 2);
//         // qDebug().noquote() << QString("  Latitude: %1 | Longitude: %2")
//         //                           .arg(aircraft.latitude, 0, 'f', 7)
//         //                           .arg(aircraft.longitude, 0, 'f', 7);
//         // qDebug().noquote() << QString("  GPS Altitude: %1 m | Relative Altitude: %2 m")
//         //                           .arg(aircraft.gpsAltitude, 0, 'f', 1)
//         //                           .arg(aircraft.relAltitude, 0, 'f', 1);
//         // qDebug().noquote() << QString("  East Speed: %1 m/s | North Speed: %2 m/s | Up Speed: %3 m/s")
//         //                           .arg(aircraft.eastSpeed, 0, 'f', 2)
//         //                           .arg(aircraft.northSpeed, 0, 'f', 2)
//         //                           .arg(aircraft.upSpeed, 0, 'f', 2);
//         // qDebug().noquote() << "=========================================";

//         emit dataUpdated(aircraft);
//     }

//     // 如果缓冲区中有剩余数据，显示未处理的内容
//     if (!buffer.isEmpty()) {
//         qDebug() << "Remaining buffer (incomplete data):" << buffer.toHex(' ').toUpper();
//     }
// }

// void Serial::onDataReceived() {
//     QByteArray data = serialPort->readAll();
//     buffer.append(data);

//     // 格式化显示接收到的原始数据
//     QString formattedData;
//     for (int i = 0; i < data.size(); ++i) {
//         formattedData += QString("%1 ").arg(static_cast<unsigned char>(data[i]), 2, 16, QChar('0')).toUpper();
//         if ((i + 1) % 16 == 0) {
//             formattedData += "\n"; // 每 16 个字节换行
//         }
//     }
//     qDebug() << "Raw Data (Hex):\n" << formattedData;

//     while (buffer.size() >= 34) {
//         if (static_cast<unsigned char>(buffer[0]) != 0xEE || static_cast<unsigned char>(buffer[1]) != 0x81 ||
//             static_cast<unsigned char>(buffer[2]) != 0x22) {
//             buffer.remove(0, 1);
//             continue;
//         }

//         QByteArray frame = buffer.left(34);
//         buffer.remove(0, 34);

//         AircraftData aircraft = parseAircraftData(frame);

//         // // 格式化显示解析后的数据
//         // qDebug() << "Parsed Aircraft Data:";
//         // qDebug() << QString("Roll: %1° | Pitch: %2° | Yaw: %3°")
//         //                 .arg(aircraft.roll, 0, 'f', 2)
//         //                 .arg(aircraft.pitch, 0, 'f', 2)
//         //                 .arg(aircraft.yaw, 0, 'f', 2);
//         // qDebug() << QString("Latitude: %1 | Longitude: %2")
//         //                 .arg(aircraft.latitude, 0, 'f', 7)
//         //                 .arg(aircraft.longitude, 0, 'f', 7);
//         // qDebug() << QString("GPS Altitude: %1 m | Relative Altitude: %2 m")
//         //                 .arg(aircraft.gpsAltitude, 0, 'f', 1)
//         //                 .arg(aircraft.relAltitude, 0, 'f', 1);
//         // qDebug() << QString("East Speed: %1 m/s | North Speed: %2 m/s | Up Speed: %3 m/s")
//         //                 .arg(aircraft.eastSpeed, 0, 'f', 2)
//         //                 .arg(aircraft.northSpeed, 0, 'f', 2)
//         //                 .arg(aircraft.upSpeed, 0, 'f', 2);

//         emit dataUpdated(aircraft);
//     }
// }



void Serial::onDataReceived() {
    QByteArray data = serialPort->readAll();
    buffer.append(data);

    // 直接输出原始数据
    qDebug() << "原始数据:" << data;
    // 在每个字节之间插入分隔符（空格）
    QString hexString = data.toHex().toUpper();
    QString hexWithSeparator;
    for (int i = 0; i < hexString.length(); i += 2) {
        if (i > 0) {
            hexWithSeparator += " ";  // 插入分隔符
        }
        hexWithSeparator += hexString.mid(i, 2);
    }
    // 显示原始数据的十六进制格式
    qDebug() << "十六进制:" << hexWithSeparator;

    while (buffer.size() >= 34) {
        // 检查帧头
        if (static_cast<unsigned char>(buffer[0]) != 0xEE || static_cast<unsigned char>(buffer[1]) != 0x81 ||
            static_cast<unsigned char>(buffer[2]) != 0x22) {
            buffer.remove(0, 1);
            continue;
        }

        QByteArray frame = buffer.left(34);
        buffer.remove(0, 34);

        AircraftData aircraft = parseAircraftData(frame);
        //qDebug() << "Raw Roll Bytes:" << data.mid(4, 2).toHex();
        //qDebug() << "Parsed Roll:" << aircraft.roll;
        // 输出解析后的数据
        qDebug() << "解析后的数据:"
                 << "Roll:" << aircraft.roll
                 << "Pitch:" << aircraft.pitch
                 << "Yaw:" << aircraft.yaw
                 << "Latitude:" << aircraft.latitude
                 << "Longitude:" << aircraft.longitude
                 << "GPS Altitude:" << aircraft.gpsAltitude
                 << "Relative Altitude:" << aircraft.relAltitude
                 << "East Speed:" << aircraft.eastSpeed
                 << "North Speed:" << aircraft.northSpeed
                 << "Up Speed:" << aircraft.upSpeed;

        emit dataUpdated(aircraft);
    }

    // 显示剩余未处理数据
    if (!buffer.isEmpty()) {
        qDebug() << "未解析的数据:" << buffer;
    }
}


Serial::~Serial()
{
    serialPort->close(); // 关闭串口
    serialPort->clear(QSerialPort::Input); // 清空输入缓冲区
}

