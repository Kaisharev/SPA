cmake_minimum_required(VERSION 3.15)
project(SensorNetwork VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /utf-8)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()


set(SOURCES
    src/main.cpp
    src/algorithms/Dijkstra.cpp
    src/algorithms/KruskalMST.cpp
    src/algorithms/UnionFind.cpp
    src/graph/graph.cpp
    src/loaders/GraphLoader.cpp
    src/loaders/SensorLoader.cpp
    src/reports/ReportGenerator.cpp
    src/simulation/FailureSimulator.cpp
    src/simulation/LoadCalculator.cpp
    src/tree/Tree.cpp
    src/tree/TreeBuilder.cpp
)

set(LIB_SOURCES
    src/algorithms/Dijkstra.cpp
    src/algorithms/KruskalMST.cpp
    src/algorithms/UnionFind.cpp
    src/graph/graph.cpp
    src/loaders/GraphLoader.cpp
    src/loaders/SensorLoader.cpp
    src/reports/ReportGenerator.cpp
    src/simulation/FailureSimulator.cpp
    src/simulation/LoadCalculator.cpp
    src/tree/Tree.cpp
    src/tree/TreeBuilder.cpp
)

add_library(sensor_lib STATIC ${LIB_SOURCES})
target_include_directories(sensor_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(zadaca src/main.cpp)
target_link_libraries(zadaca PRIVATE sensor_lib)

option(BUILD_TESTS "Build unit tests" ON)

if(BUILD_TESTS)
    enable_testing()
    
    # Test UnionFind
    add_executable(test_unionfind tests/test_UnionFind.cpp)
    target_link_libraries(test_unionfind PRIVATE sensor_lib)
    add_test(NAME UnionFindTest COMMAND test_unionfind)
    
    # Test KruskalMST
    add_executable(test_kruskal tests/test_KruskalMST.cpp)
    target_link_libraries(test_kruskal PRIVATE sensor_lib)
    add_test(NAME KruskalTest COMMAND test_kruskal)
    
    # Test Dijkstra
    add_executable(test_dijkstra tests/test_Dijkstra.cpp)
    target_link_libraries(test_dijkstra PRIVATE sensor_lib)
    add_test(NAME DijkstraTest COMMAND test_dijkstra)
    
    # Test LoadCalculator
    add_executable(test_loadcalc tests/test_LoadCalculator.cpp)
    target_link_libraries(test_loadcalc PRIVATE sensor_lib)
    add_test(NAME LoadCalculatorTest COMMAND test_loadcalc)
    
    # Test Tree
    add_executable(test_tree tests/test_Tree.cpp)
    target_link_libraries(test_tree PRIVATE sensor_lib)
    add_test(NAME TreeTest COMMAND test_tree)
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Build tests: ${BUILD_TESTS}")

install(TARGETS zadaca
    RUNTIME DESTINATION bin
)


install(DIRECTORY "${CMAKE_SOURCE_DIR}/data"
    DESTINATION bin
)

if(BUILD_TESTS)
    install(TARGETS 
        test_unionfind 
        test_kruskal 
        test_dijkstra 
        test_loadcalc 
        test_tree
        RUNTIME DESTINATION bin/tests
    )
endif()