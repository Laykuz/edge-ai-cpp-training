#include <iostream>
#include "types.h"

int main() {
    std::cout << "=== Edge AI Sensor & Vision Data Test ===" << std::endl;

    // 1. 비전 데이터 객체 생성 및 초기화
    VisionData camera_frame = {
        101,
        "pedestrian",
        0.95f,
        {100, 200, 50, 120} // x, y, w, h
    };

    // 2. 센서 데이터 객체 생성 및 초기화
    SensorData lidar_sensor = {
        1,
        3.42,
        42.5f,
        true
    };

    // 3. 값 변경 및 추적용 로직 (디버그 중단점 걸 위치)
    if (lidar_sensor.is_active) {
        lidar_sensor.distance_m -= 0.5; // 거리가 가까워짐을 가상 처리
    }

    if (camera_frame.confidence > 0.9f) {
        std::cout << "[VISION] High confidence object detected: " 
                  << camera_frame.label << std::endl;
    }

    std::cout << "[LiDAR] Distance: " << lidar_sensor.distance_m << "m" << std::endl;

    return 0;
}