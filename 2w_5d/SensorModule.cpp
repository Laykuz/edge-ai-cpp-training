#include "SensorModule2.hpp" // 헤더 파일 이름에 맞춰서 수정해주세요!
#include <iostream>
#include <utility>

// constructor (생성자)
SensorModule::SensorModule(std::string name, size_t size)
    : sensor_name_(std::move(name)), data_(size) {
    // 필요한 초기화 로직 작성
}

// destructor (소멸자)
SensorModule::~SensorModule() {
    // 필요한 정리 로직 작성
}

// Move constructor (이동 생성자)
SensorModule::SensorModule(SensorModule&& other) noexcept
    : sensor_name_(std::move(other.sensor_name_)), data_(std::move(other.data_)) {
}

// Move assignment operator (이동 대입 연산자)
SensorModule& SensorModule::operator=(SensorModule&& other) noexcept {
    if (this != &other) {
        sensor_name_ = std::move(other.sensor_name_);
        data_ = std::move(other.data_);
    }
    return *this;
}

// member function (멤버 함수)
void SensorModule::processData() {
    // 데이터 처리 로직 구현
}