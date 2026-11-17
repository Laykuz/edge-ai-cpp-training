#include <iostream>
#include <thread>
#include <chrono> // 시간 지연을 주기 위한 라이브러리

// 백그라운드에서 동작할 작업 함수
void backgroundTask(int id) {
    std::cout << "[Worker " << id << "] 백그라운드 작업 시작!\n";
    
    // 무거운 AI 연산이나 센서 데이터 수집을 2초 동안 수행한다고 가정
    std::this_thread::sleep_for(std::chrono::seconds(2)); 
    
    std::cout << "[Worker " << id << "] 백그라운드 작업 완료!\n";
}

int main() {
    std::cout << "[Main] 메인 스레드 시작\n";

    // 1. 백그라운드 스레드 생성 (생성과 동시에 worker 함수 실행 시작)
    std::thread workerThread(backgroundTask, 42);

    std::cout << "[Main] 메인 스레드는 자기 할 일을 계속 수행 중...\n";

    // 2. 백그라운드 스레드가 끝날 때까지 안전하게 대기 (종료 타이밍 제어)
    if (workerThread.joinable()) {
        workerThread.join(); // 여기서 자식 스레드가 끝날 때까지 메인 스레드가 멈춰서 기다림
        std::cout << "[Main] 백그라운드 스레드 join 완료. 안전하게 동기화됨!\n";
    }

    std::cout << "[Main] 프로그램 정상 종료\n";
    return 0;
}