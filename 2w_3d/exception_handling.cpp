#include <iostream>
#include <vector>
#include <stdexcept>
#include <utility>
#include <string>

// ==========================================
// [Part 1] 예외 처리 (Exception Handling) 실습
// ==========================================

// BoundingBox 구조체 정의 컴퓨터 비전(Computer Vision)이나 에지 
// BoundingBox: AI 시스템에서 이미지, 영상 속 센서가 감지한 특정 객체(예: 위험물, 사람, 차량 등)의 위치를 사각형 형태로 감싸서 지정하는 영역
struct BoundingBox {
    int x, y, width, height;

    BoundingBox(int bx, int by, int bw, int bh) {
        // 비정상적인 바운딩 박스 크기(음수) 감지 시 예외 던지기 (throw)
        if (bw < 0 || bh < 0) {
            throw std::invalid_argument("Error: Width and height must not be negative! (너비와 높이는 음수일 수 없습니다)");
        }
        if (bx < 0 || by < 0) {
            throw std::out_of_range("Error: Coordinates are out of valid bounds! (좌표 범위를 벗어났습니다)");
        }
        x = bx;
        y = by;
        width = bw;
        height = bh;
        std::cout << "[Info] BoundingBox created successfully. (바운딩 박스 생성 완료)\n";
    }
};

// '''만약 3d BoundingBox를 구현하고 싶다면, 아래와 같이 구조체를 확장할 수 있습니다.'''
// #include <iostream>
// #include <stdexcept>
// #include <cmath> // std::abs 사용을 위해 필요

// struct BoundingBox3D {
//     double x, y, z;             // 3D 위치 좌표 (음수 허용!)
//     double width, height, depth;// 3D 크기 (음수 불가능)

//     BoundingBox3D(double bx, double by, double bz, double bw, double bh, double bd) {
//         // 1. 크기(Width, Height, Depth)는 물리적으로 음수가 될 수 없으므로 여전히 엄격하게 차단
//         if (bw < 0 || bh < 0 || bd < 0) {
//             throw std::invalid_argument("Error: Dimensions must not be negative! (크기는 음수일 수 없습니다)");
//         }

//         // 2. 좌표(x, y, z)는 음수일 수 있으므로 단순 '음수 금지' 체크는 제거!
//         // 대신 센서의 최대 물리 감지 거리(예: 100미터)를 벗어났는지를 체크하는 진짜 '범위 초과(out_of_range)' 검사로 변경합니다.
//         const double MAX_SENSOR_RANGE = 100.0; // 예시: 센서 최대 감지 거리 100m
//         if (std::abs(bx) > MAX_SENSOR_RANGE || std::abs(by) > MAX_SENSOR_RANGE || std::abs(bz) > MAX_SENSOR_RANGE) {
//             throw std::out_of_range("Error: Coordinates are out of sensor detection range! (센서 감지 범위를 초과했습니다)");
//         }

//         x = bx;
//         y = by;
//         z = bz;
//         width = bw;
//         height = bh;
//         depth = bd;
        
//         std::cout << "[Info] 3D BoundingBox created successfully. (3D 박스 생성 완료)\n";
//     }
// };

// ==========================================
// [Part 2] 이동 의미론 (Move Semantics) 실습
// ==========================================
class SensorBuffer {
private:
    std::string sensor_name_;
    std::vector<double> data_; // 대용량 센서 데이터 시뮬레이션

public:
    // Constructor (생성자)
    SensorBuffer(std::string name, size_t size) 
        : sensor_name_(name), data_(size, 3.14) {
        std::cout << "[Constructor] " << sensor_name_ << " allocated with size " << size << "\n";
    }

    // Destructor (소멸자)
    ~SensorBuffer() {
        std::cout << "[Destructor] " << sensor_name_ << " destroyed.\n";
    }

    // Move Constructor (이동 생성자) - 복사 없이 자원 훔치기! 이동 생성자 사용했을때 이제 필요없는 ptr b를 빈 객체로 만들어서 메모리 즉 자원 만 넘겨주고 a를 탄생
    // std::move: 객체는 이제 곧 버려도 되는 임시 객체(Rvalue) 취급을 해다오"*라고 신분을 바꿔주는 강제 캐스팅(Casting) 도구
    SensorBuffer(SensorBuffer&& other) noexcept
        : sensor_name_(std::move(other.sensor_name_)), data_(std::move(other.data_)) {
        std::cout << "[Move Constructor] Steals resources from " << sensor_name_ << " (이동 생성자 호출: 복사 비용 0)\n";
    }

    // 이동 대입 연산자 (`operator=`)
    SensorBuffer& operator=(SensorBuffer&& other) noexcept {
        // SensorBuffer& (리턴 타입): 대입 연산(a = b)이 끝난 뒤에 그 결과물인 자기 자신(*this)의 참조(reference)를 돌려주겠다는 뜻입니다. 
        // 레퍼런스(&)로 리턴하기 때문에 복사 없이 객체 자체를 반환할 수 있습니다.

        // operator= (함수 이름): C++ 컴파일러에게 "앞으로 코드에서 = 기호가 사용되면, 이 함수를 실행해라" 하고 약속해 주는 지정 키워드입니다. 
        // 우리가 평소에 쓰는 = 연산자의 진짜 동작 방식을 개발자가 직접 커스텀하는 것입니다. 사용자가 만든 클래스에서는 '=' 연산자가 기본적으로 제공되지 않기 때문에, 우리가 직접 정의해 주어야 합니다.

        // &&: 이 변수 other는 곧 쓰임이 끝나고 소멸할 불쌍한 임시 객체야. 그러니 아깝게 새로 복사하지 말고, 그 안에 든 대용량 메모리 주소를 안심하고 싹 훔쳐

        // 1. 자기 자신에게 대입하는 바보 같은 짓 방지 (예: a = std::move(a);)
        if (this != &other) {
            
            // 2. [가장 중요!] 내 안에 있던 기존 자원을 먼저 해제합니다. (메모리 누수 방지)
            // 만약 raw pointer를 썼다면 여기서 delete[] data_; 가 들어갑니다.
            // (std::vector 같은 컨테이너는 대입되는 순간 자기 옛날 메모리를 알아서 지워줍니다.)

            // 3. 상대방(other)의 자원을 내 안으로 훔쳐옵니다.
            sensor_name_ = std::move(other.sensor_name_);
            data_ = std::move(other.data_);

            // 4. 원본(other)은 빈털터리(nullptr)로 만듭니다.
            // other.data_ = nullptr;
        }
        return *this;
}

    // 불필요한 복사(Copy)를 원천 차단하기 위해 복사 생성자/대입 연산자는 삭제
    SensorBuffer(const SensorBuffer&) = delete;
    SensorBuffer& operator=(const SensorBuffer&) = delete;

    size_t getSize() const { return data_.size(); }
};

int main() {
    // ------------------------------------------
    // 실습 1: 잘못된 데이터 예외 처리 테스트
    // ------------------------------------------
    std::cout << "=== Part 1: Exception Handling Test (예외 처리) ===\n";
    try {
        std::cout << "1. 정상적인 바운딩 박스 생성 시도...\n";
        BoundingBox valid_box(10, 20, 100, 200);

        std::cout << "\n2. 비정상적인 바운딩 박스(음수 너비) 생성 시도...\n";
        BoundingBox invalid_box(10, 20, -50, 200); // 여기서 예외 발생!
    } 
    catch (const std::exception& e) {
        std::cout << "[Exception Caught] " << e.what() << "\n\n";
    }

    // ------------------------------------------
    // 실습 2: Move Semantics를 통한 대용량 데이터 이동 테스트
    // ------------------------------------------
    std::cout << "=== Part 2: Move Semantics Test (이동 의미론) ===\n";
    {
        // 100만 개의 요소를 가진 대용량 센서 버퍼 생성
        SensorBuffer raw_sensor("LiDAR_Sensor_A", 1'000'000);
        std::cout << "Original buffer size: " << raw_sensor.getSize() << "\n\n";

        // std::move를 통해 복사 비용 없이 소유권을 processed_sensor로 통째로 이전
        std::cout << "--- Transferring ownership via std::move ---\n";
        SensorBuffer processed_sensor = std::move(raw_sensor);

        std::cout << "\nAfter move - processed_sensor size: " << processed_sensor.getSize() << "\n";
        std::cout << "After move - raw_sensor size: " << raw_sensor.getSize() << " (자원을 뺏겨서 0이 됨)\n\n";
    } // 범위를 벗어나면서 생성된 객체들이 안전하게 소멸됨

    std::cout << "=== All tasks completed safely! (모든 실습 정상 종료) ===\n";
    return 0;
}