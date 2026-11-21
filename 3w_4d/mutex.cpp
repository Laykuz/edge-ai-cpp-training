#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

// 공유 자원 (여러 스레드가 동시에 덤벼서 값을 깎아먹을 변수)
long long g_counter = 0;

// 스레드 A가 임계 구역에 들어가기 전에 std::mutex를 먼저 잠급니다. 
// 그러면 스레드 B, C, D는 자물쇠가 잠긴 것을 보고 문 앞에서 멈춰 서서 스레드 A가 일을 끝내고 자물쇠를 열 때까지 기다립니다. 즉, 임계 구역 안에는 항상 한 번에 한 스레드만 들어가게 만드는 출입 통제 장치
std::mutex g_mtx;

//
void race_worker(int interatons) {
    for (int i = 0; i < interatons; ++i) {
        g_counter++; // 원자적(Atomic) 연산이 아니라서 데이터가 깨집니다!
    }
}

// std::lock_guard로 보호하는 함수
void safe_worker(int interatons) {
    for (int i = 0; i < interatons; ++i) {
        std::lock_guard<std::mutex> lock(g_mtx); // RAII 락 가드: 생성될 때 잠그고, 스코프를 벗어날 때(for문 한바퀴 또는 함수 종료) 자동 해제!
        g_counter++; 
    }
}

int main() {
    std::cout << "=== 멀티스레드 데이터 레이스 & 동기화 실습 ===\n\n";

    const int num_threads = 10;
    const int iterations_per_thread = 100000; // 스레드당 10만 번 연산

    // C++에서 연산은 피연산자의 타입을 기준으로 계산됩니다. 만약 형변환 없이 num_threads * iterations_per_thread처럼 int끼리 먼저 곱하게 되면, 
    // 값이 커질 때 곱셈 결과가 대입되기 전에 int 범위(일반적으로 약 21억)를 넘어 오버플로우(overflow, 정수 오버플로우)가 먼저 터질 위험
    const long long target_total = (long long)num_threads * iterations_per_thread; // 기대값: 1,000,000

    
    // ==========================================
    // [실험 1] 락 없이 실행하기 (Data Race 유발)
    // ==========================================
    g_counter = 0; // 초기화
    {
        std::vector<std::thread> threads;
        threads.reserve(num_threads);

        //
        for (int i = 0; i < num_threads; ++i) {
            threads.emplace_back(race_worker, iterations_per_thread);
        }

        //
        for (auto& t : threads) {
            t.join();
        }
    }

    std::cout << "[실험 1: 락 없음] 목표값: " << target_total << "\n";
    std::cout << "[실험 1: 락 없음] 실제값: " << g_counter << " (값이 유실되었습니다!)\n\n";
    
    // ==========================================
    // [실험 2] std::lock_guard로 보호하며 실행하기
    // ==========================================
    g_counter = 0; // 초기화
    {
        std::vector<std::thread> threads;
        threads.reserve(num_threads);

        //
        for (int i = 0; i < num_threads; ++i) {
            threads.emplace_back(safe_worker, iterations_per_thread);
        }

        //
        for (auto& t : threads) {
            t.join();
        }
    }
}

