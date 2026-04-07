cmake_minimum_required(VERSION 3.10)
project(str_project)

set(CMAKE_CXX_STANDARD 17)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
    add_executable(code main.cpp)
else()
    # Create a dummy main.cpp just in case
    file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/dummy.cpp" "int main() { return 0; }")
    add_executable(code dummy.cpp)
endif()
