cmake_minimum_required(VERSION 3.10)

project(task3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(DEFINED ENV{THREAD_SANITIZER})
    if($ENV{THREAD_SANITIZER} STREQUAL "1")
        message(STATUS "Enabling ThreadSanitizer")
        add_compile_options(-fsanitize=thread -g -O1)
        add_link_options(-fsanitize=thread)
    endif()
endif()

if(DEFINED ENV{ADDRESS_SANITIZER})
    if($ENV{ADDRESS_SANITIZER} STREQUAL "1")
        message(STATUS "Enabling AddressSanitizer")
        add_compile_options(-fsanitize=address -g -O1)
        add_link_options(-fsanitize=address)
    endif()
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(SRCS
    src/main.cpp
    src/logic.cpp
    src/iofuncs.cpp
    src/constants.cpp
)

set(TESTS_NECESSITY
    src/logic.cpp
    src/iofuncs.cpp
    src/constants.cpp
)

set(TEST_SRCS
    tests/tests.cpp
)

find_package(GTest REQUIRED)

add_executable(main ${SRCS})

target_link_libraries(main PRIVATE pthread)

add_executable(tests_executable ${TEST_SRCS} ${TESTS_NECESSITY})

target_link_libraries(tests_executable PRIVATE GTest::GTest GTest::Main pthread)

add_dependencies(tests_executable main)

add_test(NAME task1tests COMMAND tests_executable)

set_target_properties(main tests_executable PROPERTIES CLEAN_DIRECTORIES "YES")
