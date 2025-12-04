cmake_minimum_required(VERSION 3.15)
project(Dnevnik VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

add_executable(dnevnik
    main.cpp
    DateTime/Date.cpp
    DateTime/Time.cpp
    Entry/DiaryEntry.cpp
    Diary/Diary.cpp
    Utils/utils.cpp
)

target_include_directories(dnevnik PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/DataStructures
    ${CMAKE_CURRENT_SOURCE_DIR}/DateTime
    ${CMAKE_CURRENT_SOURCE_DIR}/Entry
    ${CMAKE_CURRENT_SOURCE_DIR}/Diary
    ${CMAKE_CURRENT_SOURCE_DIR}/Utils
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.0)
    target_link_libraries(dnevnik PRIVATE stdc++fs)
endif()

install(TARGETS dnevnik
    RUNTIME DESTINATION bin
)

install(FILES "${CMAKE_SOURCE_DIR}/dnevnik.txt"
    DESTINATION bin
)

install(DIRECTORY "${CMAKE_SOURCE_DIR}/unosi"
    DESTINATION bin
)

option(BUILD_TESTS "Build test programs" OFF)
if(BUILD_TESTS)
    enable_testing()
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")