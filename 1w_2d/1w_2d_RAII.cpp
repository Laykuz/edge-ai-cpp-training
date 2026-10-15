#include <iostream>
#include <memory> // 스마트 포인터를 쓰기 위한 헤더

// 객체가 생성되고 소멸될 때를 눈으로 확인하기 위한 테스트용 클래스
class Resource {
public:
    Resource(int id) : id_(id) {
        std::cout << "👉 [생성됨] Resource ID: " << id_ << "\n";
    }
    
    ~Resource() {
        std::cout << "🗑️ [소멸됨(메모리 해제)] Resource ID: " << id_ << "\n";
    }

    void doSomething() {
        std::cout << "⚡ 작업 실행 중... ID: " << id_ << "\n";
    }

private:
    int id_;
};

void testUniquePtr() {
    std::cout << "\n--- [1. std::unique_ptr 테스트 시작] ---\n";
    
    // 유니크 포인터 생성 (make_unique 권장)
    std::unique_ptr<Resource> res1 = std::make_unique<Resource>(1);
    res1->doSomething();

    // 소유권 이전 테스트
    // std::unique_ptr<Resource> res2 = res1; // ❌ 에러 발생 (복사 불가)
    std::unique_ptr<Resource> res2 = std::move(res1); // ✅ 소유권 이전 (res1은 이제 텅 빔)

    if (res1 == nullptr) {
        std::cout << "⚠️ res1은 이제 소유권을 잃어버려서 비어 있습니다(nullptr).\n";
    }

    res2->doSomething();
    std::cout << "--- [1. std::unique_ptr 테스트 종료 (이 스코프를 벗어날 때 res2 자동 소멸)] ---\n";
} // 👈 이 블록을 탈출하는 순간, res2가 관리하던 Resource(1)가 자동으로 delete됨!

void testSharedPtr() {
    std::cout << "\n--- [2. std::shared_ptr 테스트 시작] ---\n";
    
    std::shared_ptr<Resource> shared1 = std::make_shared<Resource>(2);
    std::cout << "현재 참조 횟수(use_count): " << shared1.use_count() << "\n";

    {
        std::shared_ptr<Resource> shared2 = shared1; // ✅ 복사 가능 (공유)
        std::cout << "-> 내부 블록 진입 후 참조 횟수: " << shared1.use_count() << "\n";
        shared2->doSomething();
    } // 👈 이 블록을 나가면서 shared2는 소멸하지만, Resource(2)는 아직 살아있음!

    std::cout << "-> 내부 블록 탈출 후 참조 횟수: " << shared1.use_count() << "\n";
    std::cout << "--- [2. std::shared_ptr 테스트 종료 (이 스코프를 벗어날 때 마지막 shared1 소멸)] ---\n";
} // 👈 여기서 shared1이 소멸하면서 참조 횟수가 0이 되어 Resource(2)가 자동 delete됨!

int main() {
    // 한글 출력이 깨지지 않기 위한 설정 (윈도우 환경 대응)
    #ifdef _WIN32
    // (이미 앞서 터미널 인코딩을 잡아두셨으므로 한글이 잘 출력될 것입니다!)
    #endif

    std::cout << "=== 프로그램 시작 ===" << "\n";

    testUniquePtr();
    testSharedPtr();

    std::cout << "=== 프로그램 종료 ===" << "\n";
    return 0;
}