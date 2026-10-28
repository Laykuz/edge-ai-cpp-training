#include "SensorModule.hpp"
#include <iostream>

// 범위 지정 연산자(::)를 사용하여 SensorModule 클래스의 생성자 정의
SensorModule::SensorModule(std::string name, size_t size)  
    : sensor_name_(std::move(name)), data_(size, 3.14) { // 외부에서 받아온 name을 복사 비용 없이 즉시 훔쳐 와서(std::move) 멤버 변수 sensor_name_에 곧바로 꽂아넣습니다.
    std::cout << "[Constructor] " << sensor_name_ << " allocated\n";
}

// 이동 생성자 및 기타 함수 구현부 작성...