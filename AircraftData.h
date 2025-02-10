#ifndef AIRCRAFTDATA_H
#define AIRCRAFTDATA_H
#include <cstdint>
#include"GpsTime.h"

struct AircraftData {
    int16_t roll;       // 横滚角（单位：度）
    int16_t pitch;      // 俯仰角（单位：度）
    int16_t yaw;        // 航向角（单位：度）
    double latitude;   // 纬度（实际值）
    double longitude;  // 经度（实际值）
    float gpsAltitude;  // GPS高度（单位：米）
    float relAltitude;  // 相对高度（单位：米）
    GpsTime gpsTime;      // GPS时间（年、月、日、时、分、秒）
    float eastSpeed;    // 东向速度（单位：m/s）
    float northSpeed;   // 北向速度（单位：m/s）
    float upSpeed;      // 天向速度（单位：m/s）
};
#endif // AIRCRAFTDATA_H
//int16_t
