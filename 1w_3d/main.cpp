// main.cpp
#include <iostream>
#include "types.hpp" // 우리가 만든 헤더 파일 포함

int main() {
    // types.hpp에 선언된 SensorData 구조체 사용
    SensorData mySensor;
    mySensor.sensorId = 101;
    mySensor.value = 23.5;
    mySensor.status = "ACTIVE";

    std::cout << "--- Sensor Report ---" << std::endl;
    std::cout << "ID: " << mySensor.sensorId << std::endl;
    std::cout << "Value: " << mySensor.value << " °C" << std::endl;
    std::cout << "Status: " << mySensor.status << std::endl;

    return 0;
}