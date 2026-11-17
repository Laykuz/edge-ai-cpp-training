#include <iostream>
#include <thread>
#include <stdexcept>

// RAII 기반 스레드 가드 클래스 (스코프를 벗어나면 알아서 join 해줌)
class ThreadGuard {
    std::thread t;
public:
    explicit ThreadGuard(std::thread&& th) : t(std::move(th)) {}
    ~ThreadGuard() {
        if (t.joinable()) {
            t.join(); // 소멸할 때 안전하게 join 보장
            std::cout << "[ThreadGuard] 소멸자에서 안전하게 스레드 join 완료\n";
        }
    }
    // 복사 생성 금지
    ThreadGuard(const ThreadGuard&) = delete;
    ThreadGuard& operator=(const ThreadGuard&) = delete;
};

void riskyTask() {
    // 작업 수행
}

int main() {
    std::cout << "[Main] 안전한 스레드 테스트 시작\n";

    try {
        // 스레드를 만들자마자 ThreadGuard에 소유권을 넘김
        ThreadGuard g(std::thread(riskyTask));

        // 예외가 터져도 안전
        throw std::runtime_error("치명적인 예외 발생");
    } 
    catch (const std::exception& e) {
        std::cout << "예외 캐치함: " << e.what() << "\n";
    }

    // 가드 객체가 스코프를 벗어나면서 알아서 안전하게 join을 처리하므로 크래시 없음
    std::cout << "[Main] 프로그램이 터지지 않음\n";
    return 0;
}