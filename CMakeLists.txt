cmake_minimum_required(VERSION 3.16)
project(Gao4AAutopilot VERSION 5.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 可选依赖（不强制）
find_package(Eigen3 QUIET)
find_package(yaml-cpp QUIET)
find_package(OpenCV QUIET)
find_package(Threads REQUIRED)
find_package(BTCPP QUIET)          # BehaviorTree.CPP
find_package(ONNX QUIET)           # 世界模型推理

option(ENABLE_WATERMARK "Enable watermarking" ON)
option(ENABLE_COROUTINE "Enable C++20 coroutine" ON)
option(ENABLE_BEHAVIOR_TREE "Enable behavior tree safety" ON)
option(ENABLE_ONNX "Enable ONNX Runtime" OFF)

if(ENABLE_WATERMARK)
    add_compile_definitions(GAO_ENABLE_WATERMARK)
endif()
if(ENABLE_COROUTINE)
    add_compile_definitions(GAO_ENABLE_COROUTINE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcoroutines")
endif()
if(ENABLE_BEHAVIOR_TREE AND BTCPP_FOUND)
    add_compile_definitions(GAO_ENABLE_BEHAVIOR_TREE)
endif()
if(ENABLE_ONNX AND ONNX_FOUND)
    add_compile_definitions(GAO_ENABLE_ONNX)
endif()

# 收集基座源文件（排除 main.cpp）
file(GLOB_RECURSE BASE_SRC
    src/common/*.cpp
    src/control/*.cpp
    src/safety/*.cpp
    src/scenario/*.cpp
    src/intelligence/*.cpp
    src/bridge/*.cpp
    src/cross_domain/*.cpp
    src/digital_twin/*.cpp
    src/ai/*.cpp
)
list(REMOVE_ITEM BASE_SRC ${CMAKE_SOURCE_DIR}/src/main.cpp)

add_library(gao_base STATIC ${BASE_SRC})
target_include_directories(gao_base PUBLIC src)
target_link_libraries(gao_base PUBLIC Threads::Threads)

if(Eigen3_FOUND)
    target_link_libraries(gao_base PUBLIC Eigen3::Eigen)
endif()
if(yaml-cpp_FOUND)
    target_link_libraries(gao_base PUBLIC yaml-cpp)
endif()
if(OpenCV_FOUND)
    target_link_libraries(gao_base PUBLIC ${OpenCV_LIBS})
endif()
if(BTCPP_FOUND)
    target_link_libraries(gao_base PUBLIC BTCPP::BTCPP)
endif()
if(ENABLE_ONNX AND ONNX_FOUND)
    target_link_libraries(gao_base PRIVATE onnxruntime)
endif()

# 安装（方便分支使用 find_package）
install(TARGETS gao_base DESTINATION lib)
install(DIRECTORY src/ DESTINATION include/gao_base FILES_MATCHING PATTERN "*.h")

# 基座演示程序
add_executable(gao_base_demo src/main.cpp)
target_link_libraries(gao_base_demo PRIVATE gao_base)

# 单元测试
enable_testing()
function(add_test_executable TEST_NAME TEST_FILE)
    add_executable(${TEST_NAME} ${TEST_FILE})
    target_link_libraries(${TEST_NAME} PRIVATE gao_base)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()

file(GLOB TEST_FILES test/test_*.cpp)
foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    add_test_executable(${TEST_NAME} ${TEST_FILE})
endforeach()
