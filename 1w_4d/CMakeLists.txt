# 1. CMake 최소 요구 버전 설정
cmake_minimum_required(VERSION 3.10)

# 2. 프로젝트 이름과 사용할 언어 설정 (C++ 프로젝트)
project(CppTraining VERSION 1.0 LANGUAGES CXX)

# 3. 사용할 C++ 표준 지정 (C++17 또는 C++20 등)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. 내 프로젝트에서 실행파일을 어떤 소스들로 만들 것인지 지정
# 예: main.cpp와 다른 소스파일들을 묶어서 'MyProgram'이라는 이름의 실행파일로 만든다!
add_executable(MyProgram 1w_4d/Polygon.cpp)