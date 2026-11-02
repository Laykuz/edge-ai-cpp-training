#include <iostream>

class VisionResult {
private:
    // 1. 데이터를 외부에서 함부로 바꿀 수 없도록 은닉 (private)
    bool is_detected_;
    int bbox_[4];
    float confidence_;
public:
    // 2. 생성자 + 초기화 리스트로 안전하게 값 채우기
    VisionResult(bool detected, const int bbox[4], float confidence) 
        : is_detected_(detected), confidence_(confidence) {
        // 배열은 초기화 리스트에서 바로 대입이 안 되므로 복사해 줍니다
        for(int i = 0; i < 4; ++i) {
            bbox_[i] = bbox[i];
        }
    }

    // 3. 데이터를 수정하지 않고 읽기만 하는 함수 (const 멤버 함수)
    // 외부에서 객체를 const로 받아도 이 함수들은 안전하게 호출할 수 있습니다.
    bool isDetected() const {
        return is_detected_;
    }

    float getConfidence() const {
        return confidence_;
    }

    // 바운딩 박스를 통째로 안전하게 꺼내주는 함수
    void getBbox(int out_bbox[4]) const {
        for(int i = 0; i < 4; ++i) {
            out_bbox[i] = bbox_[i];
        }
    }
};

int main() {
    int initial_bbox[4] = {10, 20, 100, 200};
    VisionResult vr(true, initial_bbox, 0.95f);

    // ---------------------------------------------------------
    // 1. 일반적인 반환값(Return value)이 있는 Getter 호출하기
    // ---------------------------------------------------------
    bool detected_result = vr.isDetected();       // 값을 복사해서 가져옴
    float confidence_score = vr.getConfidence(); // 값을 복사해서 가져옴

    std::cout << "감지 여부: " << (detected_result ? "성공" : "실패") << "\n";
    std::cout << "신뢰도 점수: " << confidence_score << "\n";


    // ---------------------------------------------------------
    // 2. 배열을 받아오는 getBbox 함수 호출하기
    // ---------------------------------------------------------
    // 배열은 C++에서 함수가 통째로 리턴하기 까다롭기 때문에, 
    // 빈 그릇(배열)을 먼저 메인에서 준비해서 던져주어야 합니다!
    int my_copied_bbox[4]; 

    vr.getBbox(my_copied_bbox); // 함수에 그릇을 넘겨주면, 안에서 값이 쏙 채워져서 나옴

    // 채워진 값 확인하기
    std::cout << "가져온 BBox 좌표: " 
              << my_copied_bbox[0] << ", " 
              << my_copied_bbox[1] << ", " 
              << my_copied_bbox[2] << ", " 
              << my_copied_bbox[3] << "\n";

    return 0;
}

