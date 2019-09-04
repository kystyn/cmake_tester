# CMakeList.txt : CMake project for TestEnvironment, include source and define
# project specific logic here.
# see https://habr.com/ru/post/433822/
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
#add_executable (TestEnvironment "TestEnvironment.cpp" "TestEnvironment.h")

set(UTILADDR "../../util/build/${PROJECT_NAME}")

# TODO: Add tests and install targets if needed.
# Добавить тесты:

enable_testing()
SET (TestEnvironment_TIMEOUT 100)
add_test(Trivial_FirstTest UTILADDR ex1.png res.png)

# Установить поведение тестов:
set_tests_properties(Trivial_FirstTest
PROPERTIES TIMEOUT ${TestEnvironment_TIMEOUT})

set_tests_properties(Trivial_FirstTest PROPERTIES
PASS_REGULAR_EXPRESSION "The result is: -1"
FAIL_REGULAR_EXPRESSION "Error!")
