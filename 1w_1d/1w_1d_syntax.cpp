#include <iostream>
#include <string>

// 센서 데이터를 흉내 낸 간단한 구조체
struct SensorData {
    int id;
    double temperature;
};

// 1. Pass by Reference (참조에 의한 전달)
// - 복사 비용 없이 원본 데이터를 직접 수정(Mutate)할 때 사용합니다.
void updateTemperature(double& targetTemp, double newTemp) {
    targetTemp = newTemp; // targetTemp는 원본의 '별명(Alias)'이므로 바깥의 원본도 함께 바뀝니다.
}

// 2. Const Reference (상수 참조)
// - 데이터를 수정할 일은 없지만, 큰 데이터를 복사하는 비용(Performance Cost)을 아끼고 싶을 때 씁니다. (읽기 전용)
void printSensorInfo(const SensorData& data) {
    // data.temperature = 30.0; // ❌ 에러! const가 붙어 있어서 값을 바꿀 수 없습니다 (안전성 보장).
    std::cout << "[Sensor ID: " << data.id << "] Temp: " << data.temperature << "°C\n";
}

int main() {
    // --- [기본 변수 선언] ---
    double currentTemp = 25.5; // 실제 데이터가 저장된 원본 변수
    SensorData roomSensor = {101, currentTemp};

    std::cout << "=== 1. 초기 상태 및 Const Reference ===\n";
    printSensorInfo(roomSensor); // 상수 참조를 통해 안전하게 데이터 출력

    // =========================================================================
    // --- [Reference (참조) 활용] ---
    // =========================================================================
    // 특징: 
    // 1) 선언과 동시에 반드시 누군가의 '별명(Alias)'이 되어야 합니다.
    // 2) 한 번 정해진 대상을 중간에 바꿀 수 없습니다.
    // 3) 항상 유효한 대상을 가리키므로 Null일 수 없습니다 (안전함).
    
    double& tempRef = currentTemp; // tempRef는 currentTemp의 '진짜 별명'입니다.
    tempRef = 26.8;                // 별명을 통해 값을 바꾸면...

    std::cout << "\n=== 2. 참조(Reference)를 통한 값 변경 후 ===\n";
    std::cout << "currentTemp 값: " << currentTemp << " (참조를 통해 함께 변경됨)\n";

    // 함수를 통한 참조 전달 실습
    updateTemperature(currentTemp, 28.1);
    std::cout << "함수 실행 후 currentTemp: " << currentTemp << "\n";


    // =========================================================================
    // --- [Pointer (포인터) 활용] ---
    // =========================================================================
    // 특징:
    // 1) 변수의 '메모리 주소(Address)'를 값으로 가지는 별도의 변수입니다.
    // 2) 프로그램 실행 중에 가리키는 대상을 다른 곳으로 **갈아탈 수(Reassignment)** 있습니다.
    // 3) 가리키는 대상이 없음을 나타내는 **Null Pointer (`nullptr`)**를 가질 수 있습니다.

    double altTemp = 35.0; // 비교용 다른 변수
    
    double* tempPtr = &currentTemp; // tempPtr이라는 포인터 변수에 currentTemp의 '주소(&)'를 담음
    std::cout << "\n=== 3. 포인터(Pointer) 활용 ===\n";
    std::cout << "포인터가 담고 있는 주소값: " << tempPtr << "\n";
    
    // Dereference (역참조, *): 포인터가 가진 주소로 찾아가서 그 안의 값을 꺼내거나 수정함
    std::cout << "역참조(*tempPtr)를 통한 값 접근: " << *tempPtr << "\n";

    // 포인터의 특권 1: 가리키는 대상을 다른 변수로 갈아타기 (참조는 절대 불가능!)
    tempPtr = &altTemp; // 이제 altTemp의 주소를 가리키도록 대상을 변경함!
    std::cout << "갈아탄 후 포인터가 가리키는 값: " << *tempPtr << "\n";

    // 포인터의 특권 2: 가리키는 대상이 없음을 명시하는 nullptr 대입
    double* emptyPtr = nullptr; 
    if (emptyPtr == nullptr) {
        std::cout << "emptyPtr은 현재 유효한 대상을 가리키고 있지 않습니다 (Null Pointer 체크).\n";
    }

    return 0;
}