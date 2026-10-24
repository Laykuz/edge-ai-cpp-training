#include <iostream>
#include <chrono>
#include <thread>
#include <string>

// 1. 시스템 상태를 나타내는 enum class 정의 (범위 지정 열거형)
enum class SystemStatus {
    IDLE,       // 대기 상태 (Idle)
    RUNNING,    // 정상 작동 중 (Running)
    WARNING,    // 주의 / 경고 (Warning)
    ERROR       // 비상 / 에러 (Error)
};

class SystemStatusRecord {
private:
    int sensor_id_;             // 센서 ID
    SystemStatus status_;       // 시스템 상태 (enum class)
    
    // 2. 정밀한 타임스탬프를 기록하는 std::chrono 필드 (Timestamp field)
    std::chrono::steady_clock::time_point timestamp_;

public:
    // 3. 생성자 (Constructor) 및 초기화 리스트 (Initializer List)
    SystemStatusRecord(int sensor_id, SystemStatus status)
        : sensor_id_(sensor_id),
          status_(status),
          timestamp_(std::chrono::steady_clock::now()) // 객체가 생성되는 찰나의 시간 기록!
    {
    }

    // 4. 안전한 읽기 전용 창구 (const Member Functions / Getters)
    int getSensorId() const {
        return sensor_id_;
    }

    SystemStatus getStatus() const {
        return status_;
    }

    // enum 값을 사람이 읽기 좋은 문자열로 변환해주는 헬퍼 함수
    std::string getStatusString() const {
        switch (status_) {
            case SystemStatus::IDLE:    return "IDLE (대기)";
            case SystemStatus::RUNNING: return "RUNNING (정상 작동)";
            case SystemStatus::WARNING: return "WARNING (경고)";
            case SystemStatus::ERROR:   return "ERROR (에러 발생)";
            default:                    return "UNKNOWN";
        }
    }

    // 5. 타임스탬프를 활용해 객체 생성 후 경과된 시간(ms)을 계산하는 함수
    long long getElapsedMilliseconds() const {
        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - timestamp_);
        return duration.count();
    }
};

int main() {
    std::cout << "--- [Edge AI 시스템 상태 모니터링 시뮬레이션] ---\n\n";

    // 센서 객체 생성 (이 순간 정확한 타임스탬프가 찍힙니다)
    SystemStatusRecord sensor_log(101, SystemStatus::RUNNING);

    // 센서가 작동하며 시간이 흐르는 것을 시뮬레이션 (1.2초 대기)
    std::this_thread::sleep_for(std::chrono::milliseconds(1200));

    // 메인 함수에서 Getter를 통해 안전하게 정보 조회
    std::cout << "센서 ID: " << sensor_log.getSensorId() << "\n";
    std::cout << "현재 상태: " << sensor_log.getStatusString() << "\n";
    std::cout << "데이터 수집 후 경과 시간: " << sensor_log.getElapsedMilliseconds() << " ms\n";

    return 0;
}

// std::mutex
// 멀티 스레드 프로그래밍에서는 여러 스레드가 동시에 변수나 메모리에 접근해 값을 수정하려고 하면 
// 경쟁 상태(race condition)가 발생하여 데이터가 오염되거나 예측할 수 없는 버그가 생깁니다.
// std::mutex는 특정 코드 블록(임계 구역, Critical Section)에 단 하나의 스레드만 진입할 수 있도록 보장해 줍니다.