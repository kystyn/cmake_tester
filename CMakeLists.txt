# CMakeList.txt : CMake project for TestEnvironment, include source and define
# project specific logic here.
# see https://habr.com/ru/post/433822/
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
#add_executable (TestEnvironment "TestEnvironment.cpp" "TestEnvironment.h")

# TODO: Add tests and install targets if needed.
# Добавить тесты:

enable_testing()
SET (TestEnvironment_TIMEOUT 100)
add_test(Trivial_FirstTest ${PROJECT_NAME} 1 2 1)
add_test(Normal_SecondTest ${PROJECT_NAME} 0 2 -4)
add_test(Easy_ThirdTest ${PROJECT_NAME} 1)
add_test(Hard_Test4 ${PROJECT_NAME} 1 1)
add_test(Impossible_Test5 ${PROJECT_NAME} 0 0 1)

# Установить поведение тестов:
set_tests_properties(Trivial_FirstTest Normal_SecondTest Easy_ThirdTest
PROPERTIES TIMEOUT ${TestEnvironment_TIMEOUT})

set_tests_properties(Trivial_FirstTest PROPERTIES
PASS_REGULAR_EXPRESSION "The result is: -1"
FAIL_REGULAR_EXPRESSION "Error!")

set_tests_properties(Normal_SecondTest PROPERTIES
PASS_REGULAR_EXPRESSION "The result is: 2\*"
FAIL_REGULAR_EXPRESSION "Error!")

set_tests_properties(Easy_ThirdTest PROPERTIES
PASS_REGULAR_EXPRESSION "Error!")

set_tests_properties(Hard_Test4 PROPERTIES
PASS_REGULAR_EXPRESSION "Error!")

set_tests_properties(Impossible_Test5 PROPERTIES
PASS_REGULAR_EXPRESSION "Error!")

