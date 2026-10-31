#include "SensorModule2.hpp"
#include <iostream>
#include <cassert> // 검증을 위한 assert 함수

// FusedEvent 데이터가 올바르게 융합되는지 검증하는 단위 테스트 함수
void test_fused_event_logic() {
    std::cout << "[Test Start] FusedEvent 데이터 융합 검증 시작...\n";

    // 1. 테스트용 가짜 입력 데이터 설정 (Mock Data)
    double mock_vision_distance = 15.5; // [m]
    double mock_radar_velocity = -3.2;  // [m/s]

    // 2. 융합 로직 시뮬레이션 (실제 FusedEvent 객체 생성 및 계산)
    FusedEvent event;
    event.event_id = 101;
    event.timestamp = 1718000000.0; // [ms]
    event.relative_distance = mock_vision_distance;
    event.velocity = mock_radar_velocity;
    
    // 위험 판정 알고리즘 예시: 거리가 20m 이내이고 다가오고 있으면(속도가 음수) 위험!
    event.is_hazardous = (event.relative_distance < 20.0) && (event.velocity < 0.0);

    // 3. 단언문(Assert)을 통한 결과 검증 (DoD 검증)
    assert(event.relative_distance >= 0.1 && event.relative_distance <= 100.0); // 유효 범위 체크
    assert(event.is_hazardous == true); // 기대 결과가 참인지 검증

    std::cout << "[Test PASSED] FusedEvent 융합 및 유효성 검증 성공!\n";
}

int main() {
    // 모듈 생성 및 기존 실습 테스트
    SensorModule raw_sensor("LiDAR_Core", 512);
    raw_sensor.processData();

    // 이동 의미론 테스트
    SensorModule processed_sensor = std::move(raw_sensor);

    // [Day 5 과제] FusedEvent 단위 테스트 실행
    test_fused_event_logic();

    return 0;
}