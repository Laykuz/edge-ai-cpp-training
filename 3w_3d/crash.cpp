#include <iostream>
#include <thread>
#include <stdexcept>

void riskyTask() {
    // 잠시 대기
}

int main() {
    std::cout << "[Main] 위험 스레드 테스트 시작\n";

    try {
        std::thread t(riskyTask);

        // 스레드가 만들어진 직후에 어떠한 이유로 예외가 발생
        throw std::runtime_error("치명적인 예외가 터졌습니다");

        // 예외 때문에 이 코드는 실행되지 않고 건너뜀
        t.join(); 
    } 
    catch (const std::exception& e) {
        std::cout << "예외 캐치함: " << e.what() << "\n";
    }

    // [크래시 지점] 
    // try-catch 블록을 빠져나오면서 스레드 객체 `t`의 소멸자가 호출되는데,
    // `t`는 여전히 `join()`되지 않은 `joinable()` 상태이므로 C++ 런타임이 프로그램을 강제 종료(std::terminate)
    
    std::cout << "[Main] 이 문장은 절대 출력되지 않고 프로그램이 터집니다.\n";
    return 0;
}