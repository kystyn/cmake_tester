# CMakeList.txt : CMake project for TestEnvironment, include source and define
# project specific logic here.
# see https://habr.com/ru/post/433822/
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
#add_executable (TestEnvironment "TestEnvironment.cpp" "TestEnvironment.h")

# TODO: Add tests and install targets if needed.
# Добавить тесты:

set(Executable, test)

enable_testing()
SET (TestEnvironment_TIMEOUT 100)
add_test(FirstTest Executable 1 2 1)
add_test(SecondTest Executable 0 2 -4)
add_test(ThirdTest Executable 1)
add_test(Test4 Exexutable 1 1)
add_test(Test5 Executable 0 0 1)

# Установить поведение тестов:
set_tests_properties(FirstTest SecondTest ThirdTest
PROPERTIES TIMEOUT ${TestEnvironment_TIMEOUT})

set_tests_properties(FirstTest PROPERTIES
PASS_REGULAR_EXPRESSION "The result is: -1"
FAIL_REGULAR_EXPRESSION "Error!")

set_tests_properties(SecondTest PROPERTIES
PASS_REGULAR_EXPRESSION "The result is: 2\*"
FAIL_REGULAR_EXPRESSION "Error!")

set_tests_properties(ThirdTest PROPERTIES
PASS_REGULAR_EXPRESSION "Error!")

set_tests_properties(Test4 PROPERTIES
PASS_REGULAR_EXPRESSION "Error!")

set_tests_properties(Test5 PROPERTIES
PASS_REGULAR_EXPRESSION "Error!")

