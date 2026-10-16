// 이 헤더 파일은 컴파일 과정에서 단 한 번만 포함(include)되도록 해라
#pragma once

#include <string>

// 센서 데이터를 담는 구조체 선언
struct SensorData {
    int sensorId;
    double value;
    std::string status;
};