// 사실 요즘 컴파일러들은 전부 똑똑해서 #pragma once를 지원하기 때문에 훨씬 짧고 편한 #pragma once를 많이 씁니다.
// 하지만 아주 오래된 레거시 시스템이나 특수한 컴파일러 중에는 #pragma once를 완벽히 지원하지 못하는 경우도 있어서, 
// C++ 교과서나 대형 오픈소스 프로젝트에서는 여전히 방어력이 가장 확실한 인클루드 가드(#ifndef)를 
// 정석으로 가르치고 사용합니다.

#ifndef TYPES_H
#define TYPES_H

#include <iostream>
#include <string>

// 1. 비전(Vision) 센서 데이터 구조체
struct VisionData {
    int object_id;           // 물체 식별 ID
    std::string label;       // 인식된 클래스 (예: "person", "car")
    float confidence;        // 신뢰도 (0.0 ~ 1.0)
    int bbox[4];             // Bounding Box 좌표 [x, y, width, height]
                             // AI(컴퓨터 비전)가 카메라 화면에서 사람이나 자동차를 찾아냈을 때, 
                             //  그 물체가 화면 어디에 있는지 표시하기 위해 네모난 박스의 위치와 크기를 
                             //  숫자로 표현한 것입니다.
};

// 2. 센서(Sensor) 데이터 구조체
struct SensorData {
    int sensor_id;           // 센서 ID
    double distance_m;       // 측정 거리 (미터 단위)
    float temperature_c;     // 센서 온도 (섭씨)
    bool is_active;          // 센서 작동 여부
};

#endif // TYPES_H