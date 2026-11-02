#pragma once
#include <string>
#include <vector>

/**
 * @brief 비전 센서가 감지한 객체의 바운딩 박스 정보
 */
struct BoundingBox {
    float x;      ///< X 좌표 (단위: 픽셀 [px], 유효 범위: 0.0 ~ 1920.0)
    float y;      ///< Y 좌표 (단위: 픽셀 [px], 유효 범위: 0.0 ~ 1080.0)
    float width;  ///< 너비 (단위: 픽셀 [px])
    float height; ///< 높이 (단위: 픽셀 [px])
};

/**
 * @brief 다중 센서로부터 융합된 최종 이벤트 결과물
 */
struct FusedEvent {
    int event_id;             ///< 이벤트 고유 식별 번호
    double timestamp;         ///< 발생 시간 기준 (단위: 밀리초 [ms], 기준: 시스템 부팅 시점 Monotonic Clock)
    double relative_distance; ///< 감지된 객체와의 상대 거리 (단위: 미터 [m], 유효 범위: 0.1 ~ 100.0)
    double velocity;          ///< 객체의 접근/이탈 속도 (단위: 미터퍼세크 [m/s], 유효 범위: -50.0 ~ 50.0)
    bool is_hazardous;        ///< 위험 물질 여부 판정 (true: 위험, false: 안전)
};

/**
 * @brief 센서 데이터를 관리하고 이동 의미론을 지원하는 모듈 클래스
 */
class SensorModule {
public:
    SensorModule(std::string name, size_t size);
    ~SensorModule();

    // 이동 생성자 / 이동 대입 연산자선언
    SensorModule(SensorModule&& other) noexcept;
    SensorModule& operator=(SensorModule&& other) noexcept;

    void processData();

private:
    std::string sensor_name_;
    std::vector<double> data_;
};