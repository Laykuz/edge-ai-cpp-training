#include <iostream>
#include <string>     // 1. 안전한 문자열
#include <vector>     // 2. 동적 배열 (Dynamic Array)
#include <array>      // 3. 고정 크기 배열 (Fixed-size Array)
#include <optional>   // 4. 값이 없을 수 있음을 표현하는 선택적 값 (Optional Value)

// 4. std::optional을 활용하는 예제 함수
// - 특정 센서 ID를 검색하여, 찾으면 온도를 반환하고 못 찾으면 '값이 없음(std::nullopt)'을 반환합니다.
std::optional<double> findSensorTemperature(int sensorId) {
    if (sensorId == 101) {
        return 25.5; // 값이 존재하는 경우
    }
    // 만약 101번이 아니라면 찾지 못했으므로 빈 값을 반환
    return std::nullopt; // No Value (Null Optional)
}

int main() {
    // =========================================================================
    // --- [1. std::string: 안전하고 편리한 문자열] ---
    // =========================================================================
    // 특징: C 스타일의 char 배열처럼 크기나 \0(Null 문자)을 직접 신경 쓸 필요 없이
    //       알아서 메모리를 관리해주며, + 연산자로 쉽게 이어 붙일 수 있습니다.
    std::cout << "=== 1. std::string 예제 ===\n";
    std::string deviceName = "Edge-AI-Hub";
    std::string status = "Online";
    std::string info = deviceName + " Status: " + status; // 문자열 결합
    
    std::cout << info << "\n\n";


    // =========================================================================
    // --- [2. std::vector: 크기가 자유자재로 늘어나는 동적 배열] ---
    // =========================================================================
    // 특징: 프로그램 실행 중에 데이터가 얼마나 들어올지 모를 때 사용합니다.
    //       데이터가 추가되면 힙(Heap) 메모리 공간을 알아서 늘려줍니다.
    std::cout << "=== 2. std::vector (동적 배열) 예제 ===\n";
    std::vector<double> temperatureLogs = {24.0, 25.2}; // 초기 데이터 설정
    
    temperatureLogs.push_back(26.8); // 뒤쪽에 새로운 데이터를 추가 (크기 자동 확장)
    temperatureLogs.push_back(27.5);

    std::cout << "온도 로그 목록: ";
    for (double temp : temperatureLogs) {
        std::cout << temp << "°C ";
    }
    std::cout << "\n총 로그 개수(size): " << temperatureLogs.size() << "\n\n";


    // =========================================================================
    // --- [3. std::array: 크기가 고정된 안전한 정적 배열] ---
    // =========================================================================
    // 특징: 크기가 절대 바뀌지 않는 고정 배열을 쓸 때 C 스타일 배열 대신 씁니다.
    //       자기가 크기가 얼마인지 알고 있고(.size()), 범위를 안전하게 체크할 수 있습니다.
    std::cout << "=== 3. std::array (고정 크기 배열) 예제 ===\n";
    // 크기가 3으로 딱 고정된 센서 ID 목록
    std::array<int, 3> fixedSensorIds = {101, 102, 103}; 

    std::cout << "고정 배열 첫 번째 ID: " << fixedSensorIds[0] << "\n";
    std::cout << "고정 배열 크기(size): " << fixedSensorIds.size() << "\n\n";


    // =========================================================================
    // --- [4. std::optional: 값이 없을 수도 있음을 표현하는 안전장치] ---
    // =========================================================================
    // 특징: 함수가 결과를 찾지 못했을 때 -1이나 무효한 포인터를 리턴하던 과거의 혼란을 없애고,
    //       "값이 존재할 수도 있고 없을 수도 있음"을 명시적으로 표현합니다. (C++17 도입)
    std::cout << "=== 4. std::optional 예제 ===\n";
    
    int searchId = 999; // 존재하지 않는 센서 ID 검색 시도
    auto result = findSensorTemperature(searchId);

    // .has_value()로 값이 들어있는지 안전하게 확인 가능
    if (result.has_value()) {
        std::cout << searchId << "번 센서 온도: " << result.value() << "°C\n";
    } else {
        std::cout << searchId << "번 센서를 찾을 수 없습니다 (No Value 발견).\n";
    }

    return 0;
}