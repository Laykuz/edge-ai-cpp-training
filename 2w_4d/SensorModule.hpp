#pragma once // 중복으로 인클루드(include)되는 것을 방지
#include <string>
#include <vector>

// 센서가 감지한 좌표 데이터나 결과 묶음을 담기 위한 가벼운 데이터 구조체들의 뼈대입니다. 
// 상세 구현은 .cpp나 다른 곳에서 확장될 수 있도록 선언만 먼저 해둡니다
struct BoundingBox { /* ... */ };
struct SensorResult { /* ... */ };



class SensorModule {
public:
    SensorModule(std::string name, size_t size);
    ~SensorModule();

    // 이동 생성자 / 이동 대입 연산자 선언
    SensorModule(SensorModule&& other) noexcept;
    SensorModule& operator=(SensorModule&& other) noexcept;

    void processData();

private:
    std::string sensor_name_;
    std::vector<double> data_;
};