cmake_minimum_required(VERSION 3.10)

project(labwork6)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем санитайзеры
if(DEFINED ENV{THREAD_SANITIZER})
    if(ENV{THREAD_SANITIZER} STREQUAL "1")
        message(STATUS "Enabling ThreadSanitizer")
        add_compile_options(-fsanitize=thread -g -O1)
        add_link_options(-fsanitize=thread)
    endif()
endif()

if(DEFINED ENV{ADDRESS_SANITIZER})
    if(ENV{ADDRESS_SANITIZER} STREQUAL "1")
        message(STATUS "Enabling AddressSanitizer")
        add_compile_options(-fsanitize=address -g -O1)
        add_link_options(-fsanitize=address)
    endif()
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# Основные исходники
set(SRCS
    main.cpp
    general/code/utils.cpp
    Task_1/src/task1.cpp
    Task_1/src/utils.cpp
    Task_2/src/task2.cpp
    Task_2/src/utils.cpp
    Task_3/src/task3.cpp
    Task_3/src/logic.cpp
    Task_3/src/iofuncs.cpp
)

# Зависимости для тестов
set(TESTS1_NECESSITY
    general/code/utils.cpp
    Task_1/src/utils.cpp
)

set(TESTS2_NECESSITY
    general/code/utils.cpp
    Task_2/src/utils.cpp
)

set(TESTS3_NECESSITY
    general/code/utils.cpp
    Task_3/src/logic.cpp
    Task_3/src/iofuncs.cpp
)

# Исходники тестов
set(TEST_SRCS1
    Task_1/tests/tests.cpp
)

set(TEST_SRCS2
    Task_2/tests/tests.cpp
)

set(TEST_SRCS3
    Task_3/tests/tests.cpp
)

# Подключаем GTest
find_package(GTest REQUIRED)

# Основной исполняемый файл
add_executable(main ${SRCS})
target_link_libraries(main PRIVATE pthread)

# Создаем тестовые исполняемые файлы
add_executable(tests1 ${TEST_SRCS1} ${TESTS1_NECESSITY})
target_link_libraries(tests1 PRIVATE GTest::GTest GTest::Main pthread)

add_executable(tests2 ${TEST_SRCS2} ${TESTS2_NECESSITY})
target_link_libraries(tests2 PRIVATE GTest::GTest GTest::Main pthread)

add_executable(tests3 ${TEST_SRCS3} ${TESTS3_NECESSITY})
target_link_libraries(tests3 PRIVATE GTest::GTest GTest::Main pthread)

# Установка зависимостей сборки (по желанию)
add_dependencies(tests1 main)
add_dependencies(tests2 main)
add_dependencies(tests3 main)

# Регистрация тестов
add_test(NAME task1tests COMMAND tests1)
add_test(NAME task2tests COMMAND tests2)
add_test(NAME task3tests COMMAND tests3)

# Настройка свойств сборки
set_target_properties(main tests1 tests2 tests3 PROPERTIES CLEAN_DIRECTORIES "YES")
